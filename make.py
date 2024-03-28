import argparse
import datetime
import os, shutil
import json
from http.server import HTTPServer, SimpleHTTPRequestHandler
import threading
import re
import subprocess


CONFIG = 'docs/_config'
CONFIG_DATABASE = os.path.join(CONFIG, "db.json")
CONFIG_SITEMAP = os.path.join(CONFIG, "sitemap.xml")
SITE_BASEURL = 'https://wklchris.github.io/blog/'

DOCSRC, DOCDST = 'docsrc', 'docs'
ENCODING = 'utf-8'

def docsrc_prefix_path(*path, docsrc_path="docsrc"):
    return os.path.join(docsrc_path, *path)

def docdst_prefix_path(*path, docdst_path="docs"):
    return os.path.join(docdst_path, *path)

def write_str_into_file(docstr, *path):
    fpath = docsrc_prefix_path(*path)
    with open(fpath, 'w', encoding=ENCODING) as f:
        f.write(docstr)

def read_from_file(fpath, join=True):
    with open(fpath ,'r', encoding=ENCODING) as f:
        lines = f.readlines()
    return lines if not join else ''.join(lines)

def load_json(fpath):
    with open(fpath, 'r', encoding=ENCODING) as f:
        data = json.load(f)
    return data

def sort_dict(dictdata, keep_last=["rst_prolog"]):
    # Sort dict by keys, except keeping a list of keys in the last
    d = {k: dictdata[k] for k in sorted(dictdata.keys()) if k not in keep_last}
    for k in keep_last:
        if k in dictdata.keys():
            d |= {k: dictdata[k]}
    return d

def create_new_doc(docname, doctitle=None):
    """
    Create a new document and init it.
    """
    if not doctitle:
        doctitle = docname
    doc_path = docsrc_prefix_path(docname)
    if not os.path.isdir(doc_path):
        os.mkdir(doc_path)
        init_new_doc(docname, doctitle) 
        print(f"Document '{docname}' has been initialized under '{doc_path}'.")
    else:
        print(f"Document folder '{docname}' already exist.")

def init_conf_py(docname, doctitle):
    """
    Initialize the new document folder with configuration files.
    """
    # Read the general conf.py settings from hyperconf.json
    hyperconf_path = os.path.join(CONFIG, "hyperconf.json")
    doc_conf = load_json(hyperconf_path)
    ## Add doc-wise information & Sort
    doc_conf['year'] = int(f"{datetime.datetime.today():%Y}")
    doc_conf['project'] = doctitle
    doc_conf = sort_dict(doc_conf)
    # Append blog title to canonical url
    if 'canonical_url' in doc_conf['html_theme_options']:
        doc_conf['html_theme_options']['canonical_url'] += f"{docname}/"

    # Write the dict into a .py file
    def write_dict_value(dict_val):
        ## Dict value is either string or int/list
        if isinstance(dict_val, str):
            s = dict_val.strip()
            lwrap, rwrap = ('"', '"')
            # Use triple-quote format if the string has newline
            if '\n' in dict_val:
                lwrap = '"""\n'
                rwrap = '\n"""'
            write_str = f'{lwrap}{s}{rwrap}'
        else:
            write_str = dict_val
        return write_str
    
    conf_str = '\n'.join([
        f"{k} = {write_dict_value(v)}" for k,v in doc_conf.items() 
    ])
    write_str_into_file(conf_str, docname, "conf.py")

def init_index_rst(docname, doctitle):
    """
    Initialize the index.rst for table of content of the document.
    """
    rst_config_template =read_from_file(os.path.join(CONFIG, "index.rst"))
    title_heading = "{}\n{}\n".format(doctitle, '='*(len(doctitle) + 4))
    rst_str = rst_config_template.replace("{{ title heading }}", title_heading)
    write_str_into_file(rst_str, docname, "index.rst")

def init_new_doc(docname, doctitle):
    """
    Init/Copy files:
    + "conf.py"
    + "index.rst"
    """
    init_conf_py(docname, doctitle)    # Init conf.py
    init_index_rst(docname, doctitle)  # Init index.rst

