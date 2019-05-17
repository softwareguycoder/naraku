// twoarg_shellcode_tests.c - Defines the implementations of tests that exer-
// cise the two-argument shellcode functionality.
//

#include "stdafx.h"
#include "kagome.h"

#include "twoarg_shellcode_tests.h"

//////////////////////////////////////////////////////////////////////////////
// Unit tests

//////////////////////////////////////////////////////////////////////////////
// TestTwoArgumentShellCodeWithIntegerResult test

BOOL TestTwoArgumentShellCodeWithIntegerResult() {
  int x = VALUE_ONE;
  int y = VALUE_TWO;

  int result = 0;

  printf("x = %d\ny = %d\nExpected sum: %d\n", x, y, EXPECTED_SUM);

  ExecShellCode3(SHELLCODE_EXAMPLE_001,
      x, y, &result);

  printf("result = %d\n", result);

  return result == EXPECTED_SUM;
}

//////////////////////////////////////////////////////////////////////////////
// Publicly-exposed functions

void RunTwoArgShellcodeTests() {
  LPTESTSESSION lpSession = NULL;
  StartUnitTestSession(NULL, NULL, &lpSession);

  if (lpSession == NULL) {
    exit( EXIT_FAILURE);
  }

  ExecuteTest(lpSession, "TestTwoArgumentShellCodeWithIntegerResult",
      TestTwoArgumentShellCodeWithIntegerResult);

  EndUnitTestSession(&lpSession);
}
