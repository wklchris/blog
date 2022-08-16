author = "wklchris"
copyright = "wklchris"
exclude_patterns = ['_build', '**.ipynb_checkpoints']
extensions = ['nbsphinx', 'sphinx_copybutton', 'sphinx.ext.mathjax', 'sphinx.ext.extlinks']
html_css_files = ['style.css', 'roofpig.css']
html_js_files = ['roofpig_and_three.min.js']
html_static_path = ['_static', '../_static']
html_theme = "sphinx_rtd_theme"
html_theme_options = {'canonical_url': 'https://wklchris.github.io/Rubik/'}
language = "zh_CN"
project = "Rubik"
smartquotes = False
templates_path = ['../_templates']
today_fmt = "%Y-%m-%d"
year = 2022

rst_prolog = """
.. _csTimer: https://cstimer.net/
.. _WCA: https://www.worldcubeassociation.org
"""

# sphinx.ext.extlinks
extlinks = {
   'algdb': ("http://algdb.net/puzzle/333/%s", 'AlgDB: %s'),
   'algdb-pll': ("http://algdb.net/puzzle/333/pll/%s", 'AlgDB: PLL '),
   'algdb-oll': ("http://algdb.net/puzzle/333/oll/%s", 'AlgDB: OLL '),
   'speedsolving': ("https://www.speedsolving.com/wiki/index.php/%s", 'Speedsolving Wiki: '),
   'jperm': ("https://jperm.net/algs/%s", 'Jperm.net: ')
}
