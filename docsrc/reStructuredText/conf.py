author = "wklchris"
copyright = "wklchris"
exclude_patterns = ['_build', '**.ipynb_checkpoints']
extensions = ['sphinx_copybutton', 'sphinx.ext.extlinks', 'sphinx.ext.mathjax']
html_css_files = ['style.css']
html_static_path = ['../_static']
html_theme = "sphinx_rtd_theme"
html_theme_options = {'canonical_url': 'https://wklchris.github.io/blog/reStructuredText/'}
language = "zh_CN"
project = "reStructuredText 简介"
smartquotes = False
templates_path = ['../_templates']
today_fmt = "%Y-%m-%d"
year = 2020

# -- Customization ---

# [sphinx.ext.extlinks]
extlinks = {
   'docutils': ("https://docutils.sourceforge.io/docs/ref/rst/restructuredtext.html#%s", 'Docutils: %s'),
   'docutils-directive': ("https://docutils.sourceforge.io/docs/ref/rst/directives.html#%s", 'Directive: %s')
}

# Others
highlight_language = 'none'
numfig = True

mathjax3_config = {
   'tex': {'tags': 'ams'}
}


rst_prolog = """
.. math::

   \\newcommand{\\ud}{\\mathop{}\\negthinspace\mathrm{d}}
   \\newcommand{\\pfrac}[2][x]{\\frac{\\partial #2}{\\partial #1}}

.. |section-symbols| replace:: 
   ! " # $ % & ' ( ) * + , - . / : ; < = > ? @ [ \ ] ^ _ ` { | } ~
"""