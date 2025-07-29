import os
import pandas as pd

DIR = os.path.abspath(os.path.dirname(__file__))
cfop = pd.read_csv(os.path.join(DIR, "CFOP-method.csv"))

def algo_external_link(cfop_type, algo_id):
    text_prefix = 'SpeedCubeDB 链接：'
    if cfop_type == 'PLL':  # algo_id = 'Ja', 'Ra', ...
        algo_url = f"https://speedcubedb.com/a/3x3/PLL/{algo_id}"
        algo_html = f'<a href="{algo_url}">{text_prefix}{cfop_type}-{algo_id}</a>'
        return algo_html

    if cfop_type in ['OLL', 'F2L']:  # algo_id = 1, 2, 3, ...
        algo_domain = "https://speedcubedb.com/a/3x3/"
        algo_prefix = {
            'OLL': "OLL/OLL_",
            'F2L': "F2L/F2L_"
        }
        algo_url = f"{algo_domain}{algo_prefix[cfop_type]}{algo_id}"
        algo_html = f'<a href="{algo_url}">{text_prefix}{cfop_type}-{algo_id}</a>'
        return algo_html
    
    print(f"ERROR: Unknown {cfop_type} (algo: {algo_id})")
    return ''

# Process roofpig
def solution_parser(rubik_solution):
    """Remove parens and insert spaces to solution strings."""
    alg = rubik_solution.replace("(", '').replace(")", '')
    alg = alg.replace("[", '').replace("]", '')
    alg = ' '.join(alg).replace(" 2", "2").replace(" '", "'")
    return alg

def alg_to_roofpig(alg, div_text="", dataconfig_paras=dict(), add_classes=[]):
    paras = {"flags": "", "algdisplay": "2p"}
    paras.update(dataconfig_paras)
    paras_str = '|'.join([k + "=" + v for k, v in paras.items() if v])
    
    dataconfig_str = f"alg={alg}|{paras_str}"
    class_str = ''.join([f" {c}" for c in add_classes])
    div_str = f'<div class="roofpig{class_str}" data-config="{dataconfig_str}">{div_text}</div>'
    return div_str

def process_html(df, type_filter, recommend_primary_algo=True, add_colgroup=True, dataconfig_dict=dict()):
    df = df[df["type"] == type_filter]
    df = df.fillna('')

    html_linebreak = "<br />"
    # Integrate cols: type, id, and alias
    df["id_str"] = df["type"] + '-' + df["id"].astype(str)
    ## Add span id to main algo row
    main_algos = ~df.alias.str.contains("变体")
    df.loc[main_algos, "id_str"] = '<span id="' + df.loc[main_algos, "id_str"] + '">' + df.loc[main_algos, "id_str"] + "</span>"

    df.insert(0, "id_str", df.pop("id_str"))
    df.loc[df["alias"] != '', "id_str"] = df.loc[df["alias"] != '', "id_str"] + html_linebreak + "(" + df.loc[df["alias"] != '', "alias"] + ")"
    
    # Integrate cols: comment & solution, tech, observe
    df.loc[df["comment"] != '', 'comment'] = "<p>" + df.loc[df["comment"] != '', 'comment'] + "</p>"
    df["comment"] = df["comment"] + '<p class="roofpig-algo">' + df["solution"] + "</p>"

    df.loc[df["observe"] != '', 'comment'] = df.loc[df["observe"] != '', 'comment'] + "<p>" + "观察：" + df.loc[df["observe"] != '', 'observe'] + "</p>"
    df.loc[df["tech"] != '', 'comment'] = df.loc[df["tech"] != '', 'comment'] + "<p>" + "手法：" + df.loc[df["tech"] != '', 'tech'] + "</p>"

    # Add external link for algorithms
    if (type_filter == 'PLL'):
        df.loc[main_algos, "comment"] = df.loc[main_algos, "comment"] + df.loc[main_algos, "alias"].apply(
            lambda x: f"<p>{algo_external_link(type_filter, x)}</p>"
        )
    elif (type_filter in ['OLL', 'F2L']):
        df.loc[main_algos, "comment"] = df.loc[main_algos, "comment"] + df.loc[main_algos, "id"].apply(
            lambda x: f"<p>{algo_external_link(type_filter, x)}</p>"
        )

    # Convert solution column to roofpig HTML codes
    ## If recommend, add "recommend" class to standard algos, 
    def _algo_convert(x, **kwargs):
        return alg_to_roofpig(solution_parser(x), dataconfig_paras=dataconfig_dict, **kwargs)
    
    if not recommend_primary_algo:
        df["solution"] = df["solution"].apply(_algo_convert)
    else:
        variant_rows = df.alias.str.contains("变体")
        multi_angle_rows = df.alias.str.contains("多向")

        # Only mutli-angle, not variant
        multi_angle_only_rows = multi_angle_rows & ~variant_rows
        df.loc[multi_angle_only_rows, "solution"] = df.loc[multi_angle_only_rows, "solution"].apply(
            _algo_convert, add_classes=["multi-angle"]
        )

        # Variant, no matter mult-angle or not
        df.loc[variant_rows, "solution"] = df.loc[variant_rows, "solution"].apply(_algo_convert)

        # Recommended: Neither multi-angle nor variant
        recommend_rows = ~(variant_rows | multi_angle_rows)
        df.loc[recommend_rows, "solution"] = df.loc[recommend_rows, "solution"].apply(
            _algo_convert, add_classes=["recommend"]
        )

    df_col_dict = {
        "id_str": "编号",
        "name": "名称",
        "group": "分组",
        "solution": "公式",
        "comment": "注解"
    }
    df = df[[col for col in df_col_dict.keys()]]
    df.rename(columns=df_col_dict, inplace=True)

    html = df.to_html(
        classes="roofpig-table",
        # na_rep='',
        justify='center',
        escape=False,  # Keep HTML syntax for the solution column
        index=False
    )

    # Post-process
    ## Add <colgroup>
    if add_colgroup:
        colgroups = [f'    <col class="rftable_{col}" />' for col in df_col_dict.keys()]
        colgroup_labels = "\n".join(colgroups)
        colgroup_str = "\n".join(["  <colgroup>", colgroup_labels, "  </colgroup>"])
        ## Add it to the second line of the HTML, right after <table>
        firstline, remain = html.split("\n", 1)
        html = "\n".join([firstline, colgroup_str, remain])

    return html

# Main

def main(cfop_filter, dataconfig=dict()):
    html_str = process_html(cfop, cfop_filter, dataconfig_dict=dataconfig)
    with open(os.path.join(DIR, cfop_filter + '.html'), 'w', encoding="utf-8") as f:
        f.write(html_str)


cfop_filters = {
    'PLL': dict(),
    'OLL': {"dataconfig": {"colored": "u"}},
    'F2L': {"dataconfig": {"colored": "u-"}}
}

for filter, arg_dict in cfop_filters.items():
    dc = arg_dict.get("dataconfig", dict()) 
    main(filter, dataconfig=dc)
    print(f'Type "{filter}" updated.')
