// shell_code_user_state.c - Implementations of functions that work with
// instances of the SHELLCODEUSERSTATE structure
//

#include "stdafx.h"
#include "naraku.h"

#include "shell_code_user_state.h"

///////////////////////////////////////////////////////////////////////////////
// Publicly-exposed functions

///////////////////////////////////////////////////////////////////////////////
// CreateShellCodeUserState function

void CreateShellCodeUserState(LPPSHELLCODEUSERSTATE lppResult,
    void *pShellCode, int nShellCodeBytes, void* pvArgs, void* pvResult) {
  if (lppResult == NULL) {
    return; // Required parameter
  }

  if (pShellCode == NULL) {
    return; // Required parameter
  }

  if (nShellCodeBytes <= 0) {
    return; // Required to be a positive integer only
  }

  // NOTE: The pArgs argument is optional and so is ppResult
  LPSHELLCODEUSERSTATE lpUserState
  = (LPSHELLCODEUSERSTATE) malloc(1 * sizeof(SHELLCODEUSERSTATE));
  if (lpUserState == NULL) {
    fprintf(stderr, "ERROR: Failed to allocate memory.\n");
    exit(EXIT_FAILURE);
  }
  memset(lpUserState, 0, 1 * sizeof(SHELLCODEUSERSTATE));

  lpUserState->nByteCount = nShellCodeBytes;
  lpUserState->pShellCode = pShellCode;
  if (pvArgs != NULL)
    lpUserState->pvArgs = pvArgs;
  if (pvResult != NULL)
    lpUserState->pvResult = pvResult;

  /* Provide the caller with the address of the newly-allocated
   * SHELLOCDEUSERSTATE struct instance */
  *lppResult = lpUserState;
}

///////////////////////////////////////////////////////////////////////////////
// FreeShellCodeUserState function

void FreeShellCodeUserState(LPPSHELLCODEUSERSTATE lppUserState) {
  if (lppUserState == NULL) {
    return; // Required parameter
  }

  if (*lppUserState == NULL) {
    return; // There is nothing to do
  }

  /* Prevent structure member pointers from being double-freed. */
  memset(*lppUserState, 0, sizeof(SHELLCODEUSERSTATE));

  FreeBuffer((void**) lppUserState);
}

///////////////////////////////////////////////////////////////////////////////
// GetArgs function

void* GetShellCodeUserStateArgsPointer(LPSHELLCODEUSERSTATE lpUserState) {
  if (!IsShellCodeUserStateValid(lpUserState)) {
    return NULL;
  }

  return lpUserState->pvArgs;
}

///////////////////////////////////////////////////////////////////////////////
// GetResult function

void* GetShellCodeUserStateResultPointer(LPSHELLCODEUSERSTATE lpUserState) {
  if (!IsShellCodeUserStateValid(lpUserState)) {
    return NULL;
  }

  return lpUserState->pvResult;
}

///////////////////////////////////////////////////////////////////////////////
// GetShellCode function

void* GetShellCodeUserStateShellCodePointer(LPSHELLCODEUSERSTATE lpUserState) {
  if (!IsShellCodeUserStateValid(lpUserState)) {
    return NULL;
  }

  return lpUserState->pShellCode;
}

///////////////////////////////////////////////////////////////////////////////
// GetShellCodeBytes function

int GetShellCodeUserStateByteCount(LPSHELLCODEUSERSTATE lpUserState) {
  if (!IsShellCodeUserStateValid(lpUserState)) {
    return 0;
  }

  return lpUserState->nByteCount;
}

///////////////////////////////////////////////////////////////////////////////
// IsShellCodeUserStateValid function

BOOL IsShellCodeUserStateValid(LPSHELLCODEUSERSTATE lpUserState) {
  if (lpUserState == NULL) {
    return FALSE;
  }

  if (lpUserState->pShellCode == NULL) {
    return FALSE;
  }

  if (lpUserState->nByteCount <= 0) {
    return FALSE;
  }

  return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// SetArgs function

void SetShellCodeUserStateArgsPointer(LPSHELLCODEUSERSTATE lpUserState,
    void* pvArgs) {
  if (!IsShellCodeUserStateValid(lpUserState)) {
    return;
  }

  lpUserState->pvArgs = pvArgs;
}

///////////////////////////////////////////////////////////////////////////////
// SetResult function

void SetShellCodeUserStateResultPointer(LPSHELLCODEUSERSTATE lpUserState,
    void* pvResult) {
  if (!IsShellCodeUserStateValid(lpUserState)) {
    return;
  }

  lpUserState->pvResult = pvResult;
}

///////////////////////////////////////////////////////////////////////////////
// SetShellCode function

void SetShellCodeUserStateShellCodePointer(LPSHELLCODEUSERSTATE lpUserState,
    void* pShellCode) {
  if (!IsShellCodeUserStateValid(lpUserState)) {
    return;
  }

  lpUserState->pShellCode = pShellCode;
}

///////////////////////////////////////////////////////////////////////////////
// SetShellCodeBytes function

void SetShellCodeUserStateByteCount(LPSHELLCODEUSERSTATE lpUserState,
    int nByteCount) {
  if (!IsShellCodeUserStateValid(lpUserState)) {
    return;
  }

  if (nByteCount <= 0) {
    return;
  }

  lpUserState->nByteCount = nByteCount;
}
