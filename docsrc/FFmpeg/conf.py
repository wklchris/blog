author = "wklchris"
copyright = "wklchris"
exclude_patterns = ['_build', '**.ipynb_checkpoints']
extensions = [
    'sphinx_copybutton',
    'sphinx.ext.extlinks',
    'sphinx.ext.mathjax'
]
html_css_files = ['style.css']
html_static_path = ['../_static']
html_theme = "sphinx_rtd_theme"
html_theme_options = {'canonical_url': "https://wklchris.github.io/blog/FFmpeg/"}
language = "zh_CN"
project = "FFmpeg 教程"
smartquotes = False
templates_path = ['../_templates']
today_fmt = "%Y-%m-%d"
year = 2020

# sphinx.ext.extlinks
extlinks = {
    'all': ("http://ffmpeg.org/ffmpeg-all.html#%s", '%s'),
    'filter': ("https://ffmpeg.org/ffmpeg-filters.html#%s", '%s'),
    'wiki': ("https://trac.ffmpeg.org/wiki/%s", '%s'),
    'encode': ("https://trac.ffmpeg.org/wiki/Encode/%s", '%s')
}