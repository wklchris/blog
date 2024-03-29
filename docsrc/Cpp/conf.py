author = "wklchris"
copyright = "wklchris"
exclude_patterns = ['_build', '**.ipynb_checkpoints']
extensions = ['sphinx_copybutton', 'sphinx.ext.extlinks', 'sphinx.ext.mathjax']
html_css_files = ['style.css']
html_static_path = ['../_static']
html_theme = "sphinx_rtd_theme"
html_theme_options = {'canonical_url': 'https://self-contained.github.io/Cpp/'}
language = "zh_CN"
project = "Cpp"
smartquotes = False
templates_path = ['../_templates']
today_fmt = "%Y-%m-%d"
year = 2024

rst_prolog = """
.. role:: strike
.. role:: uline
.. role:: underover
.. role:: box
.. role:: xsmall
.. role:: hlred
.. role:: hlyellow
.. role:: hlgreen
.. role:: hlblue

.. role:: cpp
   :class: cpp hlblue xsmall
   
.. |cpp11| replace::
   :cpp:`C++ 11`
"""