const readline = require('readline');

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout
});

let isFirst = true;
let x1, y1, x2, y2;
let isEnteringCircles = false;
let numberOfCircles;
let circles = [];
rl.on('line', (line) => {
    if (isFirst) { isFirst = false; return; } // First Input => No use!
    const inputNumbers = line.split(' ').map(item => parseInt(item));
    if (inputNumbers.length == 4) {
        [x1, y1, x2, y2] = inputNumbers;
    }
    if (inputNumbers.length == 1) {
        isEnteringCircles = true;
        circles = [];
        numberOfCircles = inputNumbers[0];
    }
    if (isEnteringCircles) {
        if (inputNumbers.length == 3) {
            circles.push(inputNumbers);
            numberOfCircles --;
        }
        if (numberOfCircles == 0) {
            isEnteringCircles = false;
            
            // Start Calculating...
            // 1. For [x1, y1]
            const passing_1 = [];
            for (circle of circles) {
                passing_1.push(isInner([x1, y1], circle));
            }

            // 2. For [x2, y2]
            const passing_2 = [];
            for (circle of circles) {
                passing_2.push(isInner([x2, y2], circle));
            }

            // 3. Calculate only for passing_1 == true || passing_2 == true, but not both.
            let xor = 0;
            for (let i = 0; i < circles.length; i++) {
                if (passing_1[i] && passing_2[i]) continue;
                if (passing_1[i] || passing_2[i]) xor ++;
            }
            console.log(xor);
        }
    }
});

function isInner([x, y], [cx, cy, r]) {
    const dx = cx - x;
    const dy = cy - y;
    const d_square = dx * dx + dy * dy;
    
    if (d_square < r * r) {
        return true;
    }
    return false;
}

/*
문제 
어린 왕자는 소혹성 B-664에서 자신이 사랑하는 한 송이 장미를 위해 살아간다. 
어느 날 장미가 위험에 빠지게 된 것을 알게 된 어린 왕자는, 
장미를 구하기 위해 은하수를 따라 긴 여행을 하기 시작했다. 
하지만 어린 왕자의 우주선은 그렇게 좋지 않아서 행성계 간의 이동을 최대한 피해서 여행해야 한다. 
아래의 그림은 어린 왕자가 펼쳐본 은하수 지도의 일부이다.

빨간 실선은 어린 왕자가 출발점에서 도착점까지 도달하는데 있어서 필요한 행성계 진입/이탈 횟수를 최소화하는 경로이며, 
원은 행성계의 경계를 의미한다. 
이러한 경로는 여러 개 존재할 수 있지만 적어도 3번의 행성계 진입/이탈이 필요하다는 것을 알 수 있다.
위와 같은 은하수 지도, 출발점, 도착점이 주어졌을 때 어린 왕자에게 필요한 최소의 행성계 진입/이탈 횟수를 구하는 프로그램을 작성해 보자. 
(행성계의 경계가 맞닿거나 서로 교차하는 경우는 없다고 가정한다. 
    또한, 출발점이나 도착점이 행성계 경계에 걸쳐진 경우 역시 입력으로 주어지지 않는다.)

입력 
입력의 첫 줄에는 테스트 케이스의 개수 T가 주어진다. 그 다음 줄부터 각각의 테스트케이스에 대해 첫째 줄에 출발점 (x1, y1)과 도착점 (x2, y2)이 주어진다. 두 번째 줄에는 행성계의 개수 n이 주어지며, 세 번째 줄부터 n줄에 걸쳐 행성계의 중점과 반지름 (cx, cy, r)이 주어진다. 입력제한은 다음과 같다. (-1000 ≤ x1, y1, x2, y2, cx, cy ≤ 1000, 1 ≤ r ≤ 1000, 1 ≤ n ≤ 50)
좌표와 반지름은 모두 정수이다.

출력 
각 테스트 케이스에 대해 어린 왕자가 거쳐야 할 최소의 행성계 진입/이탈 횟수를 출력한다.

예제 입력 1 
2
-5 1 12 1
7
1 1 8
-3 -1 1
2 2 2
5 5 1
-4 5 1
12 1 1
12 1 2
-5 1 5 1
1
0 0 2

예제 출력 1
3
0
*/