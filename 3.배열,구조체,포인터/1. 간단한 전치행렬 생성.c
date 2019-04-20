#include <stdio.h>
#define ROWS 3
#define COLS 3
void TranseMatrix(int A[ROWS][COLS], int B[ROWS][COLS]) {
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			B[j][i] = A[i][j];
		}
	}
}

void PrintMatrix(int A[ROWS][COLS]) {
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			printf("%d ", A[i][j]);
		}
		printf("\n");
	}
}

int main() {
	int Matrix1[ROWS][COLS] = {
		{1,2,3},
	{4,2,1},
	{9,4,8}
	};
	int Matrix2[ROWS][COLS];
	TranseMatrix(Matrix1, Matrix2);
	PrintMatrix(Matrix1);
	printf("===============\n");
	PrintMatrix(Matrix2);
}