// shell_code_user_state.h - Interface for the SHELLCODEUSERSTATE structure
//

#ifndef __SHELL_CODE_USER_STATE_H__
#define __SHELL_CODE_USER_STATE_H__

typedef struct _tagSHELLCODEUSERSTATE {
  void* pShellCode;
  int nShellCodeBytes;
  void* pvArgs;
  void* pvResult;
} SHELLCODEUSERSTATE, *LPSHELLCODEUSERSTATE, **LPPSHELLCODEUSERSTATE;

void CreateShellCodeUserState(LPPSHELLCODEUSERSTATE lppResult,
    void *pShellCode, int nShellCodeBytes, void* pvArgs, void* pvResult);
void FreeShellCodeUserState(LPPSHELLCODEUSERSTATE lppUserState);
void* GetArgs(LPSHELLCODEUSERSTATE lpUserState);
void* GetResult(LPSHELLCODEUSERSTATE lpUserState);
void* GetShellCode(LPSHELLCODEUSERSTATE lpUserState);
int GetShellCodeBytes(LPSHELLCODEUSERSTATE lpUserState);
BOOL IsShellCodeUserStateValid(LPSHELLCODEUSERSTATE lpUserState);
void SetArgs(LPSHELLCODEUSERSTATE lpUserState, void* pvArgs);
void SetResult(LPSHELLCODEUSERSTATE lpUserState, void* pvResult);
void SetShellCode(LPSHELLCODEUSERSTATE lpUserState, void* pShellCode);
void SetShellCodeBytes(LPSHELLCODEUSERSTATE lpUserState, int nShellCodeBytes);

#endif //__SHELL_CODE_USER_STATE_H__
