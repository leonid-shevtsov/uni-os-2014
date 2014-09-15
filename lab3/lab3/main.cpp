#include <windows.h>
#include <fstream>
#include <sstream>
#include "resource.h"
#include "../lab3_dll/lab3_dll.h"

using namespace std;

int filesize(const char* filename) {
	ifstream file(filename , ios::binary | ios::ate);
	return file.tellg();
}

DWORD WINAPI calculationsThreadProc(LPVOID param) {
	int bufsize = filesize("10mb.txt");
	char* buf = (char*)VirtualAlloc(NULL, bufsize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	if (buf) {
		ifstream f;
		f.open("10mb.txt");
		f.get(buf, bufsize, 0);
		int answer = performCalculations(buf);
		stringstream stream;
		stream << answer;
		MessageBoxA(NULL, stream.str().c_str(), "Число слов, начинающихся и заканчивающихся той же буквой", NULL);
	} else {
		char msg[1000];
		FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(), NULL, msg, 1000, NULL);
		MessageBoxA(NULL, msg, "Не удалось выделить память", 0);
	}
	return 0;
}

void startCalculations() {
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
			case 101: startCalculations(); break;
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