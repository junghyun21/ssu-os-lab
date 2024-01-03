#include <stdio.h>
#include <time.h>

void test();
int estimate_clock(); 
int estimate_time();

int main()
{
    double res;

    res = estimate_clock();
    printf("> clock_t를 통한 실행 시간 측정 결과: %.1fms\n", res);

    res = estimate_time();
    printf("> time_t를 통한 실행 시간 측정: %.1fs\n", res);

    return 0;
}

// 1부터 1000000까지의 합을 모두 더하는 함수
void test()
{
    long long sum = 0;

    for (int i = 1; i <= 1000000; ++i) {
        sum += i;
    }

    return;
}

// ms 단위
int estimate_clock()
{
    clock_t start, end;
    double res;

    start = clock();
    test();
    end = clock();

    res = (double)end - start;

    return res; 
}

// s eksdnl
int estimate_time()
{
    time_t start, end;
    double res;

    start = time(NULL);
    test();
    end = time(NULL);

    res = (double)difftime(end, start);

    return res;
}