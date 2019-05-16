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

#include "void_shellcode_tests.h"

//////////////////////////////////////////////////////////////////////////////
// Main application code

int main(void) {

  PrintSoftwareTitleAndCopyright();

  RunVoidShellCodeTests();

  return EXIT_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////////
