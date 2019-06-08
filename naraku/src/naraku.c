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

//////////////////////////////////////////////////////////////////////////////
// Publicly-exposed functions

//////////////////////////////////////////////////////////////////////////////
// ExecShellCode1Async function

HTHREAD ExecShellCode1Async(const void* pvShellCode, int nShellCodeLength,
    void** ppShellCodeBytes) {
  if (pvShellCode == NULL) {
    return INVALID_HANDLE_VALUE;
  }

  if (nShellCodeLength <= 0) {
    return INVALID_HANDLE_VALUE;
  }

  if (ppShellCodeBytes == NULL) {
    return INVALID_HANDLE_VALUE;
  }

  void *pShellCode = NULL;

  PlaceShellCodeInMemory(pvShellCode, nShellCodeLength, &pShellCode);

  if (pShellCode == NULL) {
    fprintf(stderr, FAILED_ALLOC_SHELL_CORE_SPACE);
    exit(EXIT_FAILURE);
  }

  *ppShellCodeBytes = pShellCode;

  HTHREAD hThread = CreateThreadEx(ExecShellCode1AsyncProc,
      (void*) pShellCode);

  return hThread;
}

HTHREAD ExecShellCode2Async(const void* pvShellCode, int nShellCodeLength,
    int nArg1, void** ppShellCodeBytes) {
  if (pvShellCode == NULL) {
    return INVALID_HANDLE_VALUE;
  }

  if (nShellCodeLength <= 0) {
    return INVALID_HANDLE_VALUE;
  }

  if (ppShellCodeBytes == NULL) {
    return INVALID_HANDLE_VALUE;
  }

  void *pShellCode = NULL;

  PlaceShellCodeInMemory(pvShellCode, nShellCodeLength, &pShellCode);

  if (pShellCode == NULL) {
    fprintf(stderr, FAILED_ALLOC_SHELL_CORE_SPACE);
    exit(EXIT_FAILURE);
  }

  *ppShellCodeBytes = pShellCode;

  LPSHELLCODEUSERSTATE lpUserState = NULL;

  /* Create an instance of SHELLCODEUSERSTATE to pass to the thread.
   * Notice that we do not marshal the pShellCode pointer across the thread
   * boundary because the PlaceShellCodeInMemory function, who filled it with
   * an address, did so with an address of memory already allocated on the
   * global heap, which all threads can see. */
  CreateShellCodeUserState(&lpUserState, pShellCode,
      nShellCodeLength, MarshalInt(nArg1), NULL);

  HTHREAD hThread = CreateThreadEx(ExecShellCode2AsyncProc,
      (void*)lpUserState);

  return hThread;
}

//////////////////////////////////////////////////////////////////////////////
// ExecShellCode1 function

void ExecShellCode1(const void* pvShellCode, int nShellCodeLength) {
  if (pvShellCode == NULL) {
    return;
  }

  if (nShellCodeLength <= 0) {
    return;
  }

  void *pShellCode = NULL;

  PlaceShellCodeInMemory(pvShellCode, nShellCodeLength, &pShellCode);

  if (pShellCode == NULL) {
    fprintf(stderr, FAILED_ALLOC_SHELL_CORE_SPACE);
    exit(EXIT_FAILURE);
  }

  ((LPSHELLCODE_VOID_ROUTINE) pShellCode)();

  RemoveShellCodeFromMemory(pShellCode, nShellCodeLength);
}

///////////////////////////////////////////////////////////////////////////////
// ExecShellCode2 function

void ExecShellCode2(const void* pvShellCode, int nShellCodeLength,
    int nArg1, int *pnResult) {
  if (pvShellCode == NULL) {
    return; // Required parameter
  }

  if (nShellCodeLength <= 0) {
    return; // Required parameter
  }

  if (pnResult == NULL) {
    return; // Required parameter
  }

  void *pShellCode = NULL;

  PlaceShellCodeInMemory(pvShellCode, nShellCodeLength, &pShellCode);

  if (pShellCode == NULL) {
    fprintf(stderr, FAILED_ALLOC_SHELL_CORE_SPACE);
    exit(EXIT_FAILURE);
  }

  /* GCC, with the options with which this library is compiled, utilizes
   * the 64-Bit x86-64 C Calling Convention, which puts the address of the
   * shellcode into RAX, and the nArg1 value into RDI prior to doing a
   * CALL RAX instruction.  So, shellcode invoked with this function needs
   * to look in RDI for the value of the nArg1 variable used here.
   */
  *pnResult = ((LPSHELLCODE_ONEARG_FUNCTION) pShellCode)(nArg1);

  RemoveShellCodeFromMemory(pShellCode, nShellCodeLength);
}

///////////////////////////////////////////////////////////////////////////////
// ExecShellCode3 function

void ExecShellCode3(const void* pvShellCode, int nShellCodeLength,
    int nArg1, int nArg2, int *pnResult) {
  if (pvShellCode == NULL) {
    return; // Required parameter
  }

  if (nShellCodeLength <= 0) {
    return; // Required parameter
  }

  if (pnResult == NULL) {
    return; // Required parameter
  }

  void *pShellCode = NULL;

  PlaceShellCodeInMemory(pvShellCode, nShellCodeLength, &pShellCode);

  if (pShellCode == NULL) {
    fprintf(stderr, FAILED_ALLOC_SHELL_CORE_SPACE);
    exit(EXIT_FAILURE);
  }

  /* GCC, with the options with which this library is compiled, utilizes
     * the 64-Bit x86-64 C Calling Convention, which puts the address of the
     * shellcode into RAX, and the nArg1 value into RDI and the value of nArg2
     * into RSI prior to doing a CALL RAX instruction.  So, shellcode
     * invoked with this function needs to look in RDI for the value of
     * the nArg1 variable used here.
     */
  *pnResult = ((LPSHELLCODE_TWOARG_FUNCTION) pShellCode)(nArg1, nArg2);

  RemoveShellCodeFromMemory(pShellCode, nShellCodeLength);
}

//////////////////////////////////////////////////////////////////////////////
// PlaceShellCodeInMemory function

void PlaceShellCodeInMemory(const void* pvShellCode,
    int nShellCodeLength, void **ppBuf)
{
  if (nShellCodeLength <= 0) {
    return;
  }

  if (ppBuf == NULL) {
    return;
  }

  const int PAGE_SIZE = 4096;

  /* Allocate a buffer aligned on a page boundary;
   initial protection is PROT_READ | PROT_WRITE */

  void *mem = aligned_alloc(PAGE_SIZE, 4 * PAGE_SIZE);
  if (mem == NULL) {
    fprintf(stderr,
    FAILED_ALLOC_SHELL_CORE_SPACE);
    exit(EXIT_FAILURE);
  }
  memset(mem, 0, 4 * PAGE_SIZE);

  memcpy(mem, pvShellCode, nShellCodeLength);

  if (0 !=
      mprotect(mem, nShellCodeLength, PROT_READ | PROT_WRITE | PROT_EXEC)) {
    fprintf(stderr, "ERROR: Failed to make the heap executable.\n");
    exit(EXIT_FAILURE);
  }

  /* Set the ppBuf pointer to the address of the shellcode from the heap. */
  *ppBuf = mem;
}

//////////////////////////////////////////////////////////////////////////////
// RemoveShellCodeFromMemory function

void RemoveShellCodeFromMemory(void *pvShellCode, int nShellCodeLength) {
  if (pvShellCode == NULL) {
    return;
  }

  if (nShellCodeLength <= 0) {
    return;
  }

  munmap(pvShellCode, nShellCodeLength);
}
