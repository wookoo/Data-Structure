#include <stdio.h>
#define ARRAY_MAX 100
#define MAZE_SIZE 6
typedef struct {
	short r;
	short c;
}element;
typedef struct {
	element data[ARRAY_MAX];
	int top;
}stack;

char maze[MAZE_SIZE][MAZE_SIZE] = {
	{'1','1','1','1','1','1'},
	{'e','0','1','0','0','1'},
	{'1','0','0','0','1','1'},
	{'1','0','1','0','1','1'},
	{'1','0','1','0','0','x'},
	{'1','1','1','1','1','1'}
};


element here = { 1,0 }, entry = { 1,0 };

typedef stack* stack_ptr;

void init(stack_ptr Stack) {
	Stack->top = -1;
}

int is_empty(stack Stack) {
	return (Stack.top == -1);
}
int is_full(stack Stack) {
	return (Stack.top == ARRAY_MAX - 1);
}
element peek(stack Stack) {
	if (is_empty(Stack) != 1) {
		return (Stack.data[Stack.top]);
	}
	else {
		printf("값이 없어 peek 을 수행할수 없습니다.");
		exit();
	}
}
void push(stack_ptr Stack,element data) {
	if (is_full(*Stack)) {
		printf("더이상 값을 추가할수 없습니다.");
		exit(1);
	}
	
	Stack->data[++(Stack->top)] = data;
}

element pop(stack_ptr Stack) {
	if (is_empty(*Stack)) {
		printf("더이상 값을 지울 수 없습니다.");
		exit(1);
	}
	element data = Stack->data[(Stack->top)];
	Stack->top -= 1;
	return data;
}

void push_loc(stack_ptr stack, int r, int c) {
	if (r < 0 || c < 0) return;
	if (maze[r][c] != '1' && maze[r][c] != '.') {
		element temp;
		temp.r = r;
		temp.c = c;
		push(stack, temp);
	}
}

void printMaze(char maze[MAZE_SIZE][MAZE_SIZE]) {
	printf("\n");
	for (int i = 0; i < MAZE_SIZE; i++) {
		for (int j = 0; j < MAZE_SIZE; j++) {
			printf(" %c", maze[i][j]);
		}
		printf("\n");
	}
}

int main() {
	stack a;
	stack* Stack = &a;

	init(Stack);
	here = entry;
	int r;
	int c;
	while (maze[here.r][here.c] != 'x') {
		r = here.r;
		c = here.c;
		maze[r][c] = '.';
		printMaze(maze);
		push_loc(Stack, r - 1, c);
		push_loc(Stack, r + 1, c);
		push_loc(Stack, r, c - 1);
		push_loc(Stack, r, c + 1);
		if (is_empty(*Stack)) {
			printf("실패\n");
			return;
		}
		else {
			here = pop(Stack);
		}
			

	}
	printf("성공\n");
}
