#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Node 구조체 정의
// 각 Node는 키(key)와 최대 3개의 자식 노드(childern)를 가진다.
typedef struct Node {
    int key;    // 노드의 키 값
    struct Node* children[3];   // 노드의 자식 노드들
} Node;

int globalKeyCounter = 0;  // 노드의 키 값을 저장하는 전역변수 정의. 이것은 새 노드를 생성할 때마다 증가한다.

// 새 노드를 동적 할당하여 생성하고 키 값을 부여하는 함수
Node* createNode() {
    Node* newNode = (Node*) malloc(sizeof(Node));  // 새 노드를 위한 메모리 할당
    newNode->key = globalKeyCounter++;  // 새 노드에 전역카운터의 현재 값으로 key를 할당하고 globalKeyCounter를 증가시킨다.
    
    // 새로운 노드의 모든 자식 노드를 NULL로 초기화
    for (int i = 0; i < 3; i++) {
        newNode->children[i] = NULL;
    }

    return newNode;     // 새로 생성된 노드 반환
}

// 랜덤 트리 생성 함수
// 주어진 깊이에서 랜덤한 트리를 생성한다.
Node* createRandomTree(int depth) {
    Node** stack = (Node**) malloc(depth * sizeof(Node*));  // 노드와 노드의 level을 저장하기 위한 스택을 할당
    int* levels = (int*) malloc(depth * sizeof(int));
    Node* root = createNode();  // 루트 노드를 생성하고 스택에 push한다.
    stack[0] = root;
    levels[0] = depth;
    int top = 1;    // 스택의 top을 가리키는 인덱스

    // 스택이 비어있지 않은 동안 반복한다.
    while (top > 0) {
        // 스택의 top 노드를 pop하고 현재의 깊이값을 가져온다.
        Node* currentNode = stack[--top];
        int currentDepth = levels[top];

        if (currentDepth > 1) {     // 현재 노드가 최대 깊이에 노달하지 않았다면, 새 자식 노드를 생성하고 스택에 push한다.
            for (int i = 0; i < 3; i++) {   // 각 자식 노드에 대해..
                if (rand() % 2) {   // 50%의 확률로 자식 노드를 생성한다.
                    Node* child = createNode();
                    currentNode->children[i] = child;
                    stack[top] = child;
                    levels[top++] = currentDepth - 1;
                }
            }
        }
    }

    // stack과 levels의 메모리를 해제한다.
    free(stack);
    free(levels);

    return root;    // 생성된 트리의 루트 노드를 반환
}

// 주어진 노드부터 DFS 탐색하고 탐색 경로를 저장하는 함수
void DFS(Node* node, int *path, int *index) {
    if (node == NULL)   // 루트 노드가 NULL이면 return
        return;

    path[(*index)++] = node->key;   // 현재 노드의 키를 탐색 경로에 추가한다.

    for (int i = 0; i < 3; i++) {   // 모든 자식노드에 대해 DFS를 재귀적으로 호출한다.
        DFS(node->children[i], path, index);
    }
}

// 주어진 노드부터 BFS 탐색하고 탐색 경로를 저장하는 함수
// 재귀를 사용하지 않는다.
void BFS(Node* root, int *path, int *index) {
    if (root == NULL)   // 루트 노드가 NULL이면 return
        return;

    Node** queue = (Node**) malloc(sizeof(Node*));  // 노드들을 저장하기 위해 큐를 생성
    int front = 0;      // 큐의 front를 가리키는 인덱스
    int rear = 1;       // 큐의 rear를 가리키는 인덱스
    queue[0] = root;    // 큐의 front에 루트 노드 넣는다.

    while (front != rear) {     // 큐가 비어 있지 않은 동안 반복한다.
        Node* currentNode = queue[front++];     // 큐의 front노드를 가져온다.
        path[(*index)++] = currentNode->key;    // 현재 노드의 키를 탐색 경로에 추가한다.

        // 현재 노드의 모든 자식 노드를 큐에 추가한다.
        for (int i = 0; i < 3; i++) {
            if (currentNode->children[i] != NULL) {
                queue = (Node**) realloc(queue, (++rear) * sizeof(Node*));
                queue[rear - 1] = currentNode->children[i];
            }
        }
    }

    // queue의 메모리를 해제한다.
    free(queue);
}

// 탐색 경로를 출력하는 함수
void print_path(int *path, int index) {
    for (int i = 0; i < index; i++) {   // 모든 키 값을 순서대로 출력한다.
        printf("%d", path[i]);
        if (i != index - 1)
            printf("->");
    }
    printf("\n");
}

// 주어진 노드와 그 하위 노드들의 메모리를 해제하는 함수
void freeTree(Node* root) {
    if (root == NULL)   // 노드가 NULL이면 return
        return;

    for (int i = 0; i < 3; i++) {   // 노드의 모든 자식 노드를 해제한다.
        freeTree(root->children[i]);
    }

    free(root);     // 노드를 해제한다.
}

// main 함수
int main() {
    srand(time(NULL));  // 무작위 숫자를 생성하기 위해 time을 seed로 설정

    int depth;  // 트리의 깊이 저장 변수
    printf("트리의 높이를 입력하시오: ");   // 사용자에게 트리의 깊이 입력 받는다.
    scanf("%d", &depth);

    // 랜덤한 트리 생성
    Node* root = createRandomTree(depth);

    int *DFSpath = (int*) malloc(globalKeyCounter * sizeof(int));   // DFS경로를 저장할 배열을 동적할당
    int *BFSpath = (int*) malloc(globalKeyCounter * sizeof(int));   // BFS경로를 저장할 배열을 동적할당
    int DFSindex = 0;   // DFS의 경로 배열의 현재 위치를 가리키는 인덱스
    int BFSindex = 0;   // BFS의 경로 배열의 현재 위치를 가리키는 인덱스

    clock_t start, end;     // 시간 측정을 위한 변수

    // DFS 수행하고 실행 시간을 측정한다.
    start = clock();    // 측정 시작
    DFS(root, DFSpath, &DFSindex);
    end = clock();      // 측정 종료

    // DFS 경로와 수행시간 출력
    printf("DFS 탐색경로: ");
    print_path(DFSpath, DFSindex);
    printf("DFS 수행시간: %f msec\n", ((double) end - start) / CLOCKS_PER_SEC * 1000);  // msec로 표시

    // BFS 수행하고 실행 시간을 측정한다.
    start = clock();    // 측정 시작
    BFS(root, BFSpath, &BFSindex);
    end = clock();      // 측정 종료

    // BFS 경로와 수행시간 출력
    printf("BFS 탐색경로: ");
    print_path(BFSpath, BFSindex); 
    printf("BFS 수행시간: %f msec\n", ((double) end - start) / CLOCKS_PER_SEC * 1000);  // msec로 표시

    // 트리와 경로를 저장한 배열의 메모리 해제
    freeTree(root);
    free(DFSpath);
    free(BFSpath);

    return 0;
}
