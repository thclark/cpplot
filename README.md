# cpplot

> **Work is in progress to refactor this out from other libraries. Watch this space.**

Interactive graphs and charts for C++ 11 upward,
[interactively viewable in-browser using cpplot-viewer](https://cpplot.herokuapp.com).

This library allows you to save figure files (in a *.json form compliant with the `plotly.js` library) to disk
during program execution.


## Why?

For most engineering and scientific applications that come across my desk, it's a case of "prototype in MATLAB or Python, rewrite in C++". But:
 - I'm getting really sick of MATLAB in terms of deployability (there's no CI option to build it, the slug size of the runtime library is 3.7Gb, etc etc).
 - I'm getting really really sick of writing the damn code twice.
 - Most of my engineering and science apps are now getting deployed to cloud services. So displaying natively generated figures in-browser is a nightmare.

What I need is a solution where I can prototype straight into a language which is fast, capable and has a pretty good ecosystem of third party libraries to help me.

Now, with:
 - the great improvements to C++ in the C++11 and 14 standards (which make it much easier to handle threading and generally connect APIs of various libraries together),
 - availability of libraries like Eigen, cpr, ceres-solver, Intel MKL, cxxopts (I could go on and on),
 - great utilities like googletest and Cmake to remove all the old-skool build and test agony...

C++ is really getting there. The one thing missing is a plotting library, which allows me to:
 - quickly and easily prototype new algorithms (visually diagnose what's wrong etc etc)
 - display analysis results on the web
 - produce the same figures on different platforms
 - save publication quality figures easily

In all the other languages I use, I now use `plotly` to do those things. So now it's here for C++ too.


## Viewing Figures

A browser based utility is supplied at [https://cpplot.herokuapp.com](https://cpplot.herokuapp.com).
Navigate to that link and you'll easily be able to view and export the figures created here.

The browser viewer is built in React (using the excellent `react-plotly.js`), is also open-source, free and it
always keeps your data local (files are never uploaded to a server). Find the source
at [https://github.com/thclark/cpplot-viewer](https://github.com/thclark/cpplot-viewer).

**Some example figures to try out with the viewer are included in `/examples`**.

## The Plotly Library

### Plotly figure json specs

At the core of plotly is a set of open specifications for JSON data which can be rendered into various figure types. The various figure classes available here

### Plotly Offline

`Plotly.js` is a javascript library for rendering figures, which can be used offline. This is what's used by the browser viewer.

### Plotly Online

Plotly have a range of online services for collaboration on data grids and figures. You can use their API or tools to take the contents of the files produced here (plotly compliant JSON strings) onto Plotly Online, but how to do that is out of scope here (check their docs).

**HELP WANTED** - I have a branch that's starting to use the Plotly API, which might be the very early beginning of a
client SDK for C++, enabling direct manipulation of online data. However, I have very little appetite for this (I personally don't use plotly online) so collaborators are welcome.


## For Developers

### Style guide

We use the [Google C++ style guide](https://google.github.io/styleguide/cppguide.html) with the following exceptions:
 - Don't care about line width so long as its within reason
 - Use 4 space indenting, not 2 as suggested by the style guide, because we're not [total monsters](https://www.youtube.com/watch?v=SsoOG6ZeyUI) (just kidding xx).

### Threading

Figure write-to-disk is called as an async task, so doesn't block the main computation thread.

This delays program termination when the main program executes quicker than the figure write.
TODO consider creating daemonised threads for writing figures.

### Third party dependencies

We are currently using:

[**Eigen**](http://eigen.tuxfamily.org/) provides a linear algebra library. It isn't as consistent with MATLAB's API as armadillo (an alternative), but the API is very understandable and is used extensively in the C++ community.

[**glog**](https://github.com/google/glog) google's asynchronous logging library, used for logging to file.

[**googletest**](https://github.com/google/googletest) for unit testing.

### Submodule dependencies

You'll need to clone the repository **and its submodules, cpr and json,** in order to build it.
```
git clone --recurse-submodules https://github.com/thclark/cpplot
```

### Third party library installation (OSX)

**ceres-solver which includes eigen and glog dependencies:**
```bash
brew install homebrew/science/ceres-solver
```

### Compilation with cmake

A cross-platform compilation file is provided using cmake, but it's **not tested on windows**.

PRs to fix or improve it for windows are most welcome.
