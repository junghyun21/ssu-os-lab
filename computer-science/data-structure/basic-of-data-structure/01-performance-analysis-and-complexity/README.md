# 1-1 알고리즘의 성능 분석과 정확도

### 프로그램 실행 시간 측정

프로그램의 실행 시간을 측정하는 방법에는 데이터 타입 `clock_t`와 `time_t`을 활용한 방법이 있다. 두 방법에서 사용되는 자료형, 함수, 상수는 헤더파일 `<time.h>`에 정의되어 있다.

[source](https://github.com/junghyun21/ssu-os-lab/new/main/computer-science/data-structure/basic-of-data-structure/01-performance-analysis-and-complexity/running_time.c)

- clock_t
    - `clock()` 함수는 CPU의 clock 수를 통해 시간 측정
    - `clcok()` 함수는 1초에 1000clock으로 정의되어 있으므로, 1 clock은 1ms임
    - 예를 들어 측정 중간에 `sleep()`이 사용된다면, 정확한 시간 측정이 어려울 수 있음
    - 기본 ms 단위로 측정
    - 초 단위의 측정을 원한다면 `CLOCL_PER_SEC`으로 나누어 주면 됨

- time_t
    - `time()` 함수는 현재 캘린더 시간을 통해 시간 측정
    - 초 단위 측정만 가능
