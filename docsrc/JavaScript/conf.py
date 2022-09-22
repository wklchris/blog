author = "wklchris"
copyright = "wklchris"
exclude_patterns = ['_build', '**.ipynb_checkpoints']
extensions = ['nbsphinx', 'sphinx_copybutton', 'sphinx.ext.mathjax']
html_css_files = ['style.css']
html_static_path = ['../_static']
html_theme = "sphinx_rtd_theme"
html_theme_options = {'canonical_url': 'https://self-contained.github.io/JavaScript/'}
language = "zh_CN"
project = "JavaScript"
smartquotes = False
templates_path = ['../_templates']
today_fmt = "%Y-%m-%d"
year = 2022

rst_prolog = """
.. _ECMA: https://www.ecma-international.org/
"""