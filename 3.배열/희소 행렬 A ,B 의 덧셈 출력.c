/*
	*	����
	*		��� A,  B�� ���� C ����(�ʱ�ȭ ����)�� �ۼ��϶�. 
	*		(��� Ÿ���� SparseMatrix, ����� �� ��Ҵ� (row, col, val)�� ǥ��)
	*		������ A B �� �޾Ƽ� �� ����� ��ȯ�ϴ� add �Լ��� �ۼ��϶�.

	*	�˰���
	*		�������� ����

	

*/

#include <stdio.h>
#define MAX_TERMS 100 //data  �迭�� �� �ִ� ������ ��ȣ ����� ����
#define ROW 5 //���� ũ�⸦ ��ȣ ����� ����
#define COL 10 //���� ũ�⸦ ��ȣ ����� ����
typedef struct {
	int row;
	int col;
	int value;
} element;

typedef struct {
	element data[MAX_TERMS];
	int rows;	//���� ũ��
	int cols;	//���� ũ��
	int terms;	//data �迭�� �� index ��
} sparse_matrix;

sparse_matrix MakeSparse(int Matrix[ROW][COL]);  
void printMatrix(sparse_matrix Matrix);
sparse_matrix add(sparse_matrix matrix1, sparse_matrix matrix2);
void print(sparse_matrix matrix);

int main(void) {
	

	sparse_matrix SparseA = { { { 0, 2, 1 },
	{ 1, 5, 2 },
	{ 3, 1, 3 },
	{ 3, 9, 4 },
	{ 4, 0, 5 },
	{ 4, 4, 6 },
	{ 4, 9, 7 } },5,10,7 };
	sparse_matrix SparseB = { {{ 0, 0, 5 },
	{ 0, 4, 6 },
	{ 0, 9, 7 },
	{ 1, 1, 3 },
	{ 1, 5, 1 },
	{ 1, 9, 4 },
	{ 2, 2, 1 },
	{ 3, 5, 2 },
	{ 4, 4, 1 },
	{ 4, 9, 1 }},5,10,10 };
	
	sparse_matrix SparseC = add(SparseA, SparseB);
	print(SparseC);


}

sparse_matrix MakeSparse(int Matrix[ROW][COL]) {
	sparse_matrix temp;
	int terms = 0;
	for (int row = 0; row < ROW; row++) {
		for (int col = 0; col < COL; col++) {
			if (Matrix[row][col] != 0) {
				temp.data[terms].row = row;
				temp.data[terms].col = col;
				temp.data[terms].value = Matrix[row][col];
				terms++;


			}
		}
	}
	temp.rows = ROW ;
	temp.cols = COL ;
	temp.terms = terms;
	return temp;
}

void printMatrix(sparse_matrix Matrix) {
	int index = Matrix.terms;
	printf("{{");
	for (int i = 0; i < index; i++) {
		printf("{ %d, %d, %d },\n", Matrix.data[i].row, Matrix.data[i].col, Matrix.data[i].value);
	}
	printf("},%d,%d,%d}", Matrix.rows, Matrix.cols, Matrix.terms);
}

sparse_matrix add(sparse_matrix matrix1, sparse_matrix matrix2) {
	sparse_matrix temp;
	int it = 0, i1 = 0, i2 = 0;
	int matrix1Index = matrix1.terms;
	int matrix2Index = matrix2.terms;

	temp.rows = matrix1.rows > matrix2.rows ? matrix1.rows : matrix2.rows;
	temp.cols = matrix1.cols > matrix2.cols ? matrix1.cols : matrix2.cols;

	int matrix1ROW = matrix1.rows;
	int matrix2ROW = matrix2.rows;
	temp.terms = 0;

	while (matrix1Index > i1 && matrix2Index > i2) {
		if (matrix1.data[i1].row == matrix2.data[i2].row) {
			if (matrix1.data[i1].col == matrix2.data[i2].col) {
				temp.data[it].col = matrix1.data[i1].col;
				temp.data[it].row = matrix1.data[i1].row;
				temp.data[it].value = matrix1.data[i1].value + matrix2.data[i2].value;
				i1++, i2++, it++;

			}
			else if (matrix1.data[i1].col > matrix2.data[i2].col) {
				temp.data[it].col = matrix2.data[i2].col;
				temp.data[it].row = matrix2.data[i2].row;
				temp.data[it].value = matrix2.data[i2].value;
				i2++, it++;
			}
			else {
				temp.data[it].col = matrix1.data[i1].col;
				temp.data[it].row = matrix1.data[i1].row;
				temp.data[it].value = matrix1.data[i1].value;
				i1++, it++;
			}
		}
		else if (matrix1.data[i1].row > matrix2.data[i2].row) {
			temp.data[it].col = matrix2.data[i2].col;
			temp.data[it].row = matrix2.data[i2].row;
			temp.data[it].value = matrix2.data[i2].value;
			i2++, it++;

		}
		else {
			temp.data[it].col = matrix1.data[i1].col;
			temp.data[it].row = matrix1.data[i1].row;
			temp.data[it].value = matrix1.data[i1].value;
			i1++, it++;
		}

			
		temp.terms++;
	}
	return temp;

}
void print(sparse_matrix matrix) {

	int index = 0;


	
	for (int i = 0; i < matrix.rows * matrix.cols; i++) {
		int position = (matrix.data[index].row * matrix.cols) + matrix.data[index].col;
		
		if (position == i) {
			printf("%d ", matrix.data[index].value);
			index++;
		}
	
		else {
			printf("0 ");
		}
		
		if (i % matrix.cols == matrix.cols - 1) {
			printf("\n");
		}
		
	}

}