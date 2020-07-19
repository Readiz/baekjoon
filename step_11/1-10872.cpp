#include <stdio.h>

int main() {
    int N;
    int result = 1;
    for (scanf("%d", &N); N; N--) {
        result *= N;
    }
    printf("%d\n", result);
    return 0;
}

/*
문제
0보다 크거나 같은 정수 N이 주어진다. 이때, N!을 출력하는 프로그램을 작성하시오.

입력
첫째 줄에 정수 N(0 ≤ N ≤ 12)가 주어진다.

출력
첫째 줄에 N!을 출력한다.
*/
