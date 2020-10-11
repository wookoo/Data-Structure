#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int weight; //우선순위
    char ch; //가진 문자
    struct Node* left; //좌측노드
    struct Node* right; //우측노드
}Node; //구성할 트리

typedef struct {
    Node* pTree;
    int key; //우선순위, 더한 값
    char ch; //더한값의 우선순위
}element; //힙에 삽입될 데이터
typedef struct {
    element heap[200];
    int heapSize;
}Heap;

typedef struct {
    char code[100];
    char ch;
}dict; //알파벳에 대응하는 허프만코드를 저장하는 구조체

typedef Heap* HeapPtr; //힙 포인터 정의

//함수 원형 정의부
void initHeap(HeapPtr h);
void insertMinHeap(HeapPtr h, element data);
element deleteMinHeap(HeapPtr h);
Node* makeTree(Node* left, Node* right);
void deleteTree(Node* root);
int isLeaf(Node* root);
element huffmanTree(int freq[], char ch_list[], int n);
int* getFrequency();
void writeCode(FILE* file, Node* root, int codes[], int top);
void preorder(Node* root);
int* getCodes();
void makeEncodedMsg(dict* codes, int codesSize);
void makeDecodedMsg(Node* root);
void makeFrequencyText();

//함수 원형 정의부 끝
void makeRandomText() {
    printf("-----랜덤 huff.txt 생성-----\n");
    FILE* huff = fopen("huff.txt", "w");
    srand(time(NULL));
    int newline = rand() % 30 + 4; //4줄~33줄 사이
    for (int i = 0; i < newline; i++) {
        int lines = rand() % 30 + 8;//한줄에 알파벳8개 이상 37개 이하
        for (int j = 0; j < lines; j++) {
            int t = rand() % 28 + 'a';//랜덤 알파벳

            t = t == 'z' + 1 ? ' ' : t; //공백인경우
            t = t == 'z' + 2 ? '.' : t;  //점인경우
            printf("%c", t);

            fprintf(huff, "%c", t);//파일에 작성
        }
        printf("\n");
        fprintf(huff, "\n");
    }
    fclose(huff);
    printf("---------------\n");
    printf("-----랜덤 msg.txt 생성-----\n");
    FILE* msg = fopen("msg.txt", "w");
    newline = rand() % 5 + 4;
    for (int i = 0; i < newline; i++) {
        int lines = rand() % 9 + 8;//한줄에 알파벳9 이상 8개 이하
        for (int j = 0; j < lines; j++) {
            int t = rand() % 28 + 'a';//랜덤 알파벳

            t = t == 'z' + 1 ? ' ' : t;//공백인경우
            t = t == 'z' + 2 ? '.' : t;//점인경우
            printf("%c", t);

            fprintf(msg, "%c", t);//파일에 작성
        }
        printf("\n");
        fprintf(msg, "\n");
    }
    fclose(msg);
    printf("---------------\n");

}



