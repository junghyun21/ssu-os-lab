#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    char c;
    int fd;
    int count = 0;

    if((fd = open("test.txt", O_RDONLY)) < 0){
        fprintf(stderr, "open error for %s\n", "test.txt");
        exit(1);
    }

    // read(): 성공 시 실제로 읽은 바이트 수 혹은 파일의 끝을 읽으면 0 반환 (실패 시 -1 반환)
    // 실제로 읽은 데이터가 있는 동안만 반복
    while(read(fd, &c, 1) > 0){
        if(c == '\n')
            ++count;
    }

    printf("Total line: %d\n", count);
    exit(0);
}