def sphinx_build(docname, update_home=True):
    """
    Build the Sphinx website and output files in specifc folder.
    """
    if docname == "_homepage" and update_home:
        update_homepage()
        return
    # Buld the HTML website
    build_dirname = "build"
    build_dir = docsrc_prefix_path(docname, build_dirname)
    src_dir = docsrc_prefix_path(docname)
    cmd = f"sphinx-build -M html {src_dir} {build_dir}"
    os.system(cmd)
    # Copy to /docs folder
    if docname != "_homepage":
        dst_dir = docdst_prefix_path(docname)
    else:
        dst_dir = docdst_prefix_path("")
    shutil.copytree(os.path.join(build_dir, "html"), dst_dir, dirs_exist_ok=True)
    # Delete the build folder from src directory
    shutil.rmtree(build_dir)
    print("---\nHTML pages have been moved into " + dst_dir)
    
    # Automatically update the database & homepage
    if docname != "_homepage":
        update_database(docname)
        if update_home:
            update_homepage()

def update_json(json_file, docname, docmeta):
    if docname == "_homepage":
        return
    d = load_json(json_file)
    def _treat_as_list(inputs):
        return inputs if isinstance(inputs, list) else [inputs]
        
    def _add_doc_to_list(parentkey):
        multiple_value_lst = _treat_as_list(docmeta[parentkey])
        for child in multiple_value_lst:
            children_docs = d[parentkey].get(child, [])
            if docname not in children_docs:
                children_docs.append(docname)
            d[parentkey][child] = sorted(children_docs)
    
    # Delete relevant records first (if docname exists)
    if docname in d["blogs"]:
        pop_meta = d["blogs"][docname]
        for parentkey in "series,keywords,category".split(','):
            for key in _treat_as_list(pop_meta[parentkey]):
                after_remove = [x for x in d[parentkey][key] if x != docname]
                if after_remove:
                    d[parentkey][key] = after_remove
                else:  # delete the key if the list is empty
                    _ = d[parentkey].pop(key, None)
        _ = d["blogs"].pop(docname, None)
    # If docmeta != None, add relevant records
    if docmeta:
        # Add to blogs key
        d["blogs"][docname] = docmeta
        # Add to series key
        series_docs = d["series"].get(docmeta["series"], [])
        if docname not in series_docs:
            series_docs.append(docname)
        series_lst = []
        for doc in series_docs:
            doc_series_num = int(d["blogs"][doc].get("series_num", -1))
            series_lst.append((doc_series_num, doc))
        d["series"][docmeta["series"]] = [val[1] for val in sorted(series_lst)]
        # Add to keywords & category key
        for parent_key in "keywords,category".split(','):
            _add_doc_to_list(parent_key)
    
    # Update homepage meta
    d["_homepage"]["date_modified"] = f"{datetime.datetime.today():%Y-%m-%d}"
    # Sort keys and write back to the json file
    for k in "_homepage,blogs,category,keywords,series".split(","):
        d[k] = sort_dict(d[k])
    with open(json_file, 'w', encoding=ENCODING) as f:
        json.dump(d, f, indent=4, ensure_ascii=False)

def update_database(docname):
    """
    Update the metadata database & sitemap after building cuurent document.
    """
    # Read the meta header of the source document RST
    doc_str_lines = read_from_file(docsrc_prefix_path(docname, "index.rst"), join=False)
    doc_meta = dict()
    for line in doc_str_lines[1:]:
        line = line.strip()
        if line.startswith(':'):
            key, value = line[1:].split(':', 1)
            doc_meta[key] = value.strip()
        else:
            break
    # Update modification date
    doc_meta["keywords"] = [x.strip() for x in doc_meta["keywords"].split(',')]
    doc_meta["date_build"] = f"{datetime.datetime.today():%Y-%m-%d}"
    doc_meta["abstract"] = doc_meta.pop("abstract")  # put abstract at last
    # Write into the database
    update_json(CONFIG_DATABASE, docname, doc_meta)
    # Update sitemap
    update_sitemap()
    print('Database & sitemap has been updated.')

