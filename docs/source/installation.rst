.. _installation:

============
Installation
============

.. ATTENTION::
    `We're working on it. I promise. <https://github.com/thclark/cpplot/issues/6>`_

    Until we get conan or vcpkg up and running, installation is via cmake.

.. _upgrading_from_previous_versions:

Upgrading from previous versions
================================

Please see the note on version stability and backward compatibility :ref:`here<_stability>`.


.. _third_party_dependencies:

Third party dependencies
========================

Install and link
----------------

`**Eigen** <http://eigen.tuxfamily.org/>`__ provides a linear algebra
library. It isn't as consistent with MATLAB's API as armadillo (an
alternative), but the API is very understandable and is used extensively
in the C++ community.

`**glog** <https://github.com/google/glog>`__ google's asynchronous
logging library, used for logging to file.

`**googletest** <https://github.com/google/googletest>`__ for unit
testing.


Submodule dependencies
----------------------

We also use `cpr <https://github.com/whoshuu/cpr>`__ and `json <https://github.com/nlohmann/json>`__, which are included as submodule dependencies.

**THIS WILL CHANGE VERY SOON!** But for now, you'll need to clone the repository **and its submodules, cpr and
json,** in order to build it.

.. code:: bash

    git clone --recurse-submodules https://github.com/thclark/cpplot


.. _compilation_with_cmake:

Compilation with cmake
======================

A cross-platform compilation file is provided using cmake, but it's
**not tested on windows**.

PRs to fix or improve it for windows are most welcome.
