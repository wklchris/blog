# Launch Jupyter Notebook in a given project folder
param($projectname)
$notebookdir = "./docsrc/" + $projectname
jupyter notebook --notebook-dir=$notebookdir