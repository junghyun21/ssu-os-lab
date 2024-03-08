#include <stdio.h>
#include <stdlib.h> // exit() 정의
#include <fcntl.h> // oflag(open()의 작동 방식 결정)에 사용되는 플래그 정의 

int main()
{
    char *fname = "./test.txt";
    int fd;

    if((fd = open(fname, O_RDONLY)) < 0){
        fprintf(stderr, "open error for %s\n", fname);
        exit(1);
    }
    else{
        printf("Success!\n");
        printf("Filename: %s\n", fname);
        printf("Descriptor: %d\n", fd);
    }

    exit(0);
}

