#include <stdio.h>
#define MEMO_MAX 3000000
// source: 1, target: 3 기준으로 메모
// 0: undefined
// 1: 1 -> 2
// 2: 1 -> 3
// 3: 2 -> 1
// 4: 2 -> 3
// 5: 3 -> 1
// 6: 3 -> 2
enum Path {
    undefined = 0,
    sourceToExtra = 1,
    sourceToTarget = 2,
    extraToSource = 3,
    extraToTarget = 4,
    targetToSource = 5,
    targetToExtra = 6
};
Path memo[21][MEMO_MAX] = {undefined, };

// f(n) = (f(n-1) + 1) + (f(n-2) + 1) + ... + (f(1) + 1) + 1
int hanoi(int n) {
    if (n == 1) return 1;
    int result = 0;
    for (int i = n - 1; i >= 1; i--) {
        result += hanoi(i) + 1;
    }
    result += 1;
    
    if(memo[n][0] == undefined) {
        // Make Hanoi Solution Here...
        int pos = 0;
        for (; memo[n - 1][pos] != undefined; pos++) {
            // In this case, change extra <-> target
            switch(memo[n - 1][pos]) {
                case sourceToExtra:
                    memo[n][pos] = sourceToTarget;
                    break;
                case sourceToTarget:
                    memo[n][pos] = sourceToExtra;
                    break;
                case extraToSource:
                    memo[n][pos] = targetToSource;
                    break;
                case extraToTarget:
                    memo[n][pos] = targetToExtra;
                    break;
                case targetToSource:
                    memo[n][pos] = extraToSource;
                    break;
                case targetToExtra:
                    memo[n][pos] = extraToTarget;
                    break;
                case undefined:
                    break;
            }
        }
        int tmpOffset = pos + 1;
        memo[n][pos++] = sourceToTarget;
        for (; memo[n - 1][pos - tmpOffset] != undefined; pos++) {
            // In this case, change extra <-> source
            switch(memo[n - 1][pos - tmpOffset]) {
                case sourceToExtra:
                    memo[n][pos] = extraToSource;
                    break;
                case sourceToTarget:
                    memo[n][pos] = extraToTarget;
                    break;
                case extraToSource:
                    memo[n][pos] = sourceToExtra;
                    break;
                case extraToTarget:
                    memo[n][pos] = sourceToTarget;
                    break;
                case targetToSource:
                    memo[n][pos] = targetToExtra;
                    break;
                case targetToExtra:
                    memo[n][pos] = targetToSource;
                    break;
                case undefined:
                    break;
            }
        }
    }

    return result;
}

int main() {
    // Initialize
    memo[1][0] = sourceToTarget;

    memo[2][0] = sourceToExtra;
    memo[2][1] = sourceToTarget;
    memo[2][2] = extraToTarget;

    int N;
    scanf("%d", &N);
    printf("%d\n", hanoi(N));

    for (int i = 0; memo[N][i] != undefined; i++) {
        switch(memo[N][i]) {
            case sourceToExtra:
                printf("1 2\n");
                break;
            case sourceToTarget:
                printf("1 3\n");
                break;
            case extraToSource:
                printf("2 1\n");
                break;
            case extraToTarget:
                printf("2 3\n");
                break;
            case targetToSource:
                printf("3 1\n");
                break;
            case targetToExtra:
                printf("3 2\n");
                break;
        }
    }
    return 0;
}

/*
규칙을 찾아보즈아~~~
대충 해보면 n: 홀수 일때와, n: 짝수 일때 시작점만 달라지고 패턴은 유지 되는 듯

n: 1   => 1번
1 3   -> / / 1

n: 2    => 3
1 2  -> 2 / 1 /       ---> 여기까지가 n = 1 일때 (2 <-> 3) target이 Extra로 바뀜.
1 3  ->  / 1 / 2
2 3  ->  /  / 12      ==> f(1) + 1 + 1

n: 3    => 7번
1 3  -> 23 / / 1
1 2  -> 3 / 2 / 1
3 2  -> 3 / 12 /       ----> 여기까지가 n = 2 일때 (2 <-> 3) ==> target이 extra랑 바뀜.
1 3  -> / 12 / 3       --> 그 다음 추가된 원반을 가져다가 놓고... 
2 1  -> 1 / 2 / 3      --> 다시 f(2) 스타트. 중앙의 12를 우측으로 가져다 놓는다. source <-> extra
2 3  -> 1 / / 23              -> 원래 1 2 (sourceToExtra) 였음. source가 1->2로 바뀜 (1<->2)
1 3  -> / / 123        ==> f(2)[2 <-> 3] + 1 + f(1)[] + 1 + 1

==> n번째의 수행횟수가 f(n)번이라면, 
   (n+1)번째에는, f(n) + 1(새로 추가된 원판 우측으로) + f(n-1) + 1(n-1 단계의 원판을 우측으로) + f(n-2) + 1(n-2 ... 우측) +...
   즉, n = 3일때는, f(2) + 1 + f(1) + 1 + 1(마지막 1개짜리 우측으로) = 3 + 1 + 1 + 1 + 1 = 7
n:4     => 13번
1 2  -> 234 / 1 / 
1 3  -> 34 / 1 / 2 
2 3  -> 34 /  / 12
1 2  -> 4 / 3 / 12
3 1  -> 14 / 3 / 2
3 2  -> 14 / 23 / 
1 2  -> 4 / 123 /    -----> 여기까지가 n: 3 일때를 2 <-> 3 한 부분이 들어가는 것
1 3  -> / 123 / 4     ----> + 1
2 3  ->  / 23 / 14
2 1  -> 2 / 3 / 14
3 1  -> 12 / 3 / 4     ---> n: 2 일때
2 3  -> 12 / / 34      ----> + 1
1 2  -> 2 / 1 / 34     ---> n: 1 일때
1 3  -> / 1 / 234       ---> + 2
2 3  -> / / 1234      ---> 최종 + 1
==> n = 4 일때 분석:
    [f(3) + 1] + [f(2) + 1] + [f(1) + 1] + 1 = (7 + 1) + (3 + 1) + (1 + 1) + 1 = 8 + 4 + 2 + 1 = 15
    재귀적임을 알 수 있다.

===> 라인 분석
source, target, extra 의 약자를 따서 s, t ,e 라고 하면 항상 동일 함.

세 종류의 라인

*/

/*
문제
세 개의 장대가 있고 첫 번째 장대에는 반경이 서로 다른 n개의 원판이 쌓여 있다. 각 원판은 반경이 큰 순서대로 쌓여있다. 이제 수도승들이 다음 규칙에 따라 첫 번째 장대에서 세 번째 장대로 옮기려 한다.

한 번에 한 개의 원판만을 다른 탑으로 옮길 수 있다.
쌓아 놓은 원판은 항상 위의 것이 아래의 것보다 작아야 한다.
이 작업을 수행하는데 필요한 이동 순서를 출력하는 프로그램을 작성하라. 단, 이동 횟수는 최소가 되어야 한다.

아래 그림은 원판이 5개인 경우의 예시이다.



입력
첫째 줄에 첫 번째 장대에 쌓인 원판의 개수 N (1 ≤ N ≤ 20)이 주어진다.

 

출력
첫째 줄에 옮긴 횟수 K를 출력한다.

두 번째 줄부터 수행 과정을 출력한다. 두 번째 줄부터 K개의 줄에 걸쳐 두 정수 A B를 빈칸을 사이에 두고 출력하는데, 이는 A번째 탑의 가장 위에 있는 원판을 B번째 탑의 가장 위로 옮긴다는 뜻이다.
*/
