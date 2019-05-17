// twoarg_shellcode_tests.h - Interface to test functions that exercise the
// functionality of a shellcode execution function that takes two arguments.
//

#ifndef __TWOARG_SHELLCODE_TESTS_H__
#define __TWOARG_SHELLCODE_TESTS_H__

#ifndef VALUE_ONE
#define VALUE_ONE    67
#endif //VALUE_ONE

#ifndef VALUE_TWO
#define VALUE_TWO    324
#endif //VALUE_TWO

#ifndef EXPECTED_SUM
#define EXPECTED_SUM  391
#endif //EXPECTED_SUM

extern char SHELLCODE_EXAMPLE_001[];

void RunTwoArgShellcodeTests();

#endif //__TWOARG_SHELLCODE_TESTS_H__
