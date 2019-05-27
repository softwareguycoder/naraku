// kagome.c - Implementation of main function
//
// This application is a test harness for the naraku shared library.  It
// depends on the following libraries:
//
// - naraku
// - api_core
// - common_core
// - test_core
//

#include "stdafx.h"
#include "kagome.h"

#include "twoarg_shellcode_tests.h"
#include "void_shellcode_tests.h"

const char *FILE_PATH = "/proc/cpuinfo";

//////////////////////////////////////////////////////////////////////////////
// Main application code

int main(void) {

  PrintSoftwareTitleAndCopyright();

  int file_size = 0;
  char* output = NULL;
  ReadAllText(FILE_PATH, &output, &file_size);

  fprintf(stdout, "%s\n", output);

  free(output);
  output = NULL;

  fprintf(stdout, "The file '%s' is %d B in size.\n", FILE_PATH, file_size);

  //RunVoidShellCodeTests();

  //RunTwoArgShellcodeTests();

  return EXIT_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////////
