// Feature tests of dynamic checking in Checked C
//
// The following lines are for the LLVM test harness:
//
// RUN: %clang -fcheckedc-extension -Xclang -verify -o %t.exe %s
// RUN: %t.exe

#include <stdbool.h>
#include <signal.h>
#include <stdlib.h>
#include "../../../include/stdchecked.h"

void handle_error(int err) {
  _Exit(0);
}

int main(void) {
  // Currently the Checked C clang implementation raises a SIGILL when a
  // dynamic check fails.  This may change in the future.
  signal(SIGILL, handle_error);

  // This is expected fail at runtime. It is simple enough for clang to issue a warning
  dynamic_check(false); // expected-warning {{dynamic check will always fail}}

  return 1;
}