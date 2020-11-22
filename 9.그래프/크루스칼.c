#include <stdio.h>
#define MAX_HEAP 1000 //힙의 최대 크기
#define MAX_VERTICES 100 //최대 삽입할 정점수

int parent[MAX_VERTICES]; //집합에 저장할 

typedef struct { //간선정보 구조체
	int start; //시작 정점
	int end; //끝 정점
	int weight; //가중치 
}edge;

typedef struct graph {
	int v;//정점의 갯수
	int n;//간선의 갯수
	edge edges[2 * MAX_VERTICES]; //간선의 최대갯수는 최대정점수 * 2
}graph;
typedef graph* graph_ptr;

typedef struct {
	edge arr[MAX_VERTICES];
	int size;
}set; //반환할 신장트리의 간선 집합



typedef edge element; //힙에 들어갈 데이터, element
typedef struct heap {
	element heap[MAX_HEAP]; 
	int heap_size;
}heap;//힙타입 정의

typedef heap* heap_ptr;

//함수 원형 정의부
void heap_init(heap_ptr h);
heap_ptr create_heap();
void insert_min_heap(heap_ptr h, element item);
element delete_min_heap(heap_ptr h);
void set_init(int n);
int set_find(int curr);
void set_union(int a, int b);
void insert_vertex(graph_ptr g, int v);
void graph_init(graph_ptr g);
void insert_edge(graph_ptr g, int start, int end, int weight);
set kruskal(graph_ptr g);
void print(set s);
void gen_graph(graph_ptr g);
//함수 원형 정의부 끝

int main() {

	graph_ptr g;
	g = (graph_ptr)malloc(sizeof(graph));
	gen_graph(g); //사용자에게서 입력받아 그래프 생성

	set T = kruskal(g); //크루스칼 알고리즘으로 간선집합 생성
	print(T); //생성된 간선 집합 출력
	gen_graph(g); //두번째 그래프 생성
	T = kruskal(g); //생성된 간선 집합 출력
	print(T);
	free(g);
	return 0;
}

void heap_init(heap_ptr h) { //힙 초기화 함수
	h->heap_size = 0; //힙의 크기를 0으로 설정
}
heap_ptr create_heap() { //힙 생성 함수
	return (heap_ptr)malloc(sizeof(heap)); //동적할당으로 힙 생성후 포인터 반환
}

