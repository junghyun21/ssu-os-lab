#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main()
{
    char buf[BUFFER_SIZE];
    int length;

    length = read(0, buf, BUFFER_SIZE); // 표준 입력 장치에서 데이터 읽어옴
    write(1, buf, length); // 표준 출력 장치로 데이터 출력

    exit(0);
}