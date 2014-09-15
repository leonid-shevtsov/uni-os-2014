#include <windows.h>
#include <stdio.h>

typedef int FilterFunction(int[5][2], int[10]);

int main() {
	int i;

	HINSTANCE hDLL;
	FilterFunction *filterArray;

	hDLL = LoadLibrary(L"lab1_dll");

	if (hDLL != NULL) {
		filterArray = (FilterFunction*)GetProcAddress(hDLL, "filterArray");

		if (filterArray) {
			int in[5][2] = {{1, -1}, {2, -2}, {3, -3}, {4, -4}, {5, -5}};
			int out[10];
			int n = filterArray(in, out);
			for(i=0; i < n; ++i) {
				printf("filtered[%i] = %i\n", i, out[i]);
			}
		} else {
			printf("Failed to load the function from the DLL\n");
		}
		FreeLibrary(hDLL);
	} else {
		printf("Failed to load the DLL\n");
	}
	scanf("%i", &i);
}