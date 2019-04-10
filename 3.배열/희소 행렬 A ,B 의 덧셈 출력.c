/*
	*	문제
	*		행렬 A,  B에 대한 C 선언문(초기화 포함)을 작성하라. 
	*		(행렬 타입은 SparseMatrix, 행렬의 각 요소는 (row, col, val)로 표현)
	*		희소행렬 A B 를 받아서 그 결과를 반환하는 add 함수를 작성하라.

	*	알고리즘
	*		1. 희소행렬의 표현 :
	*			희소행렬의 표현은 value 가 0 이 아닌 값을 구조체 배열에 저장을 하면된다.
	*			그 데이터는 0 이 아닌 value 의 row 값, col 값을 저장을 하게 된다.
	*			{2,5,4} 로 저장이 되어있으면, 2행 5열의 4 라는 값이 있다는 뜻 이다.
	*
	*		2. 희소행렬 A + B 의 덧셈
	*			희소행렬 A + B 의 덧셈은 구조체 배열을 가져와서 그 두가지를 더하면 된다.
	*			예를들어 A 는 { 3, 3 ,1},{ 3 , 5 , 4 } 고 B 는 { 3, 3, 4 }, { 5, 4, 7 } 이라고 가정을 하자
	*			생성될 배열을 C 라고 하면, A 의 첫번째인 3 3 1 과 B 의 첫번째인 3 3 4 를 비교 해야 한다.
	*			이 케이스는 A 의 row col 은 3 3 , B 의  rowl col 은 3 3 이므로 A B value 를 더한 5를 C 에 저장하면 된다.
	*			{ 3, 3 ,5} 이런식으로 말이다.
	*			A 의 3 3 1 B의 3 3 4 는 더해졌으므로 이제 A 의 3 5 4 와 B 의 5 4 7 을 비교하면 된다.
	*			row 값이 같을 경우 col 값도 비교해야되는데 이경우 row 값이 다르기 때문에 더 작은 row 를 가진
	*			A 의 값이 그대로 C 배열로 들어가면 된다. C 배열은 곧 {3, 3, 5},{3, 5, 4} 가 된다.
	*			그럼 A 의 요소들은 모두 사용됬기 때문에 이제, 남은 B 배열이 C 배열로 그냥 내려오면 된다.
	*			이 알고리즘을 적용해서 구하면, C 는 결국 {3, 3, 5},{3, 5, 4},{5, 4, 7}
	

*/

#include <stdio.h>
#define MAX_TERMS 100 //data  배열에 들어갈 최대 갯수를 기호 상수로 선언
#define ROW 5 //행의 크기를 기호 상수로 선언
#define COL 10 //열의 크기를 기호 상수로 선언
typedef struct {
	int row;
	int col;
	int value;
} element;

typedef struct {
	element data[MAX_TERMS];
	int rows;	//행의 크기
	int cols;	//열의 크기
	int terms;	//data 배열의 들어간 index 수
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