#ifndef __LAB3_DLL_H__
#define __LAB3_DLL_H__

extern "C" {
	__declspec(dllexport) int __cdecl performCalculations(char* dataString);
}

#endif