int main() {
  
    makeRandomText();
    makeFrequencyText();//빈도수 파일 생성
    printf("빈도수 파일 생성 끝\n");
   
    int* frequencyData = getFrequency(); //가져올 데이터는 배열임으로 frequencyData 를 포인터로 선언
    int* count_arr = frequencyData[0]; //빈도수 데이터, 빈도는 숫자임으로 int 포인터
    char* ch_arr = frequencyData[1]; //알파벳 데이터, 알파벳은 char 임으로 char 포인터
    int index = frequencyData[2]; //데이터의 총 갯수, index 는 그냥 int 임으로 int 로 설정
    printf("빈도수 파일 에서 빈도수 읽어옴\n");
    free(frequencyData); //데이터를 다 받아왔으면, 운영체제에 메모리 반환

    element e = huffmanTree(count_arr, ch_arr, index); //허프만 트리로 생성된 노드
    printf("허프만 코드 생성 끝\n");
  
    printf("---------노드의 전위 순회------------\n");
    int newline = 1;
    preorder(e.pTree,&newline);//노드의 전위 순회
    printf("\n--------노드의 전위 순회 끝---------\n");
    printf("----------허프만 코드 생성 시작------\n");
    int codes[100]; //허프만 코드를 저장할 배열
    FILE* codesFile = fopen("codes.txt", "w"); //파일 포인터 생성
    if (codesFile == NULL) {
        printf("파일 생성 실패");
        exit(0);
    }
    writeCode(codesFile, e.pTree, codes, 0); //파일 작성 함수 실행
    fclose(codesFile);
    printf("--------허프만 코드 생성 끝------------\n");
    int* codesData = getCodes(); //가져올 값은 2개 이상임으로 codesData 를 포인터로 선언
    dict* codesDict = codesData[0]; //알파벳 : 허프만 코드 데이터
    int codesDictSize = codesData[1]; //저장된 알파벳 갯수
    printf("인코딩 실행\n");
    makeEncodedMsg(codesDict, codesDictSize);
    printf("인코딩 끝\n");
    printf("--------디코딩 시작-------\n");
    makeDecodedMsg(e.pTree);
    printf("\n--------디코딩 끝-------\n");
    free(codesData);
    

    return;
}
void initHeap(HeapPtr h) { //힙 초기화
    //힙의 크기를 0으로 설정해서 초기화 해준다.
    h->heapSize = 0;
}

