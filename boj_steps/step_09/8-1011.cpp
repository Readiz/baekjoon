#include <stdio.h>

// x_n+1 = 1/2(x_n + a/x_n) 임을 활용 (a: 입력값)
// 반복할 수록 정밀도 높아짐.
unsigned int approx_sqrt(unsigned int a)
{
    unsigned int x = 2;
    unsigned int x_new;
    for(int i = 0; i < 20; i++) {
        x_new = ( x + ( a / x ) ) / 2;
        if (x_new == x) break;
        x = x_new;
    }
 
    return x;
}

// 구해야할 수열:
// 1 2 4 6 9 12 16 20 25 30 36 42 49 56 64 72 81 90 100 110 121 132 144 156 169 182 196 210 225 240 256 272 289 306 324 342 361 380 400 420 441 462 484 506 529 552 576 600 625 650 676 702 729 756 784 812 841 870 900 930 961 992 1024 1056 1089 1122 1156 1190 1225 1260 1296 1332 1369 1406 1444 1482 1521 1560 1600 1640 1681 1722 1764 1806 1849 1892 1936 1980 2025 2070 2116 2162 2209 2256 2304 2352 2401 2450 2500
// 홀수 수열
// 1 4 9 16 25 36 49 64 81 ...
// => i^2임
// 짝수 수열
// 2 6 12 20 30 42 56 72 90 ...
// => i^2 + i 임
unsigned int get_max_dist(unsigned int i) {
    if (i % 2 == 1) {
        unsigned int tmp = ((i + 1) / 2);
        return tmp * tmp;
    } else {
        unsigned int tmp = (i / 2);
        return tmp * tmp + tmp;
    }
}

int main() {
    int T;
    scanf("%d", &T);
    for (int tc = 0; tc < T; tc++) {
        unsigned int x, y, diff, approx_min;
        scanf("%u %u", &x, &y);
        diff = y - x;

        approx_min = approx_sqrt(diff) * 2;
        int overstep = 0;
        while (diff <= get_max_dist(approx_min)) {
            // printf("diff > approx_dist! recalculate...\n");
            // printf("diff: %u, approx_dist: %u, approx_min: %u\n", diff, get_max_dist(approx_min), approx_min);
            approx_min--;
            overstep++;
        }
        // printf("Done! Overstep: %d\n", overstep);
        // printf("[Final] diff: %u, approx_dist: %u, approx_min: %u\n", diff, get_max_dist(approx_min + 1), approx_min + 1);
        printf("%u\n", approx_min + 1);
    }
    return 0;
}

/*
가장 적게 공간이동 하려면 당연히 가속을 풀로 땡기다가, 서서히 감속해야 할 것.
그리고 직전에는 k = 1이 되어야 하고..
그러면 요런 형태임
1 2 3 4 5 6 5 4 3 2 1 ... => 이 최대값보다 적은 횟수로.. 갈 수 있는 요런 느낌
그럼 요 형태의 배열을 가지고 있으면 될 듯...? (최대거리가 되는거니)

공간이동 장치 발동 수에 따른 max 거리
1: 1                => 1   (  1) <- (i + 1) / 2 의 값
2: 1 1              => 2  ( + 1)
3: 1 2 1            => 4  ( + 2)
4: 1 2 2 1          => 6  ( + 2)
5: 1 2 3 2 1        => 9  ( + 3)
6: 1 2 3 3 2 1      => 12 ( + 3)
7: 1 2 3 4 3 2 1    => 16 ( + 4)

이걸 규칙대로 찍어보면:
1 2 4 6 9 12 16 20 25 30 36 42 49 56 64 72 81 90 100 110 121 132 144 156 169 182 196 210 225 240 256 272 289 306 324 342 361 380 400 420 441 462 484 506 529 552 576 600 625 650 676 702 729 756 784 812 841 870 900 930 961 992 1024 1056 1089 1122 1156 1190 1225 1260 1296 1332 1369 1406 1444 1482 1521 1560 1600 1640 1681 1722 1764 1806 1849 1892 1936 1980 2025 2070 2116 2162 2209 2256 2304 2352 2401 2450 2500

홀수 수열
1 4 9 16 25 36 49 64 81 ...
=> i^2임
짝수 수열
2 6 12 20 30 42 56 72 90 ...
=> i^2 + i 임

=> 만약 distance가 주어진다면, 우선 그 distance를 갖는 것보다 작은 i 값을 먼저 찾고
   그보다 더 작아질 수 있는 i 값이 있는지를 한번 더 보면 됨.
ex) ditance가 10이다 => (10)^1/2 = 3.xxx 이므로 3부터 시작. 3 * 2 부터 시작해서 비교하면 됨
*/
