#include <stdio.h>
#include <malloc.h>

#define NULL 0

int main() 
{
	int size_x = 3;
	int size_y = 5;

	int** ap;
	ap = (int**)malloc(sizeof(int*)*size_y);

	for (int i = 0; i < size_y; i++) {
		ap[i] = (int*)malloc(sizeof(int)*size_x);
	}

	for (int i = 0; i < size_y; i++) {
		for (int j = 0; j < size_x; j++) {
			ap[i][j] = 0;
		}
	}
	
	ap[1][1] = 1;
	ap[2][2] = 1;
	ap[4][2] = 1;

	for (int i = 0; i < size_y; i++) {
		for (int j = 0; j < size_x; j++) {
			printf("%d ", ap[i][j]);
		}
		printf("\n");
	}
	
	for (int i = 0; i < size_y; i++) {
		free(ap[i]);
	}
	free(ap);

	return 0;
}