void insertMinHeap(HeapPtr h, element data) { //힙에 삽입하는 함수
    int i = ++(h->heapSize);//힙이 삽입되므로 1 추가
    //맨 아래에 삽입해야 함으로 i 는 최하단 위치
    while ((i != 1) && (data.key < h->heap[i / 2].key)) {
        //부모가 더 크면 교환을 계속 진행한다.
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = data; //정위치를 찾았으면 데이터를 삽입
}
element deleteMinHeap(HeapPtr h) { //최소힙 삭제
    int parent, child; //부모 자식 노드의 인덱스
    element data, temp; 
    data = h->heap[1]; //삭제 당할 노드
    temp = h->heap[(h->heapSize)--]; //상위로 올릴노드
    //삭제가 되면 노드가 한개 삭제됨으로, h->heap_size 에 1을 뺀다.
    parent = 1;//부모 노드의 위치
    child = 2;//자식 노드의 위치. paret *2 가 자식노드임
    while (child <= h->heapSize) { //자식노드는 힙에 저장된 값을 넘어가면 종료해야함.
        if ((child < h->heapSize) && h->heap[child].key > h->heap[child + 1].key) {
            child++; //자식 노드중, 우측 노드가 더 작으면 1을 더하여
            //우측 노드로 설정
        }
        if (temp.key < h->heap[child].key) { //임시 노드가 제 위치를 찾아갔으면, 종료
            break;
        }
        h->heap[parent] = h->heap[child]; //부모 노드랑 자식 노드랑 교환
        parent = child; //부모 노드랑 자식 노드랑 교환
        child *= 2;
    }
    h->heap[parent] = temp; //현재 부모 위치에 temp 를 씌워서
    //값을 정상적으로 설정
    return data;
}
Node* makeTree(Node* left, Node* right) { //트리를 생성한후 반환
    Node* n = (Node*)malloc(sizeof(Node)); 
    n->left = left;
    n->right = right;
    return n;
}
void deleteTree(Node* root) {//트리 삭제 함수, 하위 노드 모두 삭제
    if (root == NULL) { //입력값이 NULL 이면 종료
        return;
    }
    deleteTree(root->left); //하위노드 순환 호출로 모두 삭제
    deleteTree(root->right);
    free(root); //동적할당된 root 노드의 메모리를 운영체제에게 반환
}
int isLeaf(Node* root) {//잎노드 인지 확인
    return !(root->left) && !(root->right); //좌노드가 없고 우노드가 없어야함!
}




element huffmanTree(int freq[], char ch_list[], int n) { //허프만 트리 생성
    Node* node, * x;//생성할 노드, 더할 노드
    HeapPtr h; //힙포인터
    element e1, e2, e3; //힙에서 꺼내올 노드

    h = (Heap*)malloc(sizeof(Heap));//힙 생성

    initHeap(h); //힙 초기화
    for (int i = 0; i < n; i++) { //받아온 문자와 빈도로 힙 구성
        node = makeTree(NULL, NULL); //노드를 생성하고
        e1.ch = node->ch = ch_list[i]; //노드에 문자 설정
        e1.key = node->weight = freq[i]; //노드에 빈도 설정
        e1.pTree = node; //e1 의 트리는 생성된 노드
        insertMinHeap(h, e1); //힙에 삽입
    }
    for (int i = 1; i < n; i++) {
        e2 = deleteMinHeap(h); //최소힙에서 값 한개 삭제
        e3 = deleteMinHeap(h); //최소힙에서 값 한개 삭제
        x = makeTree(e2.pTree, e3.pTree); //삭제된 두개로 트리 생성
        e1.key = x->weight = e2.key + e3.key; //노드 두개의 빈도수 합치기
        e1.pTree = x; //e1 의 트리는 합쳐진 노드
        //값이 정상적으로 합쳐지나 확인
        insertMinHeap(h, e1);//힙에 또 삽입하여 1개 남을때 까지 반복
    }
    e1 = deleteMinHeap(h); //힙에 값이 하나 남았으면 그게 완성된 트리
    free(h);//힙 사용끝났음으로 운영체제에게 메모리 반환
    return e1; //트리 반환
}



int* getFrequency() {
    FILE* freqFile;
    freqFile = fopen("freq.txt", "r"); //파일을 읽기전용으로 가져옴
    if (freqFile == NULL) { //파일을 못읽으면
        printf("파일 읽기 실패");
        exit(0);//프로그램 종료
    }
    int count;
    char ch, temp;
    int* countArr = (int*)malloc(sizeof(int) * 300); //int 형 데이터 300개를 담는 배열 선언
    char* chArr = (char*)malloc(sizeof(char) * 300); //char 형 데이터 300개를 담는 배열 선언
    int index = 0;
    while (!feof(freqFile)) {
        fscanf(freqFile, "%c %c %d", &ch, &temp, &count);//파일은 알파벳 : 빈도순으로 이뤄져있음
        //그렇기 때문에 fscanf 를 사용하여 ch temp count 에 각각 알파벳, :, 빈도 저장
        fgetc(freqFile);//라인에 끝엔 개행문자가 있으므로 개행문자 소거
        countArr[index] = count;//countArr 에 가져온 빈도수 할당
        chArr[index++] = ch;//chArr 에 가져온 알파벳 할당
    }
    countArr = (int*)realloc(countArr, sizeof(int) * index); //realloc 으로 사용하지 않는 공간 반환
    chArr = (char*)realloc(chArr, sizeof(char) * index);//realloc 으로 사용하지 않는 공간 반환
    int* returnArr = (int*)malloc(sizeof(int*) * 3); //반환해야할 데이터는 3개임으로 반환할 데이터의 포인터
    //반환할 데이터의 3개중 2개는 포인터 임으로 int 포인터 저장하는 배열 3개
    //반환할 데이터 중 한개는 그냥 int 형이기 때문에 나중에 타입변경
    returnArr[0] = countArr; //빈도수 데이터
    returnArr[1] = chArr; //알파벳 데이터
    returnArr[2] = index; //배열의 총 길이
    return returnArr; //데이터 3개를 반환

}
void writeCode(FILE* file, Node* root, int codes[], int top) {
    //파일포인터는 한개만 필요함으로 codesFile 에 생성한 파일포인터넣음
    //순환호출로 코드 출력
    if (root->left) { //왼쪽 간선을 탈수 있으면,
        codes[top] = 1; //코드에 1 부여
        writeCode(file, root->left, codes, top + 1);
        //순환 호출로 다음 간선을 탄다.
    }
    if (root->right) {//오른쪽 간선을 탈수 있으면
        codes[top] = 0; //코드에 0을 부여
        writeCode(file, root->right, codes, top + 1);
        //순환 호출로 다음 간선을 탄다.
    }
    if (isLeaf(root)) { //단말노드면출력 
        //단말노드에만 정보가 있기때문에 정보 출력
        fprintf(file, "%c : ", root->ch); //fprintf 로 단말노드의 글자를 파일에 작성

        printf("%c : ", root->ch);
        for (int i = 0; i < top; i++) {
            printf("%d", codes[i]);
            fprintf(file, "%d", codes[i]);
        }//fprintf 로 간선을 타고 내려오며 생긴 코드를 파일에 작성
        fprintf(file, "\n");

        printf("\n");
    }
}

void preorder(Node* root,int *newline) {//전위순회,개행라인 변수
   
    if (root == NULL) {//루트가 없다면
        return;//종료
    }
    printf("%d\t",root->weight);//루트가 가진 값 출력
    if (*newline % 5 == 0) {
        printf("\n");//5행씩 개행
    }
    *newline = *newline + 1;
    preorder(root->left, newline); //재귀적 호출
    preorder(root->right, newline);
}

int* getCodes() {
    FILE* cdoesFile;
    cdoesFile = fopen("codes.txt", "r"); //파일을 읽기전용으로 가져옴
    if (cdoesFile == NULL) { //파일을 못읽으면
        printf("파일 읽기 실패");
        exit(0);//프로그램 종료
    }
    dict* codes = (dict*)malloc(sizeof(dict) * 200); //알파벳 : 허프만 코드를 저장할 배열,
    //해시 테이블 구조사용
    int index = 0;
    char string[100];
    char temp; //파일에서 읽어온 ':' 를 저장할 변수

    while (!feof(cdoesFile)) {
        fscanf(cdoesFile, "%c %c %s", &codes[index].ch, &temp, string);//파일은 알파벳 : 빈도순으로 이뤄져있음
        //그렇기 때문에 fscanf 를 사용하여 ch temp count 에 각각 알파벳, :, 빈도 저장
        fgetc(cdoesFile);//라인에 끝엔 개행문자가 있으므로 개행문자 소거
        strcpy(codes[index].code, string); //strcpy 함수로 codes[index] 번째의 code 에 string 을 복사
        index++;
    }
    codes = (dict*)realloc(codes, sizeof(dict) * index); //파일에 추가가 끝났으면
    //realloc 으로 사용하지 않는 공간 반환

    int* returnValue = (int*)malloc(sizeof(int*) * 2); //반환할 데이터는 두개
    //반환할 데이터의 1개는 포인터 임으로 int 포인터 저장하는 배열 2개
    //반환할 데이터 중 한개는 그냥 int 형이기 때문에 나중에 타입변경
    returnValue[0] = codes; //0번짼 생성된 해시 테이블 포인터 즉, 배열
    returnValue[1] = index - 1;  //1번짼 생성된 index 값
    return returnValue;
}
void makeEncodedMsg(dict* codes, int codesSize) {
    FILE* encodedFile = fopen("encodedMsg.txt", "w");
    FILE* msgFile = fopen("msg.txt", "r");
    if (encodedFile == NULL || msgFile == NULL) {
        printf("파일 열기 실패");
        exit(0);
    }
    char ch;
    while ((ch = fgetc(msgFile)) != EOF) {
        ch = ch == ' ' ? '-' : ch;
        ch = ch == '\n' ? '!' : ch;
        for (int i = 0; i < codesSize; i++) {
            if (ch == codes[i].ch) {
                fprintf(encodedFile, "%s", codes[i].code);
                break;
            }
        }
    }
    fclose(encodedFile);//파일 읽기 쓰기 종료
    fclose(msgFile);

}
void makeDecodedMsg(Node* root) {//허프만 트리를 읽어옴
    FILE* encodedFile = fopen("encodedMsg.txt", "r"); //인코딩된 메세지는 읽기전용
    FILE* decodedFile = fopen("decodedMsg.txt", "w"); //디코딩된 메세지는 쓰기전용
    if (encodedFile == NULL || decodedFile == NULL) {//파일읽기 실패하면
        printf("파일 열기 실패"); //프로그램종료
        exit(0);
    }
    Node* now = root; //루트에서 간선을 타고 내려와야 함으로 현재위치는 루트
    char ch;
    while ((ch = fgetc(encodedFile)) != EOF) {//파일끝이 아닐떄까지 하나씩 읽어온다


        if (ch == '0') { //읽어온 코드가 0이면
            now = now->right; //우측 간선을 타고 내려간다
        }
        else {//읽어온 코드가 1이면
            now = now->left; //좌측 간선을 타고 간다.
        }
        if (isLeaf(now)) { //간선을 타고 내려갔는데 노드가 잎노드면
            //글자가 있는것.
            char temp = now->ch; //출력변수
            temp = temp == '-' ? ' ' : temp; //출력할 기호가 - 면 ' ' 으로치환
            temp = temp == '!' ? '\n' : temp; //출력할 기호가 ! 면 \n 로 치환
            fprintf(decodedFile, "%c", temp); //파일에 디코딩 결과 작성
            printf("%c", temp); //콘솔에 출력
            now = root;//간선을 타고 못내려가니 다시 root 로 설정
        }
    }
    fclose(encodedFile); //파일 읽기 쓰기 종료
    fclose(decodedFile);

}
void makeFrequencyText() {
    FILE* referenceFile;
    referenceFile = fopen("huff.txt", "r");//문장이 적혀있는 파일
    if (referenceFile == NULL){ //파일을 여는걸 실패하면 프로그램 종료
        printf("파일 읽기 실패");
        exit(0);
    }
    int freq['z' - 'a' + 5] = { 0 }; //'z' 의 아스키코드에서 'a' 를 빼면
    //a~z 알파뱃 갯수-1 이 나옴, EOF 랑 개행 마침표 공백 총 4개 필요함으로
    //+5로 설정
    char c; //파일을 한글자씩 읽기위해 변수 c 선언
    while ((c = fgetc(referenceFile)) != EOF) {//읽은 파일이 EOF 즉, 파일 끝이면 종료
        if (c == ' ') {//읽은게 공백이면
            freq['z' - 'a' + 1] += 1; //공백, - 빈도수 1 추가
        }
        else if (c == '\n') {//읽은게 점이면
            freq['z' - 'a' + 2] += 1; //새줄, 느낌표 빈도수 1 추가
        }
        else if (c == '.') {//읽은게 점이면
            freq['z' - 'a' + 3] += 1; //마침표, 점 빈도수 1 추가
        }
        else {//그외에 읽은게 a~z 면
            freq[c - 'a'] += 1; //a인경우 0번째 인덱스에 빈도를 저장해야함으로
            //'a'아스키 코드를 빼줌, b 인경우 1번째 인덱스여야 함으로 'a' 를 뺌

        }

    }
    if (c == EOF) { //while 문이 끝나면 항상 수행됨
        freq['z' - 'a' + 4] += 1;//파일끝 빈도수 1 추가
    }
    fclose(referenceFile);//파일을 다 읽었기 때문에 파일을 닫음
    FILE* freqFile = fopen("freq.txt", "w");//새로 작성해함으로 w 옵션
    if (freqFile == NULL) { //파일생성을 못하면
        printf("파일 생성 실패\n");//프로그램 종료
        exit(0);
    }
    for (int i = 0; i <= 'z' - 'a'; i++) { //a~z 의 갯수만큼 반복
        fprintf(freqFile, "%c : %d\n", i + 'a', freq[i]);
        //fprintf로 freq.txt 에 글자 : 빈도 를 적는다
        //%c 에서 i 가 0일때 a 이여야 함으로 'a' 를 더함
    }
    fprintf(freqFile, "- : %d\n", freq['z' - 'a' + 1]);//공백 개행 마침표 느낌표 직접 설정
    fprintf(freqFile, "! : %d\n", freq['z' - 'a' + 2]);
    fprintf(freqFile, ". : %d\n", freq['z' - 'a' + 3]);
    fprintf(freqFile, "+ : %d\n", freq['z' - 'a' + 4]);

    fclose(freqFile);//파일 생성 다됬으면 종료

}
