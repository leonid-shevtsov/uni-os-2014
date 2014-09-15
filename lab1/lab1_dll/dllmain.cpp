#include <windows.h>
#include <stdio.h>
#include "exports.h"

int internalFilterArray(int inArray[MAX_I][MAX_J], int outArray[MAX_N]) {
	int n = 0;
	for (int i = 0; i < MAX_I; i++) {
		for (int j = 0; j < MAX_J; j++) {
			if (inArray[i][j] < 0) {
				outArray[n++] = inArray[i][j];
			}
		}
	}
	return n;
}

__declspec( dllexport ) int filterArray(int inArray[MAX_I][MAX_J], int outArray[MAX_N]) {
	return internalFilterArray(inArray, outArray);
}
	
BOOL WINAPI DllMain(
  _In_  HINSTANCE hinstDLL,
  _In_  DWORD fdwReason,
  _In_  LPVOID lpvReserved
  ) {
	if (fdwReason == DLL_PROCESS_ATTACH) {
		if (lpvReserved == NULL) {
			printf("DLL loaded explicitly\n");
		} else {
			printf("DLL loaded implicitly\n");
		}
	} else if (fdwReason == DLL_PROCESS_DETACH) {
		if (lpvReserved == NULL) {
			printf("DLL detached explicitly\n");
		} else {
			printf("DLL detached because process is terminating\n");
		}
	}
	return TRUE;
}
