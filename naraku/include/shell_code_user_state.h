// shell_code_user_state.h - Interface for the SHELLCODEUSERSTATE structure
//

#ifndef __SHELL_CODE_USER_STATE_H__
#define __SHELL_CODE_USER_STATE_H__

typedef struct _tagSHELLCODEUSERSTATE {
  void* pShellCode;
  int nByteCount;
  void* pvArgs;
  void* pvResult;
} SHELLCODEUSERSTATE, *LPSHELLCODEUSERSTATE, **LPPSHELLCODEUSERSTATE;

void CreateShellCodeUserState(LPPSHELLCODEUSERSTATE lppResult,
    void *pShellCode, int nByteCount, void* pvArgs, void* pvResult);
void FreeShellCodeUserState(LPPSHELLCODEUSERSTATE lppUserState);
void* GetShellCodeUserStateArgsPointer(LPSHELLCODEUSERSTATE lpUserState);
void* GetShellCodeUserStateResultPointer(LPSHELLCODEUSERSTATE lpUserState);
void* GetShellCodeUserStateShellCodePointer(LPSHELLCODEUSERSTATE lpUserState);
int GetShellCodeUserStateByteCount(LPSHELLCODEUSERSTATE lpUserState);
BOOL IsShellCodeUserStateValid(LPSHELLCODEUSERSTATE lpUserState);
void SetShellCodeUserStateArgsPointer(LPSHELLCODEUSERSTATE lpUserState,
    void* pvArgs);
void SetShellCodeUserStateResultPointer(LPSHELLCODEUSERSTATE lpUserState,
    void* pvResult);
void SetShellCodeUserStateShellCodePointer(LPSHELLCODEUSERSTATE lpUserState,
    void* pShellCode);
void SetShellCodeUserStateByteCount(LPSHELLCODEUSERSTATE lpUserState,
    int nByteCount);

#endif //__SHELL_CODE_USER_STATE_H__
