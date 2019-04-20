﻿/*
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
	*			그럼 A 의 요소들은 모두 사용되기 때문에 이제, 남은 B 배열이 C 배열로 그냥 내려오면 된다.
	*			그러나 이 row 와 col 을 비교하는 경우는 너무  비효율적이다.
	*			그렇기 떄문에 matrix.data[index].row * matrix.colSize + matrix.data[index].col 을 사용해서 비교한다
	*			위 식을 matrix1Pos 와 matrix2Pos 라 생각하면 둘이 같은경우는, 위치가 같은 경우,
	*			matrix1Pos > matrix2Pos 일 경우 matrix2Pos 가 먼저 들어가야 하는경우
	*			그 외의 경우는 matrix1Pos 가 들어가야 하는 경우다.
	*			그러나 3 * 4 , 5 * 2 배열의 덧셈도 고려해야 한다.
	*			희소행렬의 크기가 다를 경우 더할수 없다 즉, 종료해야한다.
	*			이는 곧 add 함수의 알고리즘이다.
	*
	*		3. 희소 행렬의 출력
	*			희소행렬에는 terms 와 row 와 col, data 가 필드로 이뤄져있다.
	*			희소행렬의 n 번째 데이터는 다음과 같이 표현을 하면 된다.
	*			n = col * data[index].row + data[index].col
	*			for 문을 사용하여 i < col * row 까지 반복을 하고, 만약 i 값이 n 과 일치하면
	*			n 번째 데이터를 출력한다. 개행은 i 를 col 로 나누었을때 나누어 떨어지면 개행을 하면 된다.
	*
	*		출력
	*			희소행렬 A B 를 더한 C 의 원래 배열의 형태로 출력을 하면 된다.
	*			3 번 알고리즘을 통해 구현이 가능하다.
	*
	*		함수
	*			sparse_matrix add(sparse_matrix matrix1, sparse_matrix matrix2) : matrix1 과 matrix2 의 합한 구조체 반환
	*			void print(sparse_matrix matrix); matrix 배열을 출력하는 함수
*/

#include <stdio.h>
#define MAX_TERMS 100 //data  배열에 들어갈 최대 갯수를 기호 상수로 선언
#define ROW 5 //행의 크기를 기호 상수로 선언
#define COL 10 //열의 크기를 기호 상수로 선언
typedef struct {
	int row;	//데이터의 row 를 저장한다.
	int col;	//데이터의 col 을 저장한다.
	int value;	//데이터를 저장한다.
} element;	//구조체를 element 로 타입을 지정한다.

typedef struct {
	element data[MAX_TERMS];	//MAX_TERMS 만큼 data의 최대 배열 길이를 지정해준다.
	int rows;	//행의 총 크기
	int cols;	//열의 총 크기
	int terms;	//data 배열의 들어간 index 수
} sparse_matrix;


sparse_matrix add(sparse_matrix matrix1, sparse_matrix matrix2); //sparse_matrix 2개를 받아 더하고 반환하는 add 함수 원형 정의
void print(sparse_matrix matrix); //sparse_matrix 를 받아서 출력하는 print 함수 원형 정의

int main(void) {


	sparse_matrix SparseA = { { { 0, 2, 1 },
	{ 1, 5, 2 },
	{ 3, 1, 3 },
	{ 3, 9, 4 },
	{ 4, 0, 5 },
	{ 4, 4, 6 },
	{ 4, 9, 7 } },5,10,7 };	//SparseA 구조체를 선언하고 초기화후, 데이터를 넣는다.
	//row 는 5 col 은 10 terms 는 7이다.
	sparse_matrix SparseB = { {{ 0, 0, 5 },
	{ 0, 4, 6 },
	{ 0, 9, 7 },
	{ 1, 1, 3 },
	{ 1, 5, 1 },
	{ 1, 9, 4 },
	{ 2, 2, 1 },
	{ 3, 5, 2 },
	{ 4, 4, 1 },
	{ 4, 9, 1 }},5,10,10 };	//SparseB 구조체를 선언하고 초기화후, 데이터를 넣는다.
	//row 는 5 col 은 10 terms 는 10이다.
	sparse_matrix SparseC = add(SparseA, SparseB); //SparseA 와 SparseB 를 더해서 SpareseC 에 저장한다.
	print(SparseC);	//저장된 SparseC 를 출력한다.


}



