#include <stdio.h>      // 파일 입출력 기능을 포함한 헤더파일
#include <stdlib.h>     // rand 함수를 포함한 헤더파일
#include <time.h>       // time 함수를 포함한 헤더파일

void create_random(char *file);                                         // input.txt에 0~999까지의 random한 숫자를 1000개 생성하는 함수
void num_to_array(char *file, int *arr);                                // input.txt를 읽어 1차원 배열에 저장하는 함수
void selection_sort(int *arr, int size, char *file);                    // input.txt를 읽어 selectionSort 알고리즘을 통해 999개의 난수를 정렬하고 output.txt에 저장하는 함수
void comparing(char *input_txt, char *output_txt, char *result_txt);    // 난수와 정렬된 결과를 비교하여 같은 위치에 있는 값의 개수와 인덱스값을 result.txt에 저장하는 함수
int countMatch(int A[], int B[], int size);                             // 난수와 정렬된 결과를 비교하여 같은 위치에 있는 값의 개수를 세는 함수

// main 함수
int main(void)
{
    srand(time(NULL));                                      // 매번 다른 알고리즘으로 난수를 생성하도록 하기 위해
                                                            // srand 함수를 이용해 seed에 time(NULL)을 적용하여 현재 시간을 넣어준다.
    create_random("input.txt");                             // file 포인터의 주소값인 "input.txt"을 매개변수로 줘서 create_random 함수 실행
    int arr[1000];                                          // 생성된 1000개의 난수를 넣을 배열 생성
    num_to_array("input.txt", arr);                         // file 포인터의 주소값인 "input.txt"와 배열을 매개변수로 하는 num_to_array 함수 실행
    selection_sort(arr, 1000, "output.txt");                // 난수로 이루어진 배열, 배열의 크기 1000, file 포인터의 주소값인 "output.txt"을 매개변수로 하는 selection_sort 함수 실행
    comparing("input.txt", "output.txt", "match.txt");      // 각 포인터의 주소값인 "input.txt", "output.txt", "match.txt" 파일을 매개변수로 하는 comparing 함수 실행

    return 0;
}

// Fisher-Yates shuffle Algorithm을 이용해 난수 생성
// 유한 수열의 무작위 순열을 생성하기 위한 알고리즘이다. 먼저 모든 항목이 들어 있는 통에서 항목이 남아 있지 않을 때까지 항목을 무작위로 꺼내어 다음 항목을 선택한다. 이 알고리즘은 편향되지 않은 순열을 생성한다.
void create_random(char *file)              // 파일 포인터를 인자로 받음
{
    FILE *randomP = fopen(file, "w");       // file을 쓰기 모드로 연다. 이때 반환된 파일 포인터를 randomP에 저장한다.
    int arr[1000];                          // 크기가 1000인 배열을 선언한다.
    for (int i = 0; i < 1000; i++)          // i가 0부터 999까지 1씩 증가하며 실행문을 1000번 실행한다.
    {
        arr[i] = i;                         // 배열에 0부터 999까지의 수를 오름차순으로 넣는다.
    }
    
    for (int i = 1000 - 1; i >= 0; i--)     // i는 999부터 0까지 1씩 감소하며 실행문을 1000번 실행한다.
    {
        int j = rand() % (i + 1);           // 난수 생성 범위를 제한하기 위해 % 연산자를 활용해 0부터 i(999)까지의 난수를 생성한다. 생성된 난수는 j 변수에 넣는다.
        
        // swap
        int temp = arr[i];                  // 변수 temp에 배열 arr의 i번째 값을 넣는다.
        arr[i] = arr[j];                    // 배열요소 arr[i]에 배열요소 arr[j]를 넣는다.
        arr[j] = temp;                      // arr[j]에 다시 temp의 값들을 넣는다. 배열요소 arr[i]와 배열요소 arr[j]를 교환했다.
                                            // 이 반복문이 종료되면 오름차순으로 정렬되어 있던 배열 arr가 무작위순으로 바뀐다.
    }

    for (int i = 0; i < 1000; i++)          
    {
        fprintf(randomP, "%d\t", arr[i]);   // 난수로 이루어진 배열 arr[i]의 값들을 tab문자로 구분하여 파일에 print한다.
    }
    fclose(randomP);                        // randomP 파일 포인터를 fclose 함수의 매개변수로 넣어 열었던 파일을 닫는다.
}

// 파일을 읽어 1차원 배열에 저장
void num_to_array(char *file, int *arr)     // 파일 포인터와 배열 포인터를 인자로 받음
{
    FILE *arrayP = fopen(file, "r");        // file을 읽기 모드로 연다. 이때 반환된 파일 포인터를 arrayP에 저장한다.

    for(int i = 0; i < 1000; i++)
    {
        fscanf(arrayP, "%d\t", &arr[i]);    // 탭 문자로 구분된 파일을 읽어서 배열 arr[i]에 담는다.
    }
    
    fclose(arrayP);                         // arrayP 파일 포인터를 fclose 함수의 매개변수로 넣어 열었던 파일을 닫는다.
}

