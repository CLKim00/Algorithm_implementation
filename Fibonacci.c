#include <stdio.h>  // 표준 입출력 함수를 위한 헤더 파일
#include <time.h>  // 시간 관련 함수를 위한 헤더 파일
#include <stdint.h>  // 표준 정수 타입을 위한 헤더 파일

// 재귀함수를 이용한 피보나치 수열
uint64_t fibonacci_recursive(int n){
    if(n <= 0) // 만약 n이 0 이하인 경우 0을 반환
        return 0;
    else if(n == 1) // 만약 n이 1인 경우 1을 반환
        return 1;
    else  // n이 2 이상인 경우, n-1번째 피보나치 수와 n-2번째 피보나치 수를 더하여 반환
        return fibonacci_recursive(n-1) + fibonacci_recursive(n-2);
}

// 동적 프로그래밍을 이용한 피보나치 수열
uint64_t fibonacci_dynamic(int n){
    uint64_t fib[n+2];  // n+2 크기의 unsigned long long 타입 배열 선언
    fib[0] = 0;  // 피보나치 수열의 첫 번째 항을 0으로 초기화
    fib[1] = 1;  // 피보나치 수열의 두 번째 항을 1로 초기화
    for(int i=2; i<=n; i++){  // 2부터 n까지 반복
        fib[i] = fib[i-1] + fib[i-2];  // i번째 피보나치 수를 계산하여 fib[i]에 저장
    }
    return fib[n];  // n번째 피보나치 수를 반환
}

int main(){
    int n;
    printf("몇 번째 피보나치 수를 확인하시겠습니까? : ");  // 사용자에게 몇 번째 피보나치 수를 계산할지 물어봄
    scanf("%d", &n);  // 사용자의 입력을 받아 n에 저장

    clock_t start, end;  // 시작 시간과 끝나는 시간을 저장할 변수 선언
    double time;

    start = clock();  // 재귀 함수를 시작하기 전 시간을 측정
    uint64_t fib_recursive = fibonacci_recursive(n);  // 재귀 함수를 이용해 n번째 피보나치 수를 계산
    end = clock();  // 재귀 함수가 끝난 후의 시간을 측정
    time = ((double) (end - start)) / CLOCKS_PER_SEC * 1000; // 시간 차이를 밀리초로 변환
    printf("Recursive: %llu / %.3f msec\n", fib_recursive, time);  // 계산 결과와 수행 시간을 출력

    start = clock();  // 동적 프로그래밍을 시작하기 전 시간을 측정
    uint64_t fib_dynamic = fibonacci_dynamic(n);  // 동적 프로그래밍을 이용해 n번째 피보나치 수를 계산
    end = clock();  // 동적 프로그래밍이 끝난 후의 시간을 측정
    time = ((double) (end - start)) / CLOCKS_PER_SEC * 1000; // 시간 차이를 밀리초로 변환
    printf("Dynamic: %llu / %.3f msec\n", fib_dynamic, time);  // 계산 결과와 수행 시간을 출력

    return 0;  // 프로그램 종료
}
