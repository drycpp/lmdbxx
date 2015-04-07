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

namespace lmdb {
  class error;
}

////////////////////////////////////////////////////////////////////////////////
/* lmdb::error */

/**
 * LMDB exception class.
 */
class lmdb::error final : public std::runtime_error {
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
    std::snprintf(buffer, sizeof(buffer), "%s: %s", origin(), ::mdb_strerror(code()));
    return buffer;
  }
};

////////////////////////////////////////////////////////////////////////////////

#endif /* LMDBXX_H */
