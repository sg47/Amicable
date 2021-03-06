#include "stdafx.h"
#include "Platform.h"

// Platform/compiler-dependent code must be here

#ifdef _MSC_VER // MSVC & Windows

#pragma section("udiv128", read, execute)
__declspec(allocate("udiv128"))
const unsigned char udiv128Code[] =
{
	0x48, 0x89, 0xD0, // mov rax,rdx
	0x48, 0x89, 0xCA, // mov rdx,rcx
	0x49, 0xF7, 0xF0, // div r8
	0x49, 0x89, 0x11, // mov [r9],rdx
	0xC3              // ret
};

#pragma section("mulmod64", read, execute)
__declspec(allocate("mulmod64"))
const unsigned char mulmod64_code[] = {
		0x48, 0x89, 0xC8, // mov rax,rcx
		0x48, 0xF7, 0xE2, // mul rdx
		0x49, 0xF7, 0xF0, // div r8
		0x48, 0x89, 0xD0, // mov rax,rdx
		0xC3              // ret
};

number (*udiv128)(number numhi, number numlo, number den, number* rem) = (number(*)(number, number, number, number*))((const unsigned char*)udiv128Code);
number (*mulmod64)(number a, number b, number n) = (number (*)(number, number, number))((const unsigned char*) mulmod64_code);

#endif
