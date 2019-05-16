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

//////////////////////////////////////////////////////////////////////////////
// Main application code

int main(void) {
  LPTESTSESSION lpSession = NULL;
  StartUnitTestSession(NULL, NULL, &lpSession);

  if (lpSession == NULL) {
    return EXIT_FAILURE;
  }



  EndUnitTestSession(&lpSession);

	return EXIT_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////////
