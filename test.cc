/* This is free and unencumbered software released into the public domain. */

#include "lmdb++.h"

#include <cstdlib> /* for EXIT_SUCCESS */

int
main(void) {
  /* Create the LMDB environment: */
  auto env = lmdb::env::create();

  /* Open the LMDB environment: */
  env.open("/tmp");

  /* Begin the LMDB transaction: */
  auto txn = lmdb::txn::begin(env);

  // TODO

  return EXIT_SUCCESS;
}
