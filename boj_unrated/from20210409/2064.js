function solution(scanner) {
    const N = scanner.readInt();
    const db = [];
    for (let i = 0; i < N; i++) {
        const row = scanner.readLine().split('.').map(Number);
        db.push(row);
    }
    db.sort((a, b) => {
        if (a[0] === b[0]) {
            if (a[1] === b[1]) {
                if (a[2] === b[2]) {
                    if (a[3] === b[3]) {
                        return 0;
                    } else {
                        return a[3] - b[3];
                    }
                } else {
                    return a[2] - b[2];
                }
            } else {
                return a[1] - b[1];
            }
        } else {
            return a[0] - b[0];
        }
    });
    console.log(db);
    // Mask 찾기.. 비트연산으로. 최대 & 최소 XOR..
    const r = [];
    const min = db[0];
    const max = db[db.length - 1];
    for (let i = 0; i < 4; i++) {
        if (i != 0) {
            if (r[i - 1] != 255) {
                r.push(0);
            } else {
                r.push(255 - findpower2(min[i] ^ max[i]));
            }
        } else {
            r.push(255 - findpower2(min[i] ^ max[i]));
        }
    }
    console.log(r);
    function findpower2(num) {
        let i = 1;
        while (i <= num) {
            i *= 2;
        }
        return i - 1;
    }
    const r2 = [];
    for (let i = 0; i < 4; i++) {
        r2.push(r[i] & min[i]);
    }
    console.log(r2);
    return r2.join('.') + '\n' + r.join('.');
}


/////////////////////////////////////////////////////////////////////////////////
// Readiz BOJ JS Util Start
/////////////////////////////////////////////////////////////////////////////////
const scanner = {
    readInt: () => {
        return parseInt(__lineDB[__lineIdx++], 10);
    },
    readLine: () => {
        return __lineDB[__lineIdx++];
    }
};
let __lineDB = [];
let __lineIdx = 0;
const isDebug = process.argv[2] === 'readizDebug';
if (!isDebug) {
    global.console = {
        log: () => {},
        warn: () => {},
        info: () => {},
        debug: () => {},
        error: () => {}
    };
    const rl = require('readline').createInterface({
        input: process.stdin,
        output: process.stdout
    });
    rl.on('line', (line) => {
        __lineDB.push(line);
    });
    rl.on('close', () => {
        process.stdout.write(solution(scanner) + '\n');
    });
} else {
    __lineDB = require('fs').readFileSync(process.argv[1].replace('.js', '_input.txt')).toString().split('\n');
    while (__lineIdx < __lineDB.length) {
        process.stdout.write('--------------------------------------------\n');
        process.stdout.write('New Start + Log\n');
        process.stdout.write('--------------------------------------------\n');
        const start = __lineIdx;
        const answer = solution(scanner);
        const end = __lineIdx;
        process.stdout.write('----------------------\n');
        process.stdout.write('Input\n')
        process.stdout.write('----------------------\n');
        process.stdout.write(__lineDB.slice(start, end).join('\n') + '\n');
        process.stdout.write('----------------------\n');
        process.stdout.write('Answer\n')
        process.stdout.write('----------------------\n');
        process.stdout.write(answer + '\n');
    }
}


/*
IP 주소 출처다국어분류
시간 제한	메모리 제한	제출	정답	맞은 사람	정답 비율
2 초	128 MB	535	180	121	33.060%
문제
네트워크에 연결되어 있는 컴퓨터들은 각각 하나의 IP 주소를 갖게 된다. 그리고 이러한 IP 주소를 갖는 컴퓨터들이 여러 개 모여서 하나의 IP 네트워크를 구성하게 된다. IP 네트워크는 ‘네트워크 주소’와 ‘네트워크 마스크’라는 두 개의 정보로 표현된다.

IP 주소는 네 개의 바이트로 구성되어 있으며, 각각을 10진수로 나타내고(앞에 0을 붙이지 않은 형태로) 사이에 점을 찍어 주소를 표현한다. 바이트이기 때문에 각각의 수는 0부터 255까지의 값을 갖게 된다. 네트워크 주소와 네트워크 마스크 역시 같은 형식으로 나타낸다.

IP 네트워크에 대해 올바르게 이해하기 위해서는 위와 같은 주소를 2진수로 이해하면 된다. 즉, 각각의 바이트를 8자리의 이진수로 나타내고, 이를 네 개 붙여놓은(앞에서부터) 32자리의 이진수를 생각해 보자. IP 네트워크에는 기본적으로 2^m 개의 컴퓨터(혹은 IP 주소)가 할당될 수 있다. 이 경우의 네트워크 주소는 앞의 32-m 자리가 임의의 수(0 또는 1)로 구성되어 있고, 뒤의 m자리는 0으로 채워지게 된다. 네트워크 마스크는 앞의 32-m 자리가 1로 채워져 있고, 뒤의 m자리는 0으로 채워지게 된다. 이와 같은 IP 네트워크에는 앞의 32-m 자리가 네트워크 주소와 일치하는 모든 IP들이 포함되게 된다.

예를 들어 네트워크 주소가 194.85.160.176이고, 네트워크 마스크가 255.255.255.248인 경우를 생각해 보자. 이 경우, 이 네트워크에는 194.85.160.176부터 194.85.160.183까지의 8개의 IP 주소가 포함된다.

어떤 네트워크에 속해있는 IP 주소들이 주어졌을 때, 네트워크 주소와 네트워크 마스크를 구해내는 프로그램을 작성하시오. 답이 여러 개인 경우에는 가장 크기가 작은(포함되는 IP 주소가 가장 적은, 즉 m이 최소인) 네트워크를 구하도록 한다.

입력
첫째 줄에 정수 n(1≤n≤1,000)이 주어진다. 다음 n개의 줄에는 각 컴퓨터의 IP 주소가 주어진다.

출력
첫째 줄에 네트워크 주소를, 둘째 줄에 네트워크 마스크를 출력한다.

예제 입력 1 
3
194.85.160.177
194.85.160.183
194.85.160.178
예제 출력 1 
194.85.160.176
255.255.255.248
*/
