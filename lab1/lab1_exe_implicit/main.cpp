#include <windows.h>
#include <stdio.h>
#include "..\lab1_dll\exports.h"

int main() {
	int in[5][2] = {{1, -1}, {2, -2}, {3, -3}, {4, -4}, {5, -5}};
	int out[10];

	int n = filterArray(in, out), i;

	for(i=0; i < n; ++i) {
		printf("filtered[%i] = %i\n", i, out[i]);
	}
	
	scanf("%i", &i);
}