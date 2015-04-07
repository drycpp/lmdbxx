/* This is free and unencumbered software released into the public domain. */

#ifndef LMDBXX_H
#define LMDBXX_H

/**
 * <lmdb++.h>
 */

#ifndef __cplusplus
#error "<lmdb++.h> requires a C++ compiler"
#endif

////////////////////////////////////////////////////////////////////////////////

#include <lmdb.h>    /* for MDB_*, mdb_*() */

#include <stdexcept> /* for std::runtime_error */

////////////////////////////////////////////////////////////////////////////////
/* Error Handling */

namespace lmdb {
  class error;
  class key_exist_error;
  class not_found_error;
}

/**
 * Base class for LMDB exception conditions.
 */
class lmdb::error : public std::runtime_error {
protected:
  const int _code;

public:
  /**
   * Constructor.
   */
  error(const char* const origin,
        const int rc) noexcept
    : runtime_error{origin},
      _code{rc} {}

  /**
   * Returns the underlying LMDB error code.
   */
  int code() const noexcept {
    return _code;
  }

  /**
   * Returns the origin of the LMDB error.
   */
  const char* origin() const noexcept {
    return runtime_error::what();
  }

  /**
   * Returns the underlying LMDB error code.
   */
  virtual const char* what() const noexcept {
    static thread_local char buffer[1024];
    std::snprintf(buffer, sizeof(buffer),
      "%s: %s", origin(), ::mdb_strerror(code()));
    return buffer;
  }
};

/**
 * Exception class for `MDB_KEYEXIST` errors.
 */
class lmdb::key_exist_error final : public lmdb::error {
public:
  using error::error;
};

/**
 * Exception class for `MDB_NOTFOUND` errors.
 */
class lmdb::not_found_error final : public lmdb::error {
public:
  using error::error;
};

////////////////////////////////////////////////////////////////////////////////

#endif /* LMDBXX_H */
