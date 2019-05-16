// void_shellcode_tests.c - Tests that execute shellcode instructions that
// do not return any value and do not have any parameters.
//

#include "stdafx.h"
#include "kagome.h"

#include "void_shellcode_tests.h"

//////////////////////////////////////////////////////////////////////////////
// Unit tests

BOOL RunShellCode806Test() {
  ExecShellCode1(SHELLCODE_EXAMPLE_806);
  return TRUE;
}

//////////////////////////////////////////////////////////////////////////////
// Publicly-exposed functions

void RunVoidShellCodeTests() {
  LPTESTSESSION lpSession = NULL;
  StartUnitTestSession(NULL, NULL, &lpSession);

  if (lpSession == NULL) {
    exit( EXIT_FAILURE);
  }

  ExecuteTest(lpSession, "RunShellCode806Test", RunShellCode806Test);

  EndUnitTestSession(&lpSession);
}
