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

/**
 * @name PlaceShellCodeInMemory
 * @brief Prepares for executing shellcode by placing the code in the correct
 * location on the heap and then making that region of the heap executable.
 * @param pszShellCode Address of a buffer containing the bytes of shell code
 * to be placed.
 * @param nShellCodeLength Size of the input buffer of shell code, in bytes.
 * @param ppBuf Address of storage that will receive the address in memory
 * of the executable instructions.
 */
void PlaceShellCodeInMemory(const char* pszShellCode, int nShellCodeLength,
    void **ppBuf)
{
  if (nShellCodeLength <= 0) {
    return;
  }

  if (ppBuf == NULL) {
    return;
  }

  void *mem = mmap(0, nShellCodeLength, PROT_READ | PROT_WRITE,
  MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  if (mem == NULL) {
    fprintf(stderr,
        "ERROR: Failed to allocate storage on heap for the shell code.\n");
    exit(EXIT_FAILURE);
  }

  memcpy(mem, pszShellCode, nShellCodeLength);

  if (0 !=
      mprotect(mem, nShellCodeLength, PROT_READ | PROT_WRITE | PROT_EXEC)) {
    fprintf(stderr, "ERROR: Failed to make the heap executable.\n");
    exit(EXIT_FAILURE);
  }

  /* Set the ppBuf pointer to the address of the shellcode from the heap. */
  *ppBuf = mem;
}

void RemoveShellCodeFromMemory(void *pvShellCode, int nShellCodeLength) {
  if (pvShellCode == NULL) {
    return;
  }

  if (nShellCodeLength <= 0) {
    return;
  }

  munmap(pvShellCode, nShellCodeLength);
}

//////////////////////////////////////////////////////////////////////////////
// Publicly-exposed functions

//////////////////////////////////////////////////////////////////////////////
// ExecShellCode1Async function

HTHREAD ExecShellCode1Async(const char* pszShellCode, int nShellCodeLength) {
  if (IsNullOrWhiteSpace(pszShellCode)) {
    return INVALID_HANDLE_VALUE;
  }

  HTHREAD hThread = CreateThreadEx(ExecShellCode1AsyncProc,
      (void*) pszShellCode);

  return hThread;
}

//////////////////////////////////////////////////////////////////////////////
// ExecShellCode1 function

void ExecShellCode1(const char* pszShellCode, int nShellCodeLength) {
  if (IsNullOrWhiteSpace(pszShellCode)) {
    return;
  }

  if (nShellCodeLength <= 0) {
    return;
  }

  void *pShellCode = NULL;

  PlaceShellCodeInMemory(pszShellCode, nShellCodeLength, &pShellCode);

  if (pShellCode == NULL) {
    fprintf(stderr, "ERROR: Failed to place shell code in memory.\n");
    exit(EXIT_FAILURE);
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

  *pnResult = ((LPSHELLCODE_TWOARG_FUNCTION) pszShellCode)(arg1, arg2);
}

//////////////////////////////////////////////////////////////////////////////
