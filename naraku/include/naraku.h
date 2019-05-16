// naraku.h - Interface to the Naraku library
//

#ifndef __NARAKU_H__
#define __NARAKU_H__

/**
 * @brief Function signature template for a shellcode function that takes
 * no arguments and returns nothing.
 */
typedef void (*LPSHELLCODE_VOID_ROUTINE)(void);

/**
 * @name ExecShellCode1
 * @brief Executes shell code for a function that has void return type and
 * takes no arguments.
 * @param pszShellCode Address of an array of shell code bytes to be executed.
 */
void ExecShellCode1(const char* pszShellCode);

#endif //__NARAKU_H__
