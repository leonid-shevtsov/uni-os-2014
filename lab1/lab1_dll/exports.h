#ifndef __LAB1_DLL_H__
#define __LAB1_DLL_H__


const int MAX_I = 5;
const int MAX_J = 2;
const int MAX_N = 10;


extern "C" {
	__declspec( dllexport ) int __cdecl filterArray(int inArray[MAX_I][MAX_J], int outArray[MAX_N]);
}

#endif