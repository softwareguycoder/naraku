// void_shellcode_tests.c - Tests that execute shellcode instructions that
// do not return any value and do not have any parameters.
//

#include "stdafx.h"
#include "kagome.h"

#include "void_shellcode_tests.h"

char SHELLCODE_EXAMPLE_806[] =
  "\x31\xc0\x48\xbb\xd1\x9d\x96\x91\xd0\x8c\x97\xff\x48\xf7\xdb\x53\x54\x5f" \
  "\x99\x52\x57\x54\x5e\xb0\x3b\x0f\x05";

HTHREAD hAsyncTask = INVALID_HANDLE_VALUE;

//////////////////////////////////////////////////////////////////////////////
// TearDown function

void VoidShellCodeTestTearDown() {
  WaitThread(hAsyncTask);
  DestroyThread(hAsyncTask);
}

//////////////////////////////////////////////////////////////////////////////
// Unit tests

//////////////////////////////////////////////////////////////////////////////
// RunShellCode806Test test

BOOL RunShellCode806Test() {
  hAsyncTask =
      ExecShellCode1Async(SHELLCODE_EXAMPLE_806,
          sizeof(SHELLCODE_EXAMPLE_806));

  AssertIsFalse("RunShellCode806Test",
      "Failed to start asynchronous shellcode execution task.",
      INVALID_HANDLE_VALUE == hAsyncTask);

  return TRUE;
}

//////////////////////////////////////////////////////////////////////////////
// Publicly-exposed functions

void RunVoidShellCodeTests() {
  LPTESTSESSION lpSession = NULL;
  StartUnitTestSession(NULL,
      VoidShellCodeTestTearDown, &lpSession);

  if (lpSession == NULL) {
    exit( EXIT_FAILURE);
  }

  ExecuteTest(lpSession, "RunShellCode806Test", RunShellCode806Test);

  EndUnitTestSession(&lpSession);
}
