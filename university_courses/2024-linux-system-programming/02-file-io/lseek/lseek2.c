#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // write(), lseek()
#include <fcntl.h> // creat(), open()
#include <sys/stat.h> // mode 인자, <sys/types.h>가 내부에 있기 때문에 따로 include 안해줘도 됨

#define CREATE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

char buf1[] = "1234567890";
char buf2[] = "ABCDEFGHIJ";

int main()
{
    // 파일의 오프셋은 그 파일의 실제 크기보다 클 수 있음
    // 이런 경우 다음 write()에서 초과된 오프셋만큼 파일의 크기가 커짐
    // -> 이를 '파일의 홀(hole)'이 만들어졌다고 함
    char *fname = "hole.txt";
    int fd;

    if((fd = creat(fname, CREATE_MODE)) < 0){
        fprintf(stderr, "creat error for %s\n", fname);
        exit(1);
    }

    // buf1에 해당하는 내용을 파일에 씀
    if(write(fd, buf1, 11) != 11){
        fprintf(stderr, "buf1 write error\n");
        exit(1);
    }

    // 파일의 오프셋을 15000으로 변경
    if(lseek(fd, 15000, SEEK_SET) < 0){
        fprintf(stderr, "lseek error\n");
        exit(1);
    }

    if(write(fd, buf2, 11) != 11){
        fprintf(stderr, "buf2 write error\n");
        exit(1);
    }

    exit(0);
}