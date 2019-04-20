#include <stdio.h>
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MAX_DEGREE 101
typedef struct {
	int degree;
	double coef[MAX_DEGREE];
}polynomial;

polynomial Add(polynomial a, polynomial b) {
	polynomial temp;
	int indexA = 0,indexB = 0,indexT = 0;
	int degreeA = a.degree;
	int degreeB = b.degree;
	temp.degree = MAX(degreeA, degreeB);
	while (indexA <= a.degree && indexB <= b.degree) {  
	//수정하기 전 while 조건식은 indexA <= degreeA && indexB <= degreeB 였다... degreeA 와 B 는 while 을 돌면서 줄어드니 실수를 하면 안된다.
		if (degreeA > degreeB) {
			temp.coef[indexT++] = a.coef[indexA++];
			degreeA--;
		}
		else if (degreeA == degreeB) {
			temp.coef[indexT] = a.coef[indexA] + b.coef[indexB];
			degreeA--;
			degreeB;;

		}
		else {
			temp.coef[indexT++] = b.coef[indexB++];
			degreeB--;
			degreeA--;
		}
	}
	return temp;
}

void printPoly(polynomial poly) {
	for (int i = poly.degree; i > 0; i--) {
		printf("%3.2fX^%d + ", poly.coef[poly.degree - i], i);
	}
	printf("%3.2f\n", poly.coef[poly.degree-1]);
}
int main() {
	polynomial p1 = { 5,{1,2,3,3,6,10} };
	polynomial p2 = { 4,{7,0,5,0,1} };
	polynomial p3 = Add(p1, p2);
	//printf("%d", p3.degree);
	printPoly(p1);
	printPoly(p2);
	printf("----------------------\n");
	printPoly(p3);
}
