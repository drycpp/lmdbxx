******************************
lmdb++: C++11 wrapper for LMDB
******************************

This is a comprehensive C++ wrapper for the LMDB_ embedded database library.

.. _LMDB: http://symas.com/mdb/

Features
========

* Designed to be entirely self-contained as a single ``<lmdb++.h>`` header
  file that can be dropped into a project.
* Implements a straightforward mapping from C to C++, with consistent naming.
* Simplifies error handling by translating error codes into C++ exceptions.
* Carefully differentiates logic errors, runtime errors, and fatal errors.
* Plays nice with others: all symbols are placed in the ``lmdb`` namespace.
* 100% free and unencumbered `public domain <http://unlicense.org/>`_ software,
  usable in any context and for any purpose.

Error Handling
--------------

This wrapper draws a careful distinction between three different classes of
LMDB error conditions:

* **Logic errors**, represented by ``lmdb::logic_error``. Errors of this
  class are thrown due to programming errors where the function interfaces
  are used in violation of documented preconditions. A common strategy for
  handling this class of error conditions is to abort the program with a
  core dump, facilitating introspection to locate and remedy the bug.
* **Fatal errors**, represented by ``lmdb::fatal_error``. Errors of this
  class are thrown due to the exhaustion of critical system resources, in
  particular available memory (``ENOMEM``), or due to attempts to exceed
  applicable system resource limits. A typical strategy for handling this
  class of error conditions is to terminate the program with a descriptive
  error message. More robust programs and shared libraries may wish to
  implement another strategy, such as retrying the operation after first
  letting most of the call stack unwind in order to free up scarce
  resources.
* **Runtime errors**, represented by ``lmdb::runtime_error``. Errors of this
  class are thrown as a matter of course to indicate various exceptional
  conditions. These conditions are generally recoverable, and robust
  programs will take care to correctly handle them.

.. note::

   The distinction between logic errors and runtime errors mirrors that
   found in the C++11 standard library, where the ``<stdexcept>`` header
   defines the standard exception base classes ``std::logic_error`` and
   ``std::runtime_error``. The standard exception class ``std::bad_alloc``,
   on the other hand, is a representative example of a fatal error.

======================== =============================== =======================
Error code               Exception class                 Exception type
======================== =============================== =======================
``MDB_KEYEXIST``         ``lmdb::key_exist_error``       ``lmdb::runtime_error``
``MDB_NOTFOUND``         ``lmdb::not_found_error``       ``lmdb::runtime_error``
``MDB_CORRUPTED``        ``lmdb::corrupted_error``       ``lmdb::fatal_error``
``MDB_PANIC``            ``lmdb::panic_error``           ``lmdb::fatal_error``
(others)                 ``lmdb::runtime_error``         ``lmdb::runtime_error``
======================== =============================== =======================

Elsewhere
=========

Find this project at: GitHub_, Bitbucket_, and SourceForge_.

.. _GitHub:      https://github.com/bendiken/lmdbxx
.. _Bitbucket:   https://bitbucket.org/bendiken/lmdbxx
.. _SourceForge: https://sourceforge.net/projects/lmdbxx/

Author
======

`Arto Bendiken <https://github.com/bendiken>`_ - http://ar.to/

License
=======

This is free and unencumbered public domain software. For more information,
see http://unlicense.org/ or the accompanying ``UNLICENSE`` file.
