author = "wklchris"
copyright = "wklchris"
exclude_patterns = ['_build', '**.ipynb_checkpoints']
extensions = [
    'sphinx_copybutton',
    'sphinx.ext.mathjax',
    'sphinx.ext.extlinks'
]
html_css_files = ['style.css', 'roofpig.css']
html_js_files = ['jquery.js', 'roofpig_and_three.min.js']
html_static_path = ['_static', '../_static']
html_theme = "sphinx_rtd_theme"
html_theme_options = {'canonical_url': 'https://wklchris.github.io/Rubik/'}
language = "zh_CN"
project = "魔方"
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
    # If alg links are changed, also update function `algo_external_link` in CFOPtable.py
   'alg': ("https://speedcubedb.com/a/3x3/%s", 'SpeedCubeDB: %s'),
   'alg-pll': ("https://speedcubedb.com/a/3x3/PLL/%s", 'SpeedCubeDB: PLL %s'),
   'alg-oll': ("https://speedcubedb.com/a/3x3/OLL/%s", 'SpeedCubeDB: OLL %s'),
   'alg-f2l': ("https://speedcubedb.com/a/3x3/F2L/%s", 'SpeedCubeDB: F2L %s'),
   # Other links
   'speedsolving': ("https://www.speedsolving.com/wiki/index.php/%s", 'Speedsolving Wiki: %s'),
   'jperm': ("https://jperm.net/algs/%s", 'Jperm.net: %s')
}