def update_homepage():
    """
    Update & build the homepage based on the latest updated document.
    """
    def _generate_blog_datatable():
        total_meta = load_json(CONFIG_DATABASE)  
        blog_list = [doc for doc in total_meta["blogs"].keys() if not doc.startswith('_')]

        table_wrapper = lambda tabhtml: f'<table id="tableofblogs" class="display">\n{tabhtml}\n</table>'
        def write_tabrow(rowdata, wrapper='tbody'):
            inner = 'td' if wrapper == 'tbody' else 'th'
            inner_html = '\n'.join([f"<{inner}>{x}</{inner}>" for x in rowdata])
            row_html = f"<tr>\n{inner_html}\n</tr>"
            return row_html
        # Write table head <thead>
        head_row = "日志名,分类,摘要,上线,更新".split(',')
        head_html = f"<thead>\n{write_tabrow(head_row, 'thead')}\n</thead>"
        # Write table body <tbody>
        table_rows = ["" for _ in blog_list]
        for i, docname in enumerate(blog_list):
            doc_meta = total_meta["blogs"][docname]
            doc_row = [
                f'<a href="{docname}/index.html">{docname}</a>',
                doc_meta["category"],
                doc_meta["abstract"],
                doc_meta["date_init"],
                doc_meta["date_modified"]
            ]
            table_rows[i] = write_tabrow(doc_row, 'tbody')
        tbody_html = '\n'.join(table_rows)
        body_html = f"<tbody>\n{tbody_html}\n</tbody>"
        return table_wrapper(f"{head_html}\n{body_html}")
    
    rst_str = read_from_file(os.path.join(CONFIG, "index-homepage.rst"))
    blog_table_str = _generate_blog_datatable()
    write_str_into_file(blog_table_str, "_homepage", "tableofblogs.html")

    # Write it to index.rst and build the homepage
    write_str_into_file(rst_str, "_homepage", "index.rst")
    sphinx_build("_homepage", update_home=False)  # Avoid self-cycle

def update_index_rst_modified_date(docname):
    """
    Use 'git diff' to check if any file in docsrc/docname folder has been changed.
    If any, update the modified date metadata in index.rst. 
    """
    meta_key = ":date_modified:"
    date_regex = re.compile(r"\d{4}-\d{2}-\d{2}")
    def get_command_output(cmdstr):
        cmd_strlst = cmdstr.split()
        cmd_output = subprocess.run(cmd_strlst, stdout=subprocess.PIPE).stdout.decode('utf-8')
        return cmd_output
    # Check if there is change in any file that has been:
    #   * Modified but not staged yet, or
    #   * Staged
    diff_modified = f"git diff --name-only docsrc/{docname}"
    output_modified = get_command_output(diff_modified)
    diff_staged = f"git diff --name-only --staged docsrc/{docname}"
    output_staged = get_command_output(diff_staged)
    if len(output_modified) + len(output_staged) > 0:
        date_now = f"{datetime.datetime.today():%Y-%m-%d}"
        index_rst = read_from_file(docsrc_prefix_path(docname, 'index.rst'), join=False)

        # Find the date modified line number
        lineindex = -1
        for i, line in enumerate(index_rst):
            if line.lstrip().startswith(meta_key):
                lineindex = i
                break
        if lineindex >= 0:
            index_rst[lineindex] = re.sub(date_regex, date_now, index_rst[lineindex])
        
        # Write back to index.rst
        index_rst_str = ''.join(index_rst)
        write_str_into_file(index_rst_str, docname, 'index.rst')
        print(f"Auto-update modified date in {docname}/index.rst.")

def update_sitemap():
    """
    Read blog data from CONFIG_DATABASE and write it into sitemap.
    """
    sitemap_str = ('<?xml version="1.0" encoding="UTF-8"?>\n\n'
        '<urlset xmlns="http://www.sitemaps.org/schemas/sitemap/0.9">')
    sitemap_foot = '</urlset>'
    def create_sitemap_item(url, lastmod):
        item = (
            "  <url>\n"
            f"    <loc>{url}</loc>\n"
            f"    <lastmod>{lastmod}</lastmod>\n"
            "  </url>"
        )
        return item
    
    # Read blogs data
    db = load_json(CONFIG_DATABASE)
    blogs = sort_dict(db["blogs"])
    site_lastmod = db["_homepage"]["date_modified"]
    site_docs = {}
    for dockey in [*blogs.keys(), "_homepage"]:
        dirpath = os.path.join(DOCSRC, dockey)
        files = [f for f in os.listdir(dirpath) if f.endswith(('.ipynb', '.rst'))]
        lastmod = blogs[dockey]["date_build"] if dockey != "_homepage" else site_lastmod
        for docpage_fname in files:
            pname, _ = os.path.splitext(docpage_fname)
            if dockey == '_homepage':
                item_url = SITE_BASEURL  # Main site canonical url
            else:
                item_url = f"{SITE_BASEURL}{dockey}/{pname}.html"
            site_docs[item_url] = lastmod
    # Join all page items
    for url, moddate in site_docs.items():
        sitemap_item = create_sitemap_item(url, moddate)
        sitemap_str += "\n" + sitemap_item
    sitemap_str += "\n" + sitemap_foot

    with open(CONFIG_SITEMAP, 'w', encoding=ENCODING) as f:
        f.write(sitemap_str)

