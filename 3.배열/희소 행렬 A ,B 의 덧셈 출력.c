/*
	*	����
	*		��� A,  B�� ���� C ����(�ʱ�ȭ ����)�� �ۼ��϶�. 
	*		(��� Ÿ���� SparseMatrix, ����� �� ��Ҵ� (row, col, val)�� ǥ��)
	*		������ A B �� �޾Ƽ� �� ����� ��ȯ�ϴ� add �Լ��� �ۼ��϶�.

	*	�˰���
	*		1. �������� ǥ�� :
	*			�������� ǥ���� value �� 0 �� �ƴ� ���� ����ü �迭�� ������ �ϸ�ȴ�.
	*			�� �����ʹ� 0 �� �ƴ� value �� row ��, col ���� ������ �ϰ� �ȴ�.
	*			{2,5,4} �� ������ �Ǿ�������, 2�� 5���� 4 ��� ���� �ִٴ� �� �̴�.
	*
	*		2. ������ A + B �� ����
	*			������ A + B �� ������ ����ü �迭�� �����ͼ� �� �ΰ����� ���ϸ� �ȴ�.
	*			������� A �� { 3, 3 ,1},{ 3 , 5 , 4 } �� B �� { 3, 3, 4 }, { 5, 4, 7 } �̶�� ������ ����
	*			������ �迭�� C ��� �ϸ�, A �� ù��°�� 3 3 1 �� B �� ù��°�� 3 3 4 �� �� �ؾ� �Ѵ�.
	*			�� ���̽��� A �� row col �� 3 3 , B ��  rowl col �� 3 3 �̹Ƿ� A B value �� ���� 5�� C �� �����ϸ� �ȴ�.
	*			{ 3, 3 ,5} �̷������� ���̴�.
	*			A �� 3 3 1 B�� 3 3 4 �� ���������Ƿ� ���� A �� 3 5 4 �� B �� 5 4 7 �� ���ϸ� �ȴ�.
	*			row ���� ���� ��� col ���� ���ؾߵǴµ� �̰�� row ���� �ٸ��� ������ �� ���� row �� ����
	*			A �� ���� �״�� C �迭�� ���� �ȴ�. C �迭�� �� {3, 3, 5},{3, 5, 4} �� �ȴ�.
	*			�׷� A �� ��ҵ��� ��� ����� ������ ����, ���� B �迭�� C �迭�� �׳� �������� �ȴ�.
	*			�� �˰����� �����ؼ� ���ϸ�, C �� �ᱹ {3, 3, 5},{3, 5, 4},{5, 4, 7} �� ���� �ȴ�.
	*			�׷��� 3 * 4 , 5 * 2 �迭�� ������ ����ؾ� �Ѵ�. �� ��� row �� 5�� �ǰ� col �� 4 �� �ȴ�.
	*			�ֳ��ϸ� ������ ��� 4 - 2 �� 2��ŭ �迭�� �߰��� �ʿ��ѵ�, 
	*			�̴� �� �����Ͱ� ������ �ǹ��ϰ� 0���� ǥ���� �����ϴ�. �� c �迭�� row �� a b �� row �� ū��
	*			C�迭�� col �� a b �� col �� ū ���� �ȴ�.
	*			�̴� �� add �Լ��� �˰����̴�.
	*
	*		3. ��� ����� ���
	*			�����Ŀ��� terms �� row �� col, data �� �ʵ�� �̷����ִ�.
	*			�������� n ��° �����ʹ� ������ ���� ǥ���� �ϸ� �ȴ�.
	*			n = col * data[index].row + data[index].col
	*			for ���� ����Ͽ� i = col * row ���� �ݺ��� �ϰ�, ���� i ���� n �� ��ġ�ϸ�
	*			n ��° �����͸� ����Ѵ�. ������ i �� col �� ���������� ������ �������� ������ �ϸ� �ȴ�.
	*
	*		���
	*			������ A B �� ���� C �� ���� �迭�� ���·� ����� �ϸ� �ȴ�.
	*			3 �� �˰����� ���� ������ �����ϴ�.
	*
	*		�Լ�
	*			sparse_matrix add(sparse_matrix matrix1, sparse_matrix matrix2) : matrix1 �� matrix2 �� ���� ����ü ��ȯ
	*			void print(sparse_matrix matrix); matrix �迭�� ����ϴ� �Լ�

*/