void insert_min_heap(heap_ptr h,element item) { //최소힙 삽입
	if ((h->heap_size+1) == (MAX_HEAP)) { //힙을 더이상 삽입 불가능하면
		printf("더이상 힙에 삽입할수 없습니다!");
		exit(0); //프로그램 종료
	}
	int i = ++(h->heap_size); //힙이 삽입되므로 1 추가
	//맨 아래에 삽입해야 함으로 i 는 최하단 위치
	while (i != 1 && item.weight < h->heap[i / 2].weight) {
		//부모가 더 크면 교환을 계속 진행한다. 여기선 가중치가 key
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;//정위치를 찾았으면 데이터를 삽입
}

element delete_min_heap(heap_ptr h) {//최소힙 삭제
	if (h->heap_size == 0) { //힙을 삭제할수 없으면
		printf("더이상 힙을 삭제할수 없습니다!"); //오류, 프로그램 종료
		exit(0);
	}
	int parent, child; //부모 자식 노드의 인덱스
	element item, temp;
	item = h->heap[1]; //삭제 당할 노드
	temp = h->heap[(h->heap_size)--]; //상위로 올릴노드
	//삭제가 되면 노드가 한개 삭제됨으로, h->heap_size 에 1을 뺀다.
	parent = 1;//부모 노드의 위치
	child = 2;//자식 노드의 위치. paret *2 가 자식노드임
	while (child <= h->heap_size) { //자식노드는 힙에 저장된 값을 넘어가면 종료해야함.
		if (child < h->heap_size && h->heap[child].weight > h->heap[child + 1].weight) { //가중치가 여기선 key
			//자식 노드중, 우측 노드가 더 작으면 1을 더하여 우측노드로 설정
			child++;
		}
		if (temp.weight <= h->heap[child].weight) { //임시 노드가 제 위치를 찾아갔으면, 종료
			break;
		}
		h->heap[parent] = h->heap[child];//부모 노드랑 자식 노드랑 교환
		parent = child; //부모 노드랑 자식 노드랑 교환
		child *= 2;
	}
	h->heap[parent] = temp; //현재 부모 위치에 temp 를 씌워서 값을 정상적으로 설정
	return item; //반환할 데이터 반환
}


void set_init(int n) {//집합 초기화
	if (n + 1 == MAX_VERTICES) { //초기화 가능한 집합수보다 입력값이 크면
		printf("초기화 할수 없습니다."); //프로그램 에러후 종료
		exit(0);
	}
	for (int i = 0; i < n; i++) { //초기화 된경우 집합이 모두 -1 로 초기화된경우
		parent[i] = -1;
	}
}
int set_find(int curr) { //요소가 집합에 어디있는지 찾는 함수
	if (parent[curr] == -1) {
		return curr;
	}

	while (parent[curr] != -1) { //curr 의 부모가 -1 이 아니면
		curr = parent[curr]; //curr 은 부모를 찾아간다
	}
	return curr; //그후 curr 반환
}

void set_union(int a, int b) { //요소를 합집합 시키는것
	int r1 = set_find(a); //요소 두개의 집합을 가져온다
	int r2 = set_find(b);
	if (r1 != r2) { //요소 두개가 같은집합이 아니면
		parent[r1] = r2; //요소를 합친다
	}
}


void insert_vertex(graph_ptr g,int v) {
	if ((g->v) + 1 > MAX_VERTICES) {
		printf("그래프에 정점을 더 삽입할수 없습니다.");
		exit(0);
	}
	g->v++;
}
void graph_init(graph_ptr g) { //그래프 초기화
	g->v = 0; //그래프의 정점수 초기화
	g->n = 0; //그래프의 간선수 초기화
	for (int i = 0; i < 2 * MAX_VERTICES; i++) { //그래프의 간선정보 초기화
		g->edges[i].start = 0;
		g->edges[i].end = 0;
		g->edges[i].weight = -1;
	}
}


void insert_edge(graph_ptr g, int start, int end, int weight) {//간선 삽입 함수
	g->edges[g->n].start = start; //간선 시작점
	g->edges[g->n].end = end; //끝점
	g->edges[g->n].weight = weight; //가중치 설정
	g->n++; //정점 하나 추가
}

set kruskal(graph_ptr g) { //크루스칼 알고리즘

	int edge_select = 0; //선택된 정점수
	int uset, vset;
	edge e; //최소힙 삭제 요소
	set_init(g->v); //정점 정보 집합 초기화
	heap_ptr h = create_heap(); //힙 생성
	heap_init(h); //힙 초기화
	for (int i = 0; i < g->n; i++) {
		insert_min_heap(h, g->edges[i]); //그래프의 모든 간선을 힙에 삽입
	}
	set result; //반환할 데이터
	while (edge_select < (g->v-1)){ //신장트리 간선수 = 정점수 -1 이다.
		
		e = delete_min_heap(h); //최소힙 삭제, 가중치가 가장 작은값 나옴
		uset = set_find(e.start); //최소힙 삭제 값의 start 의 집합을 찾음
		vset = set_find(e.end); //최소힙 삭제 값의 end 의 집합을 찾음
		if (uset != vset) { //만약 start 와 end 의 집합이 다른경우 싸이클이 생성되지 않았으므로
			
			result.arr[edge_select] = e; //신장트리 정점 집합에 e 추가
			edge_select++; //선택간선수 1증가
			set_union(vset, uset); //정점 두개의 집합을 합침
		}
	}
	result.size = edge_select; //선택된 간선수 할당후
	free(h);
	return result; //반환
}

void print(set s) { //간선 집합 출력
	printf("------------\n");
	int sum = 0;
	for (int i = 0; i < s.size; i++) {
		//모든 간선 집합을 출력한다
		printf("정점 %d - %d, 가중치 : %d 선택\n", s.arr[i].start, s.arr[i].end, s.arr[i].weight);
		sum += s.arr[i].weight;
	}
	printf("가중치 총 합 : %d\n", sum);
	printf("------------\n");
}

void gen_graph(graph_ptr g) {
	graph_init(g); //그래프 초기화
	int v, edges;


	printf("삽입할 정점의 갯수 : ");
	scanf("%d", &v);
	printf("삽입할 간선 수 : ");
	scanf("%d", &edges);

	for (int i = 0; i < v; i++) { //입력받은 갯수만큼 정점 생성
		insert_vertex(g, i);
	}
	for (int i = 0; i < edges; i++) {
		printf("%d 번째 간선 입력 (V1,V2,weight) : ", i + 1);
		int v1, v2, weight;
		scanf("%d %d %d", &v1, &v2, &weight); //간선정보를 사용자에게 입력받고
		insert_edge(g, v1, v2, weight); //간선을 삽입
	}
	/* 입력1
	insert_edge(g, 0, 1, 29);
	insert_edge(g, 1, 2, 16);
	insert_edge(g, 2, 3, 12);
	insert_edge(g, 3, 4, 22);
	insert_edge(g, 4, 5, 27);
	insert_edge(g, 5, 0, 10);
	insert_edge(g, 6, 1, 15);
	insert_edge(g, 6, 3, 18);
	insert_edge(g, 6, 4, 25);
	*/

	/* 입력2
	insert_edge(g, 0, 1, 10);
	insert_edge(g, 0, 3, 6);
	insert_edge(g, 0, 7, 1);
	insert_edge(g, 1, 2, 4)
	insert_edge(g, 1, 5, 2);
	insert_edge(g, 2, 5, 7);
	insert_edge(g, 2, 3, 11);
	insert_edge(g, 3, 7, 3);
	insert_edge(g, 4, 5, 5);
	insert_edge(g, 4, 7, 8);
	insert_edge(g, 5, 6, 9);
	insert_edge(g, 6, 7, 12);
	*/
}
