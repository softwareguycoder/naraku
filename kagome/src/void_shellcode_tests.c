// void_shellcode_tests.c - Tests that execute shellcode instructions that
// do not return any value and do not have any parameters.
//

#include "stdafx.h"
#include "kagome.h"

#include "void_shellcode_tests.h"

char SHELLCODE_EXAMPLE[] =
    "\x55\x31\xc0\xb8\x25\x00\x00\x00\xbb\xbd\x38\x00\x00\xb9\x09\x00\x00"
    "\x00\xcd\x80\xb8\x01\x00\x00\x00\x31\xdb\xcd\x80";

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
  ExecShellCode1(SHELLCODE_EXAMPLE,
          sizeof(SHELLCODE_EXAMPLE));

  /*AssertIsFalse("RunShellCode806Test",
      "Failed to start asynchronous shellcode execution task.",
      INVALID_HANDLE_VALUE == hAsyncTask);*/

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
