#include "stdafx.h"

string get_cpu_name()
{
	uint32_t data[4] = { 0 };

	_asm
	{
		cpuid;
		mov data[0], ebx;
		mov data[4], edx;
		mov data[8], ecx;
	}

	return string((const char*)data);
}

void assembler()
{
	cout << "CPU is " << get_cpu_name() << endl;

	float f1[] = { 1.f, 2.f, 3.f, 4.f };
	float f2[] = { 5.f, 4.f, 3.f, 2.f };
	float result[4] = { 0.f };

	_asm
	{
		movups xmm1, f1;
		movups xmm2, f2;
		mulps xmm1, xmm2;
		movups result, xmm1;
	}

	for (size_t i = 0; i < 4; i++)
	{
		cout << result[i] << "\t";
	}
	cout << endl;

	// https://en.wikipedia.org/wiki/CPUID
	int d, c;

	_asm
	{
		mov eax, 1;
		cpuid;
		mov d, edx;
		mov c, ecx;
	}

	if ((d & (1 << 26)) != 0)
		cout << "sse2 is supported" << endl;
	
	if ((c & 1) != 0)
		cout << "sse3 is supported" << endl;

	if ((c & (1 << 19)) != 0)
		cout << "sse4.1 is supported" << endl;
	
	if ((c & (1 << 20)) != 0)
		cout << "sse4.2 is supported" << endl;
}

int main(int argc, char* argv[])
{

	assembler();
	return 0;
}