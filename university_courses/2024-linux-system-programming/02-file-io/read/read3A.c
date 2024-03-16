#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    char c;
    int fd;

    // 한 글자씩 읽을 파일 오픈
    if((fd = open("test.txt", O_RDONLY)) < 0){
        fprintf(stderr, "open error for %s\n", "test.txt");
        exit(1);
    }

    // 오픈한 파일에서 데이터를 한 글자씩 읽어옴
    // 파일에서 더 이상 읽을 데이터가 없을 때까지 반복
    while(1){
        if(read(fd, &c, 1) > 0)
            putchar(c); // c를 표준출력 장치에 문자로 출력
        else
            break;
    }

    exit(0);
}