#include <stdio.h>
#define MAX_TERMS 100 //data  �迭�� �� �ִ� ������ ��ȣ ����� ����
#define ROW 5 //���� ũ�⸦ ��ȣ ����� ����
#define COL 10 //���� ũ�⸦ ��ȣ ����� ����
typedef struct {
	int row;	//�������� row �� �����Ѵ�.
	int col;	//�������� col �� �����Ѵ�.
	int value;	//�����͸� �����Ѵ�.
} element;	//����ü�� element �� Ÿ���� �����Ѵ�.

typedef struct {
	element data[MAX_TERMS];	//MAX_TERMS ��ŭ data�� �ִ� �迭 ���̸� �������ش�.
	int rows;	//���� �� ũ��
	int cols;	//���� �� ũ��
	int terms;	//data �迭�� �� index ��
} sparse_matrix;


sparse_matrix add(sparse_matrix matrix1, sparse_matrix matrix2); //sparse_matrix 2���� �޾� ���ϰ� ��ȯ�ϴ� add �Լ� ���� ����
void print(sparse_matrix matrix); //sparse_matrix �� �޾Ƽ� ����ϴ� print �Լ� ���� ����

int main(void) {
	

	sparse_matrix SparseA = { { { 0, 2, 1 },
	{ 1, 5, 2 },
	{ 3, 1, 3 },
	{ 3, 9, 4 },
	{ 4, 0, 5 },
	{ 4, 4, 6 },
	{ 4, 9, 7 } },5,10,7 };	//SparseA ����ü�� �����ϰ� �ʱ�ȭ��, �����͸� �ִ´�.
	//row �� 5 col �� 10 terms �� 7�̴�.
	sparse_matrix SparseB = { {{ 0, 0, 5 },
	{ 0, 4, 6 },
	{ 0, 9, 7 },
	{ 1, 1, 3 },
	{ 1, 5, 1 },
	{ 1, 9, 4 },
	{ 2, 2, 1 },
	{ 3, 5, 2 },
	{ 4, 4, 1 },
	{ 4, 9, 1 }},5,10,10 };	//SparseB ����ü�� �����ϰ� �ʱ�ȭ��, �����͸� �ִ´�.
	//row �� 5 col �� 10 terms �� 10�̴�.
	sparse_matrix SparseC = add(SparseA, SparseB); //SparseA �� SparseB �� ���ؼ� SpareseC �� �����Ѵ�.
	print(SparseC);	//����� SparseC �� ����Ѵ�.


}



