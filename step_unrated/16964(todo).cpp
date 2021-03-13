#include <stdio.h>
#define MAX_SIZE 100002

typedef struct _list {
    int headIdx = -1;
} List;

typedef struct __node {
    int y;
    int nextIdx = -1;
} Node;

int N;
List e[MAX_SIZE];
Node n[MAX_SIZE];
bool visited[MAX_SIZE] = {false, };
int visitCount = 0;
int userInput[MAX_SIZE] = {0, };
int Stack[MAX_SIZE] = {0, };
int StackSize = 0;
void push(int a) {
    Stack[StackSize++] = a;
}
int pop() {
    if (StackSize > 0) {
        return Stack[--StackSize];
    } else return -1;
}

int listSize = 0;
void myAlloc(int x, int y) {
    if (e[x].headIdx == -1) { // 리스트에 처음 들어가는 경우
        e[x].headIdx = listSize;
        n[listSize].y = y;
    } else {
        int idx = e[x].headIdx;
        while (n[idx].nextIdx != -1) { // 마지막 아이템까지 탐색
            idx = n[idx].nextIdx;
        }
        n[idx].y = y;
    }
    listSize++;
}
bool searchList(int x, int y) {
    if (e[x].headIdx == -1) { // 해당 정점에 연결이 하나도 없는 경우
        return false;
    } else {
        int idx = e[x].headIdx;
        while (n[idx].nextIdx != -1) {
            if (n[idx].y == y) { // y를 찾았으면 리턴
                return true;
            }
            idx = n[idx].nextIdx;
        }
    }
    return false;
}

bool dfs(int x) {
    if (visitCount == N) {
        return true;
    }
    for (int y = 1; y <= N; y++) {
        if (!visited[y] && searchList(x, y)) {
            visitCount++;
            visited[y] = true;
            push(y);
            bool r = dfs(y);
            if (r) return true;
            pop();
            visited[y] = false;
            visitCount--;
        }
    }
    return false;
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N - 1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        myAlloc(a, b);
        myAlloc(b, a);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &userInput[i]);
    }
    visitCount = 1;
    visited[1] = true;
    push(1);
    dfs(1);

    for (int i = 0; i < N; i++) {
        if (Stack[i] != userInput[i]) {
            printf("0\n");
            return 0;
        }
    }
    printf("1\n");
    return 0;
}

/*
DFS 스페셜 저지 분류
시간 제한	메모리 제한	제출	정답	맞은 사람	정답 비율
2 초	512 MB	1282	457	353	42.479%
문제
BOJ에서 정답이 여러가지인 경우에는 스페셜 저지를 사용한다. 스페셜 저지는 유저가 출력한 답을 검증하는 코드를 통해서 정답 유무를 결정하는 방식이다. 오늘은 스페셜 저지 코드를 하나 만들어보려고 한다.

정점의 개수가 N이고, 정점에 1부터 N까지 번호가 매겨져있는 양방향 그래프가 있을 때, DFS 알고리즘은 다음과 같은 형태로 이루어져 있다.

1
2
3
4
5
6
7
8
9
10
11
12
void dfs(int x) {
    if (check[x] == true) {
        return;
    }
    check[x] = true;
    // x를 방문
    for (int y : x와 인접한 정점) {
        if (check[y] == false) {
            dfs(y);
        }
    }
}
이 문제에서 시작 정점은 1이기 때문에 가장 처음에 호출하는 함수는 dfs(1)이다. DFS 방문 순서는 dfs함수에서 // x를 방문 이라고 적힌 곳에 도착한 정점 번호를 순서대로 나열한 것이다.

트리가 주어졌을 때, 올바른 DFS 방문 순서인지 구해보자.

입력
첫째 줄에 정점의 수 N(2 ≤ N ≤ 100,000)이 주어진다. 둘째 줄부터 N-1개의 줄에는 트리의 간선 정보가 주어진다. 마지막 줄에는 DFS 방문 순서가 주어진다. DFS 방문 순서는 항상 N개의 정수로 이루어져 있으며, 1부터 N까지 자연수가 한 번씩 등장한다.

출력
입력으로 주어진 DFS 방문 순서가 올바른 순서면 1, 아니면 0을 출력한다.

예제 입력 1 
4
1 2
1 3
2 4
1 2 3 4
예제 출력 1 
0
예제 입력 2 
4
1 2
1 3
2 4
1 2 4 3
예제 출력 2 
1
예제 입력 3 
4
1 2
1 3
2 4
1 3 2 4
예제 출력 3 
1
*/