// 붙어있는 두 값을 비교해 swap을 반복하는 selectionSort Algorithm
void selection_sort(int *arr, int size, char *file)     // 배열 포인터, 배열의 크기, 파일 포인터를 인자로 받음
{
    int position, temp;                                 // int형 변수 position, temp 선언
    for(int i = 0; i < (size - 1); i++)                 // i가 0부터 999까지 1씩 증가하며 실행문을 1000번 실행한다.
    {
        position = i;                                   // position 변수를 i 값으로 초기화
        for(int j = i + 1; j < size; j++)               // j가 i + 1부터 999까지 1씩 증가하며 실행문을 1000번 실행한다.
        {
            if (arr[position] > arr[j])                 // position의 값과 같은 인덱스 값을 가진 배열 arr의 요소가 다음 요소보다 크면,
            {
                position = j;                           // position의 값을 j의 값으로 초기화
            }
        }
        // swap
        temp = arr[position];                           // position번째 배열 요소를 temp에 저장
        arr[position] = arr[i];                         // i번째 배열 요소를 position번째 배열 요소에 저장
        arr[i] = temp;                                  // 다시 temp의 값을 i번째 요소에 저장
    }

    FILE *sort_result = fopen(file, "w");               // file을 쓰기 모드로 연다. 이때 반환된 파일 포인터를 sort_result에 저장한다.

    for (int i = 0; i < 1000; i++)                      
    {
        fprintf(sort_result, "%d\t", arr[i]);           // 정렬된 배열 arr[i]의 값들을 tab문자로 구분하여 파일에 print한다.
    }

    fclose(sort_result);                                // sort_result 파일 포인터를 fclose 함수의 매개변수로 넣어 열었던 파일을 닫는다.
}

// 두 파일을 읽어서 비교 후 같은 위치에 같은 값이 있으면 새로운 파일에 저장하는 함수
void comparing(char *input_txt, char *output_txt, char *result_txt)     // 3개의 파일 포인터를 인자로 받는다.
{
    FILE *inputP = fopen(input_txt, "r");                               // file을 읽기 모드로 연다. 이때 반환된 파일 포인터를 inputP에 저장한다.
    FILE *outputP = fopen(output_txt, "r");                             // file을 읽기 모드로 연다. 이때 반환된 파일 포인터를 outputP에 저장한다.
    FILE *resultP = fopen(result_txt, "w");                             // file을 쓰기 모드로 연다. 이때 반환된 파일 포인터를 resultP에 저장한다.

    int arr1[1000], arr2[1000];                                         // 크기가 1000인 배열 arr1, arr2를 선언한다.

    for(int i = 0; i < 1000; i++)   
    {
        fscanf(inputP, "%d", &arr1[i]);                                 // integer로 이루어진 파일을 읽어서 배열 arr1[i]에 담는다.
        fscanf(outputP, "%d", &arr2[i]);                                // integer로 이루어진 파일을 읽어서 배열 arr2[i]에 담는다.
    }
        
    int match_count = countMatch(arr1, arr2, 1000);                     // countMatch 함수에 arr1, arr2, size:1000 을 매개변수로 입력하고 반환되는 값을 int형 변수 match_count에 넣는다.
        
    fprintf(resultP, "%d\n", match_count);                              // match_count의 값들을 tab문자로 구분하여 파일에 print한다.

    for(int i = 0; i < 1000; i++)
    {
        if (arr1[i] == arr2[i])                                         // 만약 arr1과 arr2의 i번째 값이 같다면,
        {
            fprintf(resultP, "%d\t", i);                                // i값(인덱스값)을 tab문자로 구분하여 파일에 print한다.
        }
    }

    fclose(inputP);                                                     // inputP 파일 포인터를 fclose 함수의 매개변수로 넣어 열었던 파일을 닫는다.
    fclose(outputP);                                                    // outputP 파일 포인터를 fclose 함수의 매개변수로 넣어 열었던 파일을 닫는다.
    fclose(resultP);                                                    // resultP 파일 포인터를 fclose 함수의 매개변수로 넣어 열었던 파일을 닫는다.   
}

// 두 배열을 비교하여 같은 값의 개수를 세는 함수
int countMatch(int A[], int B[], int size)      // 배열 2개와 size값을 인자로 받는다.
{
    int count = 0;                              // int형 변수 count를 0으로 선언 및 초기화한다.

    for(int i = 0; i < size; i++)               // i가 0부터 999까지 1씩 증가하며 실행문을 1000번 반복한다.
    {
        if (A[i] == B[i])                       // 만약 배열 A와 B의 i번째 값이 같다면,
        {
            count++;                            // count의 값이 1 증가한다. 
        }
    }
    return count;                               // 반복문이 종료된 후의 최종 count값을 반환한다.
}