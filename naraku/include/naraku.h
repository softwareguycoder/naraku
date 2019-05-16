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

#endif //__NARAKU_H__
