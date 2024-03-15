#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h> // close()
#include <fcntl.h> // creat()

int main()
{
    char *fname = "test.txt"; // 생성할 파일명(파일 경로)
    int fd;

    // test.txt라는 파일을 rw-rw-rw- 권한으로 생성 (umask에 따라 권한이 조금씩 달라질 수 있음)
    // 성공 시 생성한 파일의 파일 디스크릡터, 실패 시 -1 반환
    // 이 때 fd는 "쓰기 전용"으로 열린 파일 디스크립터
    // 만약 test.txt라는 파일이 기존에 존재했다면 기존 파일의 내용은 삭제됨
    // 또한 권한은 기존의 파일의 값을 가짐
    if((fd = creat(fname, 0466)) < 0){
        fprintf(stderr, "creat error for %s\n", fname);
        exit(1);
    }
    else{
        printf("Success!\nFilename: %s\nDescriptor: %d\n", fname, fd);
        close(fd);
    }

    exit(0);
}