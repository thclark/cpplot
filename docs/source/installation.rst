.. _installation:

============
Installation
============

.. _upgrading_from_previous_versions:

Upgrading From Previous Versions
================================

Please see the note on version stability and backward compatibility :ref:`here <stability>`.


.. _installation_with_cmake:

Installation With Cmake
======================

.. ATTENTION::
    We're working on getting cpplot added as a package in conan-central.
    `Follow the work in progress here. <https://github.com/thclark/cpplot/issues/6>`_
    Until we do that, installation is via cmake.

A cross-platform compilation file is provided using cmake, it's
**not tested on windows** but might actually work, since it uses conan to handle
all the tricky dependencies.

.. code:: bash

    git clone https://github.com/thclark/cpplot
    cd cpplot && cmake . -B build

This process will die first time around, and you'll get a message like:

.. code:: bash

    -- Adding dependencies with conan. Make sure you've called `conan install . --install-folder /Users/you/cpplot/cmake-build-debug`
    CMake Error at CMakeLists.txt:16 (include):
      include could not find load file:
        /Users/you/cpplot/cmake-build-debug/conanbuildinfo.cmake

It'll give you the conan install command to install the third party dependencies. Enter that, run it and re-run cmake.

If you don't have conan installed, its pretty easy to
`get started <https://docs.conan.io/en/latest/introduction.html>`__.


.. _third_party_dependencies:

Third Party Dependencies
========================

The dependencies we use are as follows:

`Eigen <http://eigen.tuxfamily.org/>`__ provides a linear algebra
library. It isn't as consistent with MATLAB's API as armadillo (an
alternative), but the API is very understandable and is used extensively
in the C++ community.

`glog <https://github.com/google/glog>`__ google's asynchronous
logging library, used for logging to file.

`googletest <https://github.com/google/googletest>`__ for unit
testing.

`cpr <https://github.com/whoshuu/cpr>`__ will probably disappear
soon as it's a dependency of some :ref:`old work with plotly online <plotly_online>`.

`json <https://github.com/nlohmann/json>`__ is a fast and popular
json library for C++. Whoever nlohmann is, they rock.

`boost <https://www.boost.org/>`__ is a library of general utilities.
cpplot uses `boost
stacktrace <https://www.boost.org/doc/libs/1_65_1/doc/html/stacktrace/getting_started.html>`__
to provide more helpful errors and `boost filesystem <https://www.boost.org/doc/libs/1_66_0/libs/filesystem/doc/reference.html>`__ utilities to ease the pain
of reading, writing and handling files.

`tbb <https://software.intel.com/content/www/us/en/develop/tools/threading-building-blocks.html>`__
is intel's threading library which allows us to write files out
of the main thread, preventing us from blocking execution.
