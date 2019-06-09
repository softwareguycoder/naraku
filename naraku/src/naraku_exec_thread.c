// naraku_exec_thread.c - Defines the implementation of functions that
// allow us to support multithreaded (i.e., asynchronous) shellcode execution
//

#include "stdafx.h"
#include "naraku.h"

#include "naraku_exec_thread.h"
#include "shell_code_user_state.h"

#define RESULT_ARRAY_SIZE 2

//////////////////////////////////////////////////////////////////////////////
// ExecShellCode1AsyncProc fucntion

void *ExecShellCode1AsyncProc(void* pvShellCodeUserState) {
  if (pvShellCodeUserState == NULL) {
    return NULL; // Required parameter
  }

  LPSHELLCODEUSERSTATE lpUserState =
      (LPSHELLCODEUSERSTATE) pvShellCodeUserState;
  if (!IsShellCodeUserStateValid(lpUserState)) {
    return NULL;  // Required to have valid info in it
  }

  void *pShellCode = GetShellCodeUserStateShellCodePointer(lpUserState);
  if (pShellCode == NULL) {
    return NULL;  // No shell code to run
  }

  ((LPSHELLCODE_VOID_ROUTINE) pShellCode)();
  if (pShellCode == NULL) {
    return NULL; // Required parameter
  }

  return NULL;
}

//////////////////////////////////////////////////////////////////////////////
// ExecShellCode2AsyncProc fucntion

void *ExecShellCode2AsyncProc(void* pvShellCodeUserState) {
  if (pvShellCodeUserState == NULL) {
    return NULL; // Required parameter
  }

  LPSHELLCODEUSERSTATE lpUserState =
      (LPSHELLCODEUSERSTATE) pvShellCodeUserState;
  if (!IsShellCodeUserStateValid(lpUserState)) {
    return NULL;  // Required to have valid info in it
  }

  void *pShellCode = GetShellCodeUserStateShellCodePointer(lpUserState);
  if (pShellCode == NULL) {
    return NULL; // Required parameter
  }

  // In this case, we expect the pArg member to be the address of an
  // integer argument to pass to the shellcode.  Likewise, we expect the
  // shell code to return an integer argument.  In this case, the ppResult
  // member will be set to the address of the value returned.
  void* pvArgs = GetShellCodeUserStateArgsPointer(lpUserState);
  if (pvArgs == NULL) {
    return NULL;  // Required value
  }

  int nArg1 = INT_MIN;

  DeMarshalBlockFromThread((void*)&nArg1, pvArgs, 1 * sizeof(int));

  // Marshal the result of the shellcode back over the thread boundary --
  // this is because the shellcode function execution operation causes the
  // compiler to output the opcodes for retrieving the return value and
  // placing it on the local stack frame of this thread.  We need the calling
  // thread to have access to this value, so we have to marshal it across
  // the thread boundary with the help of the global heap.
  SHELLCODERESULTS shellCodeResults = {0};

  // If the return value is anything other than zero, then the
  // syscall man page says that the return code in EAX is -1 times the
  // corresponding ERRNO value.  If the value in EAX is zero, then the
  // corresponding ERRNO value is usually zero as well.  Since -1*0 == 0,
  // we are good to go just multiplying the result of the shellcode call
  // times -1.
  shellCodeResults.nSyscallReturnValue =
      ((LPSHELLCODE_ONEARG_FUNCTION) pShellCode)(nArg1);
  shellCodeResults.nErrnoValue = -1*(shellCodeResults.nSyscallReturnValue);

  void* pvShellCodeResults = MarshalBlockToThread(&shellCodeResults,
      sizeof(SHELLCODERESULTS));

  SetShellCodeUserStateResultPointer(lpUserState, pvShellCodeResults);

  /* remember to free the result pointer! this is
   usually done when it is demarshaled. */

  return lpUserState;
}
