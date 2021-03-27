#include <stdio.h>
#include <algorithm>
#include <vector>
using namespace std;

class Point {
public:
    int x;
    int y;
    Point(int x, int y) {
        this->x = x;
        this->y = y;
    }
    bool operator<(Point p) {
        if (this->y != p.y) {
            return this->y < p.y;
        } else {
            return this->x < p.x;
        }
    }
};

int main() {
    int N;
    scanf("%d", &N);
    vector<Point> vPoints;

    for (int i = 0; i < N; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        vPoints.push_back(Point(x, y));
    }
    
    sort(vPoints.begin(), vPoints.end());

    for (int i = 0; i < N; i++) {
        printf("%d %d\n", vPoints[i].x, vPoints[i].y);
    }
    return 0;
}

/*
문제
2차원 평면 위의 점 N개가 주어진다. 좌표를 y좌표가 증가하는 순으로, y좌표가 같으면 x좌표가 증가하는 순서로 정렬한 다음 출력하는 프로그램을 작성하시오.

입력
첫째 줄에 점의 개수 N (1 ≤ N ≤ 100,000)이 주어진다. 둘째 줄부터 N개의 줄에는 i번점의 위치 xi와 yi가 주어진다. (-100,000 ≤ xi, yi ≤ 100,000) 좌표는 항상 정수이고, 위치가 같은 두 점은 없다.

출력
첫째 줄부터 N개의 줄에 점을 정렬한 결과를 출력한다.
*/