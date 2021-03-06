// naraku.h - Interface to the Naraku library
//

#ifndef __NARAKU_H__
#define __NARAKU_H__

#include "stdafx.h"

#include "naraku_symbols.h"
#include "shell_code_user_state.h"
#include "shell_code_results.h"

/**
 * @brief Function signature template for a shellcode function that takes
 * no arguments and returns nothing.
 */
typedef void (*LPSHELLCODE_VOID_ROUTINE)(void);

/**
 * @brief Function signature template for a shellcode function that takes
 * one integer argument and returns an integer result.
 * @param arg1 First argument to pass to the shellcode.
 * @return Result of the function (value in EAX).
 */
typedef int (*LPSHELLCODE_ONEARG_FUNCTION)(int arg1);

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
 * @param nShellCodeLength The number of bytes of shellcode passed.
 * @param ppShellCodeBytes Address of a storage location that will be filled
 * with the address of the shellcode block marked as executable with mprotect.
 * @return Handle to the newly-created thread; INVALID_HANDLE_VALUE if an
 * error occurs.
 * @remarks The function returns INVALID_HANDLE_VALUE if the pszShellCode
 * parameter contains a NULL value or a blank string, or a string containing
 * only whitespace characters.
 */
HTHREAD ExecShellCode1Async(const void* pvShellCode, int nShellCodeLength,
    void** ppShellCodeBytes);

/**
 * @name ExecShellCode1Async
 * @brief Executes shellcode that does not ask for parameters and does not
 * return an argument.  Launches a separate thread of execution in which to
 * execute the shellcode.
 * @param pszShellCode Shell code bytes to be executed.
 * @param nShellCodeLength The number of bytes of shellcode passed. Must
 * be a positive integer.
 * @param nArg1 Integer argument to be passed to the shellcode.
 * @param ppShellCodeBytes Address of a storage location that will be filled
 * with the address of the shellcode block marked as executable with mprotect.
 * @return Handle to the newly-created thread; INVALID_HANDLE_VALUE if an
 * error occurs.
 * @remarks The function returns INVALID_HANDLE_VALUE if the pszShellCode
 * parameter contains a NULL value or a blank string, or a string containing
 * only whitespace characters.
 */
HTHREAD ExecShellCode2Async(const void* pvShellCode, int nShellCodeLength,
    int nArg1, void** ppShellCodeBytes);

/**
 * @name ExecShellCode1
 * @brief Synchronously executes shell code for a function that has void
 * return type and takes no arguments.
 * @param pszShellCode Address of an array of shell code bytes to be executed.
 * @param nShellCodeLength The number of bytes of shellcode passed.
 * @remarks The function stops if the pszShellCode parameter contains a NULL
 * value, a blank string, or a string containing only whitespace characters.
 */
void ExecShellCode1(const void* pvShellCode, int nShellCodeLength);

/**
 * @name ExecShellCode2
 * @brief Synchronously executes shell code for a function that returns an
 * integer value (which it's placed into EAX) and takes one integer arg-
 * ument.
 * @param pszShellCode Address of an array of shell code bytes to be executed.
 * @param nShellCodeLength The number of bytes of shellcode passed.
 * @param nArg1 First integer argument to push onto the stack of the called
 * function.
 * @param pnResult Address of an integer that receives the result returned.
 */
void ExecShellCode2(const void* pvShellCode, int nShellCodeLength,
    int nArg1, int *pnResult);

/**
 * @name ExecShellCode3
 * @brief Synchronously executes shell code for a function that returns an
 * integer value (which it's placed into EAX) and takes two integer arg-
 * uments.
 * @param pszShellCode Address of an array of shell code bytes to be executed.
 * @param nShellCodeLength The number of bytes of shellcode passed.
 * @param arg1 First integer argument to push onto the stack of the called
 * function.
 * @param arg2 Second integer argument to push onto the stack of the called
 * function.
 * @param pnResult Address of an integer that receives the result returned.
 */
void ExecShellCode3(const void* pvShellCode, int nShellCodeLength,
    int arg1, int arg2, int *pnResult);

/**
 * @name PlaceShellCodeInMemory
 * @brief Prepares for executing shellcode by placing the code in the correct
 * location on the heap and then making that region of the heap executable.
 * @param pvShellCode Address of a buffer containing the bytes of shell code
 * to be placed.
 * @param nShellCodeLength Size of the input buffer of shell code, in bytes.
 * @param ppBuf Address of storage that will receive the address in memory
 * of the executable instructions.
 */
void PlaceShellCodeInMemory(const void* pvShellCode,
    int nShellCodeLength, void **ppBuf);

/**
 * @name RemoveShellCodeFromMemory
 * @brief Removes shell code from the heap.
 * @param pvShellCode Address on the heap of the shellcode to remove.
 * @param nShellCodeLength Size, in bytes, of the shellcode.
 */
void RemoveShellCodeFromMemory(void *pvShellCode, int nShellCodeLength);

#endif //__NARAKU_H__
