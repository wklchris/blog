author = "wklchris"
copyright = "wklchris"
exclude_patterns = ['_build', '**.ipynb_checkpoints']
extensions = ['nbsphinx', 'sphinx_copybutton', 'sphinx.ext.extlinks', 'sphinx.ext.mathjax']
html_css_files = ['style.css']
html_static_path = ['../_static']
html_theme = "sphinx_rtd_theme"
html_theme_options = {'canonical_url': 'https://wklchris.github.io/blog/Sphinx/'}
language = "zh_CN"
project = "Sphinx"
smartquotes = False
templates_path = ['../_templates']
today_fmt = "%Y-%m-%d"
year = 2020

# Customization
rst_epilog = """
.. _Sphinx: https://www.sphinx-doc.org/
.. _Jinja2: https://jinja.palletsprojects.com/
"""

# [sphinx.ext.extlinks]
extlinks = {
   'jinja': ("https://jinja.palletsprojects.com/en/master/templates/#%s", 'Jinja2: ')
}
