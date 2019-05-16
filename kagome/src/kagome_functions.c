// kagome_functions.c - Implementations of functions used across the kagome
// application
//

#include "stdafx.h"
#include "kagome.h"

#include "kagome_functions.h"

//////////////////////////////////////////////////////////////////////////////
// Publicly-exposed functions

void PrintSoftwareTitleAndCopyright()
{
  fprintf(stdout, SOFTWARE_TITLE);
  fprintf(stdout, SOFTWARE_COPYRIGHT);
}

//////////////////////////////////////////////////////////////////////////////

