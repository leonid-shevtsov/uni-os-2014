#include <windows.h>
#include <cstdlib>
#include <sstream>
#include "resource.h"

using namespace std;

int numbers[1000][1000];
int checksum = 0;

int computeChecksum() {
	int checksum = 0;
	for (int i = 0; i < 1000; ++i) {
		for (int j = 0; j < 1000; ++j) {
			checksum ^= numbers[i][j];
		}
	}
	return checksum;
}

DWORD WINAPI generatorThreadProc(LPVOID param) {
	while(1) {
		for (int i=0; i < 1000; ++i) {
			for (int j=0; j < 1000; ++j) {
				numbers[i][j] = rand();
			}
		}
		checksum = computeChecksum();
		Sleep( rand() % 1000);
	}
	return 0;
}

DWORD WINAPI calculationsThreadProc(LPVOID param) {
	int currentChecksum = computeChecksum();
	if (currentChecksum = checksum) {

		for (int i=0; i<1000; ++i) {
			int minj = 0;
			for (int j=1; j<1000; ++j) {
				if (numbers[i][j]<numbers[i][minj]) {
					minj = j;
				}
			}
			bool isSaddlePoint = true;
			for (int k=0; k<1000; ++k) {
				if (k!=i && numbers[k][minj]>numbers[i][minj]) {
					isSaddlePoint = false;
					break;
				}
			}
			if (isSaddlePoint) {
				stringstream ss;
				ss << i << "," << minj;
				MessageBoxA(NULL, ss.str().c_str(), "Saddle point", NULL);
				return 0;
			}
		}
		MessageBoxA(NULL, "No saddle points", NULL, NULL);
		return -1;
	} else {
		MessageBoxA(NULL, "Bad checksum", NULL, NULL);
		return -1;
	}
}


void startGenerator() {
	CreateThread(NULL, 0, generatorThreadProc, 0, 0, 0);
}	

void performCalculations() {
	CreateThread(NULL, 0, calculationsThreadProc, 0, 0, 0);
}	

INT_PTR CALLBACK mainDialogProc(
  _In_  HWND hwndDlg,
  _In_  UINT uMsg,
  _In_  WPARAM wParam,
  _In_  LPARAM lParam
) {
    switch (uMsg) 
    { 
		case WM_COMMAND:
			switch(LOWORD(wParam)) {
			case 101: startGenerator(); break;
			case 104: performCalculations(); break;
			case 102: DialogBox(NULL, (LPCWSTR)IDD_DIALOG2, NULL, mainDialogProc); break;
			case 103: SendMessage(hwndDlg, WM_CLOSE, 0, 0); break;
			}
			return TRUE;
        case WM_CLOSE: 
			int result;
            EndDialog(hwndDlg, (INT_PTR)&result);
            return TRUE; 
    }
	return FALSE;
}

int CALLBACK WinMain(
  _In_  HINSTANCE hInstance,
  _In_  HINSTANCE hPrevInstance,
  _In_  LPSTR lpCmdLine,
  _In_  int nCmdShow
) {
	DialogBox(NULL, (LPCWSTR)IDD_DIALOG1, NULL, mainDialogProc);
}