// twoarg_shellcode_tests.c - Defines the implementations of tests that exer-
// cise the two-argument shellcode functionality.
//

#include "stdafx.h"
#include "kagome.h"

#include "get_cpuinfo_tests.h"

#ifndef ERROR_FILESIZE_MUST_BE_POSITIVE
#define ERROR_FILESIZE_MUST_BE_POSITIVE \
    "ERROR: The nFileSize variable expected to have positive integer value.\n"
#endif //ERROR_FILESIZE_MUST_BE_POSITIVE

#ifndef FILE_LENGTH_DISPLAY_STRING
#define FILE_LENGTH_DISPLAY_STRING \
  "The file '%s' is %d B in size.\n"
#endif //FILE_LENGTH_DISPLAY_STRING

#ifndef TEST_GET_CPU_INFO_NAME
#define TEST_GET_CPU_INFO_NAME "TestGetCpuInfo"
#endif //TEST_GET_CPU_INFO_NAME

//////////////////////////////////////////////////////////////////////////////
// Globals

const char *FILE_PATH = "/proc/cpuinfo";

//////////////////////////////////////////////////////////////////////////////
// Unit tests

BOOL TestGetCpuInfo() {
  int nFileSize = 0;
  char* output = NULL;
  ReadAllText(FILE_PATH, &output, &nFileSize);

  fprintf(stdout, "%s\n", output);

  free(output);
  output = NULL;

  AssertIsTrue(TEST_GET_CPU_INFO_NAME, ERROR_FILESIZE_MUST_BE_POSITIVE,
      nFileSize > 0);

  fprintf(stdout, FILE_LENGTH_DISPLAY_STRING,
      FILE_PATH, nFileSize);

  return nFileSize > 0;
}

//////////////////////////////////////////////////////////////////////////////
// Publicly-exposed functions

void RunCpuInfoTests() {
  LPTESTSESSION lpSession = NULL;
  StartUnitTestSession(NULL, NULL, &lpSession);

  if (lpSession == NULL) {
    exit( EXIT_FAILURE);
  }

  ExecuteTest(lpSession, TEST_GET_CPU_INFO_NAME,
      TestGetCpuInfo);

  EndUnitTestSession(&lpSession);
}
