// shell_code_results.h - Interface to a data structure utilized for
// transporting shellcode results around.
//

#ifndef __SHELL_CODE_RESULTS_H__
#define __SHELL_CODE_RESULTS_H__

typedef struct _tagSHELLCODERESULTS {
  int nSyscallReturnValue;
  int nErrnoValue;
} SHELLCODERESULTS, *LPSHELLCODERESULTS, *LPPSHELLCODERESULTS;

#endif //__SHELL_CODE_RESULTS_H__
