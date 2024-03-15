#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // lseek(), lseek()의 whence 인자에 사용되는 상태 플래그
#include <fcntl.h> // open()
#include <sys/types.h> // off_t 타입 정의

int main()
{
    char *fname = "test.txt";
    off_t fsize;
    int fd;

    if((fd = open(fname, O_RDWR)) < 0){
        fprintf(stderr, "open error for %s\n", fname);
        exit(1);
    }
    
    // 성공 시, 변경된 오프셋 반환
    // 실패 시, -1 반환
    if((fsize = lseek(fd, 0, SEEK_END)) < 0){
        fprintf(stderr, "lseek error\n");
        exit(1);
    }

    printf("The size of <%s> is %ld bytes.\n", fname, fsize);

    exit(0);
}