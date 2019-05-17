// naraku.h - Interface to the Naraku library
//

#ifndef __NARAKU_H__
#define __NARAKU_H__

#include "stdafx.h"

/**
 * @brief Function signature template for a shellcode function that takes
 * no arguments and returns nothing.
 */
typedef void (*LPSHELLCODE_VOID_ROUTINE)(void);

/**
 * @brief Function signature template for a shellcode function that takes
 * two integer arguments and returns an integer result.
 * @param arg1 First argument to pass to the shellcode.
 * @param arg2 Second argument to pass to the shellcode.
 * @return Result of the function (value in EAX).
 */
typedef int (*LPSHELLCODE_TWOARG_FUNCTION)(int arg1, int arg2);

/**
 * @name ExecShellCode1Async
 * @brief Executes shellcode that does not ask for parameters and does not
 * return an argument.  Launches a separate thread of execution in which to
 * execute the shellcode.
 * @param pszShellCode Shell code bytes to be executed.
 * @return Handle to the newly-created thread; INVALID_HANDLE_VALUE if an
 * error occurs.
 * @remarks The function returns INVALID_HANDLE_VALUE if the pszShellCode
 * parameter contains a NULL value or a blank string, or a string containing
 * only whitespace characters.
 */
HTHREAD ExecShellCode1Async(const char* pszShellCode);

/**
 * @name ExecShellCode1
 * @brief Synchronously executes shell code for a function that has void
 * return type and takes no arguments.
 * @param pszShellCode Address of an array of shell code bytes to be executed.
 * @remarks The function stops if the pszShellCode parameter contains a NULL
 * value, a blank string, or a string containing only whitespace characters.
 */
void ExecShellCode1(const char* pszShellCode);

/**
 * @name ExecShellCode3
 * @brief Synchronously executes shell code for a function that returns an
 * integer value (which it's placed into EAX) and takes two integer arg-
 * uments.
 * @param pszShellCode Address of an array of shell code bytes to be executed.
 * @param arg1 First integer argument to push onto the stack of the called
 * function.
 * @param arg2 Second integer argument to push onto the stack of the called
 * function.
 * @param pnResult Address of an integer that receives the result returned.
 */
void ExecShellCode3(const char* pszShellCode, int arg1, int arg2,
    int *pnResult);

#endif //__NARAKU_H__
