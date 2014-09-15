#include <windows.h>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <sstream>
#include "resource.h"

using namespace std;

//	14) Знайти кількість слів, які починаються і закінчуються однією і тією ж літерою.
void performCalculations() {
	int answer = 0;
	ifstream f;
	string line;
	smatch m;
	regex re("\\w+");
	f.open("10mb.txt");
	while( !f.eof() ) {
		f >> line;
		transform(line.begin(), line.end(), line.begin(), ::tolower);
		regex_search(line, m, re);
		for (smatch::iterator i = m.begin(); i!= m.end(); ++i) {
			string word = *i;
			if (word[0] == word[word.size()-1]) {
				answer++;
			}
		}
	}
	stringstream stream;
	stream << answer;
	MessageBoxA(NULL, stream.str().c_str(), "Число слов, начинающихся и заканчивающихся той же буквой", NULL);
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
			case 101: performCalculations(); break;
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