#include <stdio.h>      // 파일 입출력 기능을 포함한 헤더파일
#include <stdlib.h>     // rand 함수를 포함한 헤더파일
#include <time.h>       // time 함수를 포함한 헤더파일

void create_random(char *file);                                         // input.txt에 0~999까지의 random한 숫자를 1000개 생성하는 함수
void num_to_array(char *file, int *arr);                                // input.txt를 읽어 1차원 배열에 저장하는 함수
void divide(int *arr, int start, int end);                              // 배열을 절반으로 나눈 후, 나눠진 두 개의 배열을 다시 각각 절반으로 나눈다.
void merge(int *arr, int start, int mid, int end);                      // mergeSort Algorithm으로 정렬하는 함수   
void sort_write(int *arr, int size, char *file);                        // 정렬된 배열을 파일에 저장하는 함수
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
    sort_write(arr, 1000, "output.txt");                    // 난수들로 이루어진 배열을 mergeSort algorithm으로 정렬하여 파일에 저장한다. file 포인터의 주소값으로 "output.txt"을 입력한다.
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

// 배열을 절반으로 나누는 함수
void divide(int *arr, int start, int end)       // 배열과 양끝의 값을 인자로 받는다.
{   
    if (start < end)                            // 가장 왼쪽의 수가 가장 오른쪽의 수보다 작으면,       
    {
        int mid = (start + end) / 2;            // start와 end값을 더해서 2로 나눈 값을 중간값을 나타내는 변수 mid에 넣는다.
        divide(arr, start, mid);                // 재귀호출. 배열 arr의 start와 mid의 중간값을 찾는다.
        divide(arr, mid + 1, end);              // 재귀호출. 배열 arr의 mid + 1과 end의 중간값을 찾는다.
        merge(arr, start, mid, end);            // merge 함수 호출.
    }
}

// divide 함수를 통해 나누어진 배열들을 mergeSort Algorithm을 이용해 정렬
void merge(int *arr, int start, int mid, int end)                   // 배열, 가장 왼쪽 값, 중간 값, 가장 오른쪽 값을 인자로 받는다.
{
    int i = start;                                                  // start값을 int형 변수 i에 넣는다.
    int j = mid + 1;                                                // 오른쪽 partion의 시작값인 mid + 1값을 int형 변수 j에 넣는다.
    int k = 0;                                                      // int형 변수 k 선언 및 0으로 초기화
    int *temp = (int *)malloc((end - start + 1) * sizeof(int));     // (배열의 크기 * int 자료형 크기)만큼 메모리를 동적할당하고 반환된 void 포인터를 int형 포인터로 typecast
                                                                    // 이를 temp에 넣는다.

    while (i <= mid && j <= end)                                    // i가 mid보다 작거나 같고, j가 end보다 작거나 같을 때,
    {
        if (arr[i] < arr[j])                                        // 만약 배열 arr의 i번째 요소가 j번째 요소보다 작으면,
        {
            temp[k++] = arr[i++];                                   // 배열 arr의 i + 1번째 요소를 temp의 k + 1번째 요소에 넣는다.

        }
        else                
        {
            temp[k++] = arr[j++];                                   // 배열 arr의 j + 1번째 요소를 temp의 k + 1번째 요소에 넣는다.
        }
    }

    while (i <= mid)                                                // i가 mid보다 작거나 같으면,
    {
        temp[k++] = arr[i++];                                       // 배열 arr의 i + 1번째 요소를 temp의 k + 1번째 요소에 넣는다.
    }

    while (j <= end)                                                // j가 end보다 작거나 같으면,
    {
        temp[k++] = arr[j++];                                       // 배열 arr의 j + 1번째 요소를 temp의 k + 1번째 요소에 넣는다.
    }

    for (i = start, k = 0; i <= end; i++, k++)                      // i는 start값부터 end값까지 반복, k는 0, 실행문 실행 후 i와 k값 1씩 증가
    {
        arr[i] = temp[k];                                           // temp의 k번째 요소를 arr의 i번째 요소에 넣는다.
    }

    free(temp);                                                     // 동적으로 할당된 메모리를 free 함수를 이용해 release한다.
}
    
// 정렬된 값들을 파일에 저장하는 함수
void sort_write(int *arr, int size, char *file)     // 배열, 배열의 크기, 파일의 주소값을 인자로 받는다.
{
    divide(arr, 0, size - 1);                       // 인덱스 0부터 999까지의 배열을 divide 함수로 나눈다.

    FILE *sort_result = fopen(file, "w");           // file을 쓰기 모드로 연다. 이때 반환된 파일 포인터를 sort_result에 저장한다.

    for (int i = 0; i < 1000; i++)                 
    {
        fprintf(sort_result, "%d\t", arr[i]);       // arr[i]의 값들을 tab문자로 구분하여 파일에 print한다.
    }

    fclose(sort_result);                            // sort_result 파일 포인터를 fclose 함수의 매개변수로 넣어 열었던 파일을 닫는다. 
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