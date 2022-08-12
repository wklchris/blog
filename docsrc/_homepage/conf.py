project = 'Homepage'
copyright = '2020, wklchris'
author = 'wklchris'

extensions = [
    'nbsphinx',
    'sphinx.ext.mathjax'
]

language = 'zh_CN'

exclude_patterns = [
    '_build',
    '**.ipynb_checkpoints'
]

smartquotes = False

html_theme = "sphinx_rtd_theme"
html_theme_options = {'canonical_url': "https://wklchris.github.io/blog/"}
templates_path = ['../_templates']

html_static_path = ['../_static']
html_css_files = ['homepage_style.css', "DataTables/datatables.min.css"]
html_js_files = ['load_datatable.js']