sparse_matrix add(sparse_matrix matrix1, sparse_matrix matrix2) { //더하고 구조체로 반환하기 때문에 sparse_matrix 를 쓴다.
	sparse_matrix temp; //반환할 구조체 선언 
	int it = 0, i1 = 0, i2 = 0;
	//temp 의 index matrix1 의 index matrix2 의 index 변수 it  i1 i2 를 선언한다.
	//index 의 초기값은 0이다.
	if (matrix1.rows != matrix2.rows || matrix1.cols != matrix2.cols) {
		printf("희소행렬 크기 에러");
		exit(1);
	}
	temp.rows = matrix1.rows;
	//알고리즘 설명에 있던 c 배열의 row 는 matrix 1 의 row 가 된다,..

	temp.cols = matrix1.cols;
	//C배열의 col 은 a b 의 col matrix1 의 col 이 된다.
	temp.terms = 0;	//데이터가 0 개 삽입되었으므로 0 이다.

	int Matrix1Postion, Matrix2Postion;

	while (matrix1.terms > i1 && matrix2.terms > i2) {
		//matrix1의 데이터 보관수가 i1 보다 클때까지만 해야된다, 그렇지 않으면 data 의 이상한 값도 저장되기 때문
		//마찬가지로 i2 도 matrix2 의 데이터 보관수보다 작을때 까지만 해야된다.
		Matrix1Postion = matrix1.data[i1].row * matrix1.cols + matrix1.data[i1].col; //받아온 희소행렬 a matrix1 의 위치 
		Matrix2Postion = matrix2.data[i2].row * matrix2.cols + matrix2.data[i2].col; //받아온 희소행렬 b matrix2 의 위치


		if (Matrix1Postion == Matrix2Postion) { //데이터가 같은 row 값 col 값일 경우
			temp.data[it].col = matrix1.data[i1].col;	//matrix1 이나 2 의 col 값 할당
			temp.data[it].row = matrix1.data[i1].row;//matrix1 이나 2 의 row 값 할당
			temp.data[it].value = matrix1.data[i1].value + matrix2.data[i2].value; //matrix1 과 2 의 더한값 할당
			i1++, i2++, it++; //matrix1 의 i1 데이터 matrix2 의 i2 데이터를 사용했으므로 증가
			//it 도 마찬가지로 데이터를 옆에 저장해야하므로 1 증가

		}
		//row 가 다른 경우, col 값은 볼 필요가 없다.
		else if (Matrix1Postion > Matrix2Postion) { //데이터가 다른 row 값 col 값일 경우, matrix1 이 더 뒤에 있는경우다.
			//해당 케이스는 2 1 3 과 1 8 2 인 경우인데
			//1 8 2 가 저장되어야되므로 matrix2.data[i2] 정보가 그대로 가야된다.
			temp.data[it].col = matrix2.data[i2].col; //matrix2 의 col 데이터 할당
			temp.data[it].row = matrix2.data[i2].row;	//matrix2 의 row 데이터 할당
			temp.data[it].value = matrix2.data[i2].value;	//matrix2 의 value 데이터 할당
			i2++, it++;	//matrix2 의 i2 인덱스는 사용했으므로 1 증가
			//it 도 마찬가지로 데이터를 옆에 저장해야하므로 1 증가

		}
		else {
			//해당 케이스는 1 8 2 과 2 8 2 인 경우인데
			//1 8 2 가 저장되어야되므로 matrix1.data[i2] 정보가 그대로 가야된다.
			temp.data[it].col = matrix1.data[i1].col;//matrix1 의 col 데이터 할당
			temp.data[it].row = matrix1.data[i1].row;//matrix1 의 row 데이터 할당
			temp.data[it].value = matrix1.data[i1].value;//matrix1 의 value 데이터 할당
			i1++, it++;//matrix2 의 i2 인덱스는 사용했으므로 1 증가
			//it 도 마찬가지로 데이터를 옆에 저장해야하므로 1 증가
		}


	}
	temp.terms = it; //it 이 데이터가 증가될때마다 증가되므로 terms 는 it 와 같다.
	return temp;//반환할 구조체 temp 를 반환한다.

}
void print(sparse_matrix matrix) {//구조체를 출력하는 함수 print 인자로는 matrix 를 받는다.

	int index = 0;	//matrix.data 의 index 를 설정해준다.



	for (int i = 0; i < matrix.rows; i++) { //받아온 matrix 의 row 만큼,
		for (int j = 0; j < matrix.cols; j++) { //받아온 matrix 의 col 만큼 반복한다.
			if (matrix.data[index].row == i && matrix.data[index].col == j) { //만약 matrix data 의 index 번쨰의 row 와 col 이 i j 일 경우
				printf("%d ", matrix.data[index].value); //데이터가 있다는 말이므로 출력한다.
				index++; //index 를 늘려 옆 배열을 확인한다.
			}
			else {
				printf("0 "); //그렇지 않으면 0을 출력한다.
			}
		}
		printf("\n");
	}

}