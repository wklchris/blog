author = "wklchris"
copyright = "wklchris"
exclude_patterns = ['_build', '**.ipynb_checkpoints']
extensions = ['sphinx_copybutton', 'sphinx.ext.extlinks', 'sphinx.ext.mathjax', 'nbsphinx']
html_css_files = ['style.css']
html_static_path = ['../_static']
html_theme = "sphinx_rtd_theme"
html_theme_options = {'canonical_url': 'https://self-contained.github.io/Optimization/'}
language = "zh_CN"
project = "Optimization"
smartquotes = False
templates_path = ['../_templates']
today_fmt = "%Y-%m-%d"
year = 2024
rst_prolog = """
.. role:: box
.. role:: strike
.. role:: uline
.. role:: underover
.. role:: xsmall
.. role:: hlred
.. role:: hlyellow
.. role:: hlgreen
.. role:: hlblue
"""
rst_epilog = """
.. _Cbc: https://github.com/coin-or/Cbc
.. _Clp: https://github.com/coin-or/Clp
.. _Coin-OR: https://www.coin-or.org/
.. _COPT: https://www.shanshu.ai/copt/
.. _CPLEX: https://www.ibm.com/products/ilog-cplex-optimization-studio/cplex-optimizer
.. _cvxpy: https://www.cvxpy.org/
.. _Gurobi: https://www.gurobi.com/
.. _Ipopt: https://github.com/coin-or/Ipopt
.. _MOSEK: https://www.mosek.com/
.. _OR-Tools: https://github.com/google/or-tools
.. _Pyomo: https://pyomo.readthedocs.io/en/stable/
.. _SCIP: https://scipopt.org/
.. _Xpress: https://www.fico.com/en/products/fico-xpress-optimization
"""