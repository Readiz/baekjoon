#include <stdio.h>

int prime[200001];
int nearlyPrime[200001];
void eratos(){
	for (int i = 0; i < 200001; i++) {
		prime[i] = 1; 
	}
	prime[0] = prime[1] = 0; // not primes  
	for (int i = 2; i < 200001; i++) {
		if (prime[i]) {
			for (int j = i; j < 200001; j += i) {
                if (j < 200001)
    			    prime[j] = 0; 
			}
		}
	}
}
void getNearlyPrime() {
	for (int i = 0; i < 200001; i++){
		nearlyPrime[i] = 1; 
	}
    for (int i = 1; i < 200001; i++) {
        for (int j = i + 1; j < 200001; j++) {
            if (prime[i] && prime[j] && i * j < 200001)
                nearlyPrime[i * j] = 0;
        }
    }
}


int main() {
    eratos();
    getNearlyPrime();
    for (int i = 1; i < 1000; i++) {
        if (nearlyPrime[i])
            printf("%d\n", i); 
    }


    // Nearly Prime => 소수 두개의 곱으로 나타내질 수 있는 수
    // ex) 2 * 5 = 10
    // Can you represent it as the sum of 4 different positive integers where at least 3 of them should be nearly prime.
    // => 3개가 Nearly Prime인 4개의 서로 다른 양의 장수의 합으로 Nearly Prime을 만들 수 있는가?
    // 할 수 있나??
    int T;
    scanf("%d", &T);

    for (int tc = 0; tc < T; tc++) {
        int N;
        scanf("%d", N); // (N <= 2 * 10 ^ 5 = 200000)

    }

    return 0;
}
/*
A. Captain Flint and Crew Recruitment
time limit per test1 second
memory limit per test256 megabytes
inputstandard input
outputstandard output
Despite his bad reputation, Captain Flint is a friendly person (at least, friendly to animals). Now Captain Flint is searching worthy sailors to join his new crew (solely for peaceful purposes). A sailor is considered as worthy if he can solve Flint's task.

Recently, out of blue Captain Flint has been interested in math and even defined a new class of integers. Let's define a positive integer x as nearly prime if it can be represented as p⋅q, where 1<p<q and p and q are prime numbers. For example, integers 6 and 10 are nearly primes (since 2⋅3=6 and 2⋅5=10), but integers 1, 3, 4, 16, 17 or 44 are not.

Captain Flint guessed an integer n and asked you: can you represent it as the sum of 4 different positive integers where at least 3 of them should be nearly prime.

Uncle Bogdan easily solved the task and joined the crew. Can you do the same?

Input
The first line contains a single integer t (1≤t≤1000) — the number of test cases.

Next t lines contain test cases — one per line. The first and only line of each test case contains the single integer n (1≤n≤2⋅105) — the number Flint guessed.

Output
For each test case print:

YES and 4 different positive integers such that at least 3 of them are nearly prime and their sum is equal to n (if there are multiple answers print any of them);
NO if there is no way to represent n as the sum of 4 different positive integers where at least 3 of them are nearly prime.
You can print each character of YES or NO in any case.
Example
inputCopy
7
7
23
31
36
44
100
258
outputCopy
NO
NO
YES
14 10 6 1
YES
5 6 10 15
YES
6 7 10 21
YES
2 10 33 55
YES
10 21 221 6
Note
In the first and second test cases, it can be proven that there are no four different positive integers such that at least three of them are nearly prime.

In the third test case, n=31=2⋅7+2⋅5+2⋅3+1: integers 14, 10, 6 are nearly prime.

In the fourth test case, n=36=5+2⋅3+2⋅5+3⋅5: integers 6, 10, 15 are nearly prime.

In the fifth test case, n=44=2⋅3+7+2⋅5+3⋅7: integers 6, 10, 21 are nearly prime.

In the sixth test case, n=100=2+2⋅5+3⋅11+5⋅11: integers 10, 33, 55 are nearly prime.

In the seventh test case, n=258=2⋅5+3⋅7+13⋅17+2⋅3: integers 10, 21, 221, 6 are nearly prime.
*/
