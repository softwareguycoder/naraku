// naraku.c - Implementations of main library functions
//
// This library depends on the following core libraries:
//
//  - api_core
//  - common_core
//  - threading_core
//

#include "stdafx.h"
#include "naraku.h"

#include "naraku_exec_thread.h"

//////////////////////////////////////////////////////////////////////////////
// Internal-use-only functions

// TODO: Add function implementations here

//////////////////////////////////////////////////////////////////////////////
// Publicly-exposed functions

//////////////////////////////////////////////////////////////////////////////
// ExecShellCode1Async function

HTHREAD ExecShellCode1Async(const char* pszShellCode) {
  if (IsNullOrWhiteSpace(pszShellCode)) {
    return INVALID_HANDLE_VALUE;
  }

  HTHREAD hThread = CreateThreadEx(ExecShellCode1AsyncProc,
      (void*) pszShellCode);

  return hThread;
}

//////////////////////////////////////////////////////////////////////////////
// ExecShellCode1 function

void ExecShellCode1(const char* pszShellCode) {
  if (IsNullOrWhiteSpace(pszShellCode)) {
    return;
  }

  ((LPSHELLCODE_VOID_ROUTINE) pszShellCode)();
}

//////////////////////////////////////////////////////////////////////////////
// ExecShellCode3 function

void ExecShellCode3(const char* pszShellCode, int arg1, int arg2,
    int *pnResult) {
  if (IsNullOrWhiteSpace(pszShellCode)) {
    return;
  }

  if (pnResult == NULL) {
    return;
  }

  *pnResult = ((LPSHELLCODE_TWOARG_FUNCTION)pszShellCode)(arg1, arg2);
}
//////////////////////////////////////////////////////////////////////////////
