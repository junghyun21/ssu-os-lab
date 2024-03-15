#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // close()
#include <fcntl.h> // creat(), open(), open()의 oflag 인자에 들어갈 플래그

int main()
{
    char *fname = "test.txt";
    int fd;

    // creat()의 리턴 값은 쓰기 전용으로 열린 파일 디스크립터
    if((fd = creat(fname, 0666)) < 0){
        fprintf(stderr, "creat error for %s\n", fname);
        exit(1);
    }
    else{
        // 해당 파일의 데이터를 읽기 위해서는 파일을 닫고 open()을 통해 다시 파일 디스크립터를 할당받아야 함
        close(fd);
        fd = open(fname, O_RDWR);
        printf("Succeeded!\n<%s> is new readable and writable\n", fname);
    }

    exit(0);
}