sparse_matrix add(sparse_matrix matrix1, sparse_matrix matrix2) { //���ϰ� ����ü�� ��ȯ�ϱ� ������ sparse_matrix �� ����.
	sparse_matrix temp; //��ȯ�� ����ü ���� 
	int it = 0, i1 = 0, i2 = 0;
	//temp �� index matrix1 �� index matrix2 �� index ���� it  i1 i2 �� �����Ѵ�.
	//index �� �ʱⰪ�� 0�̴�.
	temp.rows = matrix1.rows > matrix2.rows ? matrix1.rows : matrix2.rows;
	//�˰��� ���� �ִ� c �迭�� row �� a b �� row �� ū�� �� �ǹ��Ѵ�.
	
	temp.cols = matrix1.cols > matrix2.cols ? matrix1.cols : matrix2.cols;
	//C�迭�� col �� a b �� col �� ū ���� �ȴ�.


	temp.terms = 0;	//�����Ͱ� 0 �� ���ԵǾ����Ƿ� 0 �̴�.

	while (matrix1.terms > i1 && matrix2.terms > i2) {
		//matrix1�� ������ �������� i1 ���� Ŭ�������� �ؾߵȴ�, �׷��� ������ data �� �̻��� ���� ����Ǳ� ����
		//���������� i2 �� matrix2 �� ������ ���������� ������ ������ �ؾߵȴ�.

		if (matrix1.data[i1].row == matrix2.data[i2].row) { 
			//matrix1 �� matrix2 �� row �� �������, col ���� ���ؾ� �Ѵ�.
			if (matrix1.data[i1].col == matrix2.data[i2].col) {
				//row �� col �� ���� ���, value �� �� ���� ���ؼ� �����ؾ��Ѵ�.
				temp.data[it].col = matrix1.data[i1].col;	//matrix1 �̳� 2 �� col �� �Ҵ�
				temp.data[it].row = matrix1.data[i1].row;//matrix1 �̳� 2 �� row �� �Ҵ�
				temp.data[it].value = matrix1.data[i1].value + matrix2.data[i2].value; //matrix1 �� 2 �� ���Ѱ� �Ҵ�
				i1++, i2++, it++; //matrix1 �� i1 ������ matrix2 �� i2 �����͸� ��������Ƿ� ����
				//it �� ���������� �����͸� ���� �����ؾ��ϹǷ� 1 ����

			}
			else if (matrix1.data[i1].col > matrix2.data[i2].col) {
				//row �� ���� col �� �ٸ� ��� 0 2 1 �� 0 0 1 �� ��츦 ���÷� ���
				// 0 0 1 �� ���� �ǹǷ�  matrix2.data[i2] �� ������ �״�� ���ߵȴ�.
				temp.data[it].col = matrix2.data[i2].col;//matrix2 �� col ������ �Ҵ�
				temp.data[it].row = matrix2.data[i2].row;//matrix2 �� row ������ �Ҵ�
				temp.data[it].value = matrix2.data[i2].value;//matrix2 �� value ������ �Ҵ�
				i2++, it++;//matrix2 �� i2 �ε����� ��������Ƿ� 1 ����
				//it �� ���������� �����͸� ���� �����ؾ��ϹǷ� 1 ����
			}
			else {
				//row �� ���� col �� �ٸ� ��� 0 0 1 �� 0 2 1 �� ��츦 ���÷� ���
				// 0 0 1 �� ���� �ǹǷ�  matrix1.data[i2] �� ������ �״�� ���ߵȴ�.
				temp.data[it].col = matrix1.data[i1].col;//matrix1 �� col ������ �Ҵ�
				temp.data[it].row = matrix1.data[i1].row;//matrix1 �� row ������ �Ҵ�
				temp.data[it].value = matrix1.data[i1].value;//matrix1 �� value ������ �Ҵ�
				i1++, it++;
				//it �� ���������� �����͸� ���� �����ؾ��ϹǷ� 1 ����
			}
		}
		//row �� �ٸ� ���, col ���� �� �ʿ䰡 ����.
		else if (matrix1.data[i1].row > matrix2.data[i2].row) {
			//�ش� ���̽��� 2 1 3 �� 1 8 2 �� ����ε�
			//1 8 2 �� ����Ǿ�ߵǹǷ� matrix2.data[i2] ������ �״�� ���ߵȴ�.
			temp.data[it].col = matrix2.data[i2].col; //matrix2 �� col ������ �Ҵ�
			temp.data[it].row = matrix2.data[i2].row;	//matrix2 �� row ������ �Ҵ�
			temp.data[it].value = matrix2.data[i2].value;	//matrix2 �� value ������ �Ҵ�
			i2++, it++;	//matrix2 �� i2 �ε����� ��������Ƿ� 1 ����
			//it �� ���������� �����͸� ���� �����ؾ��ϹǷ� 1 ����

		}
		else {
			//�ش� ���̽��� 1 8 2 �� 2 8 2 �� ����ε�
			//1 8 2 �� ����Ǿ�ߵǹǷ� matrix1.data[i2] ������ �״�� ���ߵȴ�.
			temp.data[it].col = matrix1.data[i1].col;//matrix1 �� col ������ �Ҵ�
			temp.data[it].row = matrix1.data[i1].row;//matrix1 �� row ������ �Ҵ�
			temp.data[it].value = matrix1.data[i1].value;//matrix1 �� value ������ �Ҵ�
			i1++, it++;//matrix2 �� i2 �ε����� ��������Ƿ� 1 ����
			//it �� ���������� �����͸� ���� �����ؾ��ϹǷ� 1 ����
		}

			
	}
	temp.terms = it; //it �� �����Ͱ� �����ɶ����� �����ǹǷ� terms �� it �� ����.
	return temp;//��ȯ�� ����ü temp �� ��ȯ�Ѵ�.

}
void print(sparse_matrix matrix) {//����ü�� ����ϴ� �Լ� print ���ڷδ� matrix �� �޴´�.

	int index = 0;	//matrix.data �� index �� �������ش�.

	

	
	for (int i = 0; i < matrix.rows * matrix.cols; i++) { // �� �ڷ��� ������ �ǹ�
		int position = (matrix.data[index].row * matrix.cols) + matrix.data[index].col;
		//matrix �� data �� row �� col �� �̿��Ͽ� ���° ���������� Ȯ���Ѵ�.
		if (position == i) { //���� postion ���� i �� ��ġ�Ұ��, 0�� �ƴ� ��Ȳ�� �ǹ��Ѵ�.
			printf("%d ", matrix.data[index].value); //�׷��� ������ ��������ְ�
			index++; //index �� 1 ���������ش�.
		}
	
		else {
			printf("0 "); //else �� ��� postion �� i �� ���� ���� ����.
		}
		
		if (i % matrix.cols == matrix.cols - 1) {	//�������� matrix.cols - 1 ��� �����ؾ� �Ѵ�
			printf("\n");	//�׷��� ������ �����Ѵ�.
		}
		
	}

}