def remove_doc(docname, update_home=True):
    """
    Remove a doc from both local file and the database.
    """
    check_remove = None
    while not check_remove:
        user_option = input(f"Are you sure to remove {docname}? [y/n] y: ")
        if user_option in list('yn'):
            check_remove = user_option
    if check_remove == "n":
        exit

    # Remove source & build directory, if exists
    doc_dir = docsrc_prefix_path(docname)
    build_dir = docdst_prefix_path(docname)
    for dirpath in (doc_dir, build_dir):
        if os.path.isdir(dirpath):
            shutil.rmtree(dirpath)
    # Remove docname key from the database 
    update_json(CONFIG_DATABASE, docname, None)
    if update_home:
        update_homepage()
    print(f"Removed {docname} from the database, {doc_dir}, and {build_dir}.")

def start_local_server(docname):
    """
    Host a mini local server to preview the website before online.
    """
    bind, port = "localhost", 8000
    if docname == "_homepage":
        doc_url = f"http://{bind}:{port}"
    else:
        doc_url = f"http://{bind}:{port}/{docname}/"

    class Handler(SimpleHTTPRequestHandler):
        def __init__(self, *args, **kwargs):
            super().__init__(*args, directory=DOCDST, **kwargs)
    
    httpd = HTTPServer((bind, port), Handler)
    thread = threading.Thread(target=httpd.serve_forever)
    thread.start()
    # Open the doc main webpage in the webbrowser
    os.system(f'PowerShell -Command "Start-Process -FilePath {doc_url}"')

    # Press Enter for server shutdown
    _ = input(f'\nHosting server at {bind}:{port}. Press Enter to terminate ...\n\n')
    httpd.shutdown()
    print('---\nLocal server has been terminated.')

def enable_args():
    parser = argparse.ArgumentParser(
        description='Tool for making Sphinx HTML pages.'
    )
    args_help = {
        "docname": "Specify the docname (also project folder name).",
        "--create": "Create a new project. Won't overwrite existing ones. (Exclusive to --build)",
        "--build": "Build a project. (Exclusive to --create)",
        "--title": "Give a title to new project. Only work in --create mode.",
        "--config": "Specific the config folder path.",
        "--remove": "Remove a document from the website.",
        "--no-update-homepage": "Don't autobuild homepage. Work in --build/remove mode.",
        "--server": "Host a local server to preview website."
    }

    parser.add_argument('docname', help=args_help['docname'])
    parser_group = parser.add_mutually_exclusive_group()
    parser_group.add_argument('--build', '-b', help=args_help['--build'], action='store_true')
    parser_group.add_argument('--create', '-c', dest='build', help=args_help["--create"], action='store_false')
    parser_group.add_argument('--remove', '-R', help=args_help["--remove"], action='store_true')
    parser_group.add_argument('--server', '-s', help=args_help['--server'], action='store_true')
    parser_group.set_defaults(build=True, remove=False, server=False)

    parser.add_argument('--title', '-t', help=args_help['--title'], nargs='+', default=None)
    parser.add_argument('--no-update-homepage', '-N', dest='update_homepage', help=args_help['--no-update-homepage'], action='store_false')
    
    # Exclusive modes: build, create, server, remove.
    args = parser.parse_args()
    if args.remove:
        remove_doc(args.docname, args.update_homepage)
    elif args.server:
        start_local_server(args.docname)
    # Exclusive modes: build, create
    elif args.build:
        if args.docname == ".":
            _doclst = [d for d in os.listdir('docsrc') if not d.startswith('_')]
            for d in _doclst:
                update_index_rst_modified_date(d)
                sphinx_build(d, args.update_homepage)
        else:
            # Update modified date if docsrc files have changed
            update_index_rst_modified_date(args.docname)
            sphinx_build(args.docname, args.update_homepage)
    else:  # create
        title = ' '.join(args.title) if args.title else args.docname
        create_new_doc(args.docname, title)

# --- Main ---

enable_args()
