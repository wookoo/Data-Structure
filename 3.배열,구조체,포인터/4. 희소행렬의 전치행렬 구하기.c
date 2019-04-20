#include <stdio.h>
#define MAX_TERMS 100
typedef struct {
	int row;
	int col;
	int value;
}element;
typedef struct {
	element data[MAX_TERMS];
	int ROWS;
	int COLS;
	int terms;
}SparseMatrix;

SparseMatrix TrasneMatrix(SparseMatrix m1) {
	SparseMatrix m2;
	int index = 0;
	for (int cols = 0; cols < m1.COLS; cols++) {
		for (int i = 0; i < m1.terms; i++) {
			if (m1.data[i].col == cols) {
				m2.data[index].row = m1.data[i].col;
				m2.data[index].col = m1.data[i].row;
				m2.data[index].value = m1.data[i].value;
				index++;
			}
		}
	}
	m2.ROWS = m1.ROWS;
	m2.COLS = m1.COLS;
	m2.terms = m1.terms;
	return m2;
}

void PrintSparse(SparseMatrix m1) {
	for (int i = 0; i < m1.terms; i++) {
		printf("{%d %d %d}\n", m1.data[i].row, m1.data[i].col, m1.data[i].value);
	}
	printf("==========================\n\n");
}

int main() {
	SparseMatrix matrix1 = { {{0,3,7},{1,0,9},{1,5,8},{3,0,6},{3,1,5},{4,5,1},{5,2,2}},
		6,
		6,
		7};
	SparseMatrix matrix2 = TrasneMatrix(matrix1);
	PrintSparse(matrix1);
	PrintSparse(matrix2);

}