/* This is free and unencumbered software released into the public domain. */

#include <cstdio>   /* for std::*printf() */
#include <cstdlib>  /* for EXIT_SUCCESS */
#include <lmdb++.h>

int main() {
  /* Create the LMDB environment: */
  auto env = lmdb::env::create();

  /* Open the LMDB environment: */
  env.open("/tmp");

  /* Begin the LMDB transaction: */
  auto txn = lmdb::txn::begin(env);

  // TODO

  return EXIT_SUCCESS;
}
