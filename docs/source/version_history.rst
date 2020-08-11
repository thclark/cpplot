.. _version_history:

===============
Version History
===============

.. _origins:

Origins
=======

This library was hacked together / extracted from other repositories such as `the es-flow library <https://es-flow.readthedocs.io/en/latest/>`__ due to the
need for a plotting library enabling me to deliver results over the web.

As more stars are being added on GitHub (14 at the time of writing, woot woot!) it's now worth properly versioning
and maintaining the effort, since it seems like it's useful to more people than just me.

.. _stability:

Stability
=========

The library uses semver versioning, like `version x.y.z`.

Theoretically, only `x` increments should break backward compatibility. But, it's still early days as noted in
`issue 10 <https://github.com/thclark/cpplot/issues/10>`__ and I don't want to end up on version 200.4.5 in
the next five minutes...

**Let's be pragmatic:** whilst still on version `0.0.z` please consider the API as unstable
version-to-version (z increments). This is because I (or we -
`please help <https://github.com/thclark/cpplot/issues/10>`_!) will be still architecting the library sensibly.

**When I break it, I'll at least tell you what's breaking! Check back here as you update.**

For `versions >= 0.x.y` expect `y` increments not to break, breaking changes might occur on `x` increments.

For `versions >= x.y.z` where `x >= 1` expect `x` increments to break backward compatibility.


.. _version_0.0.1:

0.0.1
=====

Initial version applied to the library

New Features
------------
#. Documentation in RestructuredText and hooked for public viewing on `readthedocs <https://cpplot.readthedocs.io>`__.
#. Pre-commit hooks added to ensure docs always build (whatever commit you're at) and to apply consistent file formats.
#. Implemented semver versioning system which will be done with GitHub releases.

Backward Incompatible API Changes
---------------------------------
#. n/a (Initial release)

Bug Fixes & Minor Changes
-------------------------
#. n/a (Initial Release)


.. _version_0.0.2:

0.0.2
=====

Updated build system to use conan for third party dependencies

New Features
------------
#. Documentation updated with a correct installation method
#. Conan package manager built into cmake for easier dependency management
#. Huge amount of custom cmake code (there to find and cope with third party deps removed)

Backward Incompatible API Changes
---------------------------------
#. No API changes
#. Build systems updated; now requires conan.

Bug Fixes & Minor Changes
-------------------------
#. n/a (Initial Release)


0.0.3
=====

Minor fixes to build system and docs

New Features
------------
#. n/a

Backward Incompatible API Changes
---------------------------------
#. n/a

Bug Fixes & Minor Changes
-------------------------
#. Fix for building against glog on windows
#. Corrected build instructions in documentation


0.0.4
=====

Removed unused cpr dependency from build system

New Features
------------
#. n/a

Backward Incompatible API Changes
---------------------------------
#. n/a

Bug Fixes & Minor Changes
-------------------------
#. Removed unused cpr dependency from build system
#. Updated docs to reflect the removed dep and to close #17
#. Added a branch naming rule to the git pre-commit
