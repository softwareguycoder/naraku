// void_shellcode_tests.c - Tests that execute shellcode instructions that
// do not return any value and do not have any parameters.
//

#include "stdafx.h"
#include "kagome.h"

#include "void_shellcode_tests.h"

//////////////////////////////////////////////////////////////////////////////
// Unit tests

BOOL RunShellCode806Test() {
  HTHREAD hAsyncTask =
      ExecShellCode1Async(SHELLCODE_EXAMPLE_806);

  AssertIsFalse("RunShellCode806Test",
      "Failed to start asynchronous shellcode execution task.",
      INVALID_HANDLE_VALUE == hAsyncTask);

  fprintf(stdout,
      "RunShellCode806Test: Waiting on the task to complete...\n");
  WaitThread(hAsyncTask);

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
