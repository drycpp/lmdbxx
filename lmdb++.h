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
   * Throws an error based on the given LMDB return code.
   */
  [[noreturn]] static inline void raise(const char* origin, int rc);

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

inline void
lmdb::error::raise(const char* const origin,
                   const int rc) {
  switch (rc) {
    case MDB_KEYEXIST: throw key_exist_error{origin, rc};
    case MDB_NOTFOUND: throw not_found_error{origin, rc};
    default: throw error{origin, rc};
  }
}

////////////////////////////////////////////////////////////////////////////////
/* Procedural Interface */

namespace lmdb {
  static inline void env_create(MDB_env** env);
  static inline void env_open(MDB_env* env,
    const char* path, unsigned int flags, mdb_mode_t mode);
  static inline void env_close(MDB_env* env);
}

/**
 * @throws lmdb::error on failure
 */
static inline void
lmdb::env_create(MDB_env** env) {
  const int rc = ::mdb_env_create(env);
  if (rc != MDB_SUCCESS) {
    error::raise("mdb_env_create", rc);
  }
}

/**
 * @throws lmdb::error on failure
 */
static inline void
lmdb::env_open(MDB_env* env,
               const char* const path,
               const unsigned int flags,
               const mdb_mode_t mode) {
  const int rc = ::mdb_env_open(env, path, flags, mode);
  if (rc != MDB_SUCCESS) {
    error::raise("mdb_env_open", rc);
  }
}

/**
 * @note never throws an exception
 */
static inline void
lmdb::env_close(MDB_env* env) {
  ::mdb_env_close(env);
}

////////////////////////////////////////////////////////////////////////////////

#endif /* LMDBXX_H */
