[![pre-commit](https://img.shields.io/badge/pre--commit-enabled-brightgreen?logo=pre-commit&logoColor=white)](https://github.com/pre-commit/pre-commit)
[![black-girls-code](https://img.shields.io/badge/black%20girls-code-f64279.svg)](https://www.blackgirlscode.com/)


# cpplot

Interactive graphs and charts for C++ 11 upward,
[viewable in-browser using cpplot-viewer](https://cpplot.herokuapp.com).

Full documentation is at [https://cpplot.readthedocs.io](https://cpplot.readthedocs.io)




## For Developers

You should only need to read the following if you plan to develop on `cpplot`.

### Style guide

We use the [Google C++ style guide](https://google.github.io/styleguide/cppguide.html) with the following exceptions:
 - Don't care about line width so long as its within reason
 - Use 4 space indenting, not 2 as suggested by the style guide, because we're not [total monsters](https://www.youtube.com/watch?v=SsoOG6ZeyUI) (just kidding xx).

### Pre-Commit

You need to install pre-commit to get the hooks working. Do:
```
pip install pre-commit
pre-commit install
```

Once that's done, each time you make a commit, the following checks are made:

- valid github repo and files
- code style
- documentation builds correctly

Upon failure, the commit will halt. **Re-running the commit will automatically fix most issues** except:
- You'll have to fix documentation yourself prior to a successful commit (there's no auto fix for that!!).

You can run pre-commit hooks without making a commit, like:
```
pre-commit run build-docs
```
which is useful to locally build documents without crazy efforts setting up an environment for sphinx.


### Compilation with cmake

A cross-platform compilation file is provided using cmake, but it's **not tested on windows**.

PRs to fix or improve it for windows are most welcome.
