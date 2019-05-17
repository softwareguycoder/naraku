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

#ifndef SHELLCODE_EXAMPLE_001
#define SHELLCODE_EXAMPLE_001 \
    "\x55\x48\x89\xe5\x89\x7d\xfc\x89\x75\xf8\x8b\x55\xfc\x8b\x45\xf8\x01" \
    "\xd0\x5d\xc3"
#endif //SHELLCODE_EXAMPLE_001

void RunTwoArgShellcodeTests();

#endif //__TWOARG_SHELLCODE_TESTS_H__
