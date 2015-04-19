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
* Exception strings include the name of the LMDB function that failed.
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

======================== ================================ ======================
Error code               Exception class                  Exception type
======================== ================================ ======================
``MDB_KEYEXIST``         ``lmdb::key_exist_error``        runtime
``MDB_NOTFOUND``         ``lmdb::not_found_error``        runtime
``MDB_CORRUPTED``        ``lmdb::corrupted_error``        fatal
``MDB_PANIC``            ``lmdb::panic_error``            fatal
``MDB_VERSION_MISMATCH`` ``lmdb::version_mismatch_error`` fatal
``MDB_MAP_FULL``         ``lmdb::map_full_error``         runtime
``MDB_BAD_DBI``          ``lmdb::bad_dbi_error``          runtime
(others)                 ``lmdb::runtime_error``          runtime
======================== ================================ ======================

.. note::

   ``MDB_KEYEXIST`` and ``MDB_NOTFOUND`` are handled specially by some functions.

API Overview
============

Resource Interface
------------------

============================ ===================================================
C handle                     C++ wrapper class
============================ ===================================================
``MDB_env*``                 ``lmdb::env``
``MDB_txn*``                 ``lmdb::txn``
``MDB_dbi``                  ``lmdb::dbi``
``MDB_cursor*``              ``lmdb::cursor``
``MDB_val``                  ``lmdb::val``
============================ ===================================================

Procedural Interface
--------------------

============================ ===================================================
C function                   C++ wrapper function
============================ ===================================================
``mdb_version()``            N/A
``mdb_strerror()``           N/A
``mdb_env_create()``         ``lmdb::env_create()``
``mdb_env_open()``           ``lmdb::env_open()``
``mdb_env_copy()``           N/A
``mdb_env_copyfd()``         N/A
``mdb_env_copy2()``          N/A
``mdb_env_copyfd2()``        N/A
``mdb_env_stat()``           TODO
``mdb_env_info()``           TODO
``mdb_env_sync()``           ``lmdb::env_sync()``
``mdb_env_close()``          ``lmdb::env_close()``
``mdb_env_set_flags()``      ``lmdb::env_set_flags()``
``mdb_env_get_flags()``      TODO
``mdb_env_get_path()``       TODO
``mdb_env_get_fd()``         TODO
``mdb_env_set_mapsize()``    ``lmdb::env_set_map_size()``
``mdb_env_set_maxreaders()`` ``lmdb::env_set_max_readers()``
``mdb_env_get_maxreaders()`` TODO
``mdb_env_set_maxdbs()``     ``lmdb::env_set_max_dbs()``
``mdb_env_get_maxkeysize()`` TODO
``mdb_env_set_userctx()``    TODO
``mdb_env_get_userctx()``    TODO
``mdb_env_set_assert()``     N/A
``mdb_txn_begin()``          ``lmdb::txn_begin()``
``mdb_txn_env()``            ``lmdb::txn_env()``
``mdb_txn_commit()``         ``lmdb::txn_commit()``
``mdb_txn_abort()``          ``lmdb::txn_abort()``
``mdb_txn_reset()``          ``lmdb::txn_reset()``
``mdb_txn_renew()``          ``lmdb::txn_renew()``
``mdb_dbi_open()``           ``lmdb::dbi_open()``
``mdb_stat()``               ``lmdb::dbi_stat()``
``mdb_dbi_flags()``          ``lmdb::dbi_flags()``
``mdb_dbi_close()``          ``lmdb::dbi_close()``
``mdb_drop()``               ``lmdb::dbi_drop()``
``mdb_set_compare()``        ``lmdb::dbi_set_compare()``
``mdb_set_dupsort()``        ``lmdb::dbi_set_dupsort()``
``mdb_set_relfunc()``        ``lmdb::dbi_set_relfunc()``
``mdb_set_relctx()``         ``lmdb::dbi_set_relctx()``
``mdb_get()``                ``lmdb::dbi_get()``
``mdb_put()``                ``lmdb::dbi_put()``
``mdb_del()``                ``lmdb::dbi_del()``
``mdb_cursor_open()``        ``lmdb::cursor_open()``
``mdb_cursor_close()``       ``lmdb::cursor_close()``
``mdb_cursor_renew()``       ``lmdb::cursor_renew()``
``mdb_cursor_txn()``         ``lmdb::cursor_txn()``
``mdb_cursor_dbi()``         ``lmdb::cursor_dbi()``
``mdb_cursor_get()``         ``lmdb::cursor_get()``
``mdb_cursor_put()``         ``lmdb::cursor_put()``
``mdb_cursor_del()``         ``lmdb::cursor_del()``
``mdb_cursor_count()``       ``lmdb::cursor_count()``
``mdb_cmp()``                N/A
``mdb_dcmp()``               N/A
``mdb_reader_list()``        TODO
``mdb_reader_check()``       TODO
============================ ===================================================

Caveats
-------

* The C++ procedural interface is more strictly grouped by handle type than
  the LMDB native interface. For instance, ``mdb_put()`` is wrapped as the
  C++ function ``lmdb::dbi_put()``, not ``lmdb::put()``. These differences--
  a handful in number--all concern operations on ``MDB_dbi`` handles.

* ``lmdb::dbi_put()`` does not throw an exception if LMDB returns the
  ``MDB_KEYEXIST`` error code; it instead just returns ``false``.

* ``lmdb::dbi_get()`, ``lmdb::dbi_del()``, and ``lmdb::cursor_get()`` do not
  throw an exception if LMDB returns the ``MDB_NOTFOUND`` error code; they
  instead just return ``false``.

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
