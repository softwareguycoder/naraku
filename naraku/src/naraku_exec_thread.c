// naraku_exec_thread.c - Defines the implementation of functions that
// allow us to support multithreaded (i.e., asynchronous) shellcode execution
//

#include "stdafx.h"
#include "naraku.h"

#include "naraku_exec_thread.h"

//////////////////////////////////////////////////////////////////////////////
// ExecVoidThreadProc fucntion

void *ExecShellCode1AsyncProc(void* pvArgs) {
  if (pvArgs == NULL) {
    return NULL; // Required parameter
  }

  // pvArgs should be a char array of the shell code bytes
  //

  const char* pszShellCode = (const char*)pvArgs;
  if (IsNullOrWhiteSpace(pszShellCode)) {
    return NULL;  // Required parameter; shellcode must not be whitespace
  }

  ((LPSHELLCODE_VOID_ROUTINE)pszShellCode)();

  return NULL;
}
