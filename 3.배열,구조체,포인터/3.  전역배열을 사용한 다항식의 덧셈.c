#include <stdio.h>
#define MAXSIZE 101
typedef struct {
	int coef;
	int expon;
}poly;

poly terms[MAXSIZE] = { {8,3},{7,1},{1,0},{10,3},{3,2},{1,0} };
int avail = 6;
void insert(int coef, int expon) {
	if (avail > MAXSIZE) {
		printf("더이상 삽입 불가!");
		exit();
	}
	terms[avail].coef = coef;
	terms[avail++].expon = expon;
}

void add_poly(int AS, int AE, int BS, int BE, int *CS, int *CE) {
	*CS = avail;
	int tempCoef;
	while (AS <= AE && BS <= BE) {
		if (terms[AS].expon == terms[BS].expon) {
			tempCoef = terms[AS].coef + terms[BS].coef;
			insert(tempCoef, terms[AS].expon);
			AS++; BS++; 
		}
		else if (terms[AS].expon > terms[BS].expon) {
			tempCoef = terms[AS].coef;
			insert(tempCoef, terms[AS].expon);
			AS++; 
		}
		else {
			tempCoef = terms[BS].coef;
			insert(tempCoef, terms[BS].expon);
			BS++;
		}


	}

	*CE = avail - 1;

}

void printPoly(int s, int e) {
	for (int i = s; i < e; i++) {
		if (terms[i].expon != 1) {
			printf("%dx^%d+", terms[i].coef, terms[i].expon);
		}
		else {
			printf("%dx+", terms[i].coef);
		}
		
	}

	printf("%d\n", terms[e].coef, terms[e].expon);
}

int main(void) {
	printPoly(0, 2);
	printf("----------------------------------\n");
	printPoly(3, 5);
	int Cs;
	int Ce;
	add_poly(0, 2, 3, 5, &Cs, &Ce);
	printf("----------------------------------\n");
	printPoly(Cs, Ce);
}
