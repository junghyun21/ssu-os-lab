#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

int main()
{
    char buf[BUFFER_SIZE];
    char *fname = "test.txt";
    int count;
    int fd1, fd2;

    // 동일한 파일에 대해 open()을 두 번 호출
    // fd1와 fd2는 같은 파일을 가리키지만 다른 값을 가짐
    fd1 = open(fname, O_RDONLY);
    fd2 = open(fname, O_RDONLY);

    if(fd1 < 0 || fd2 < 0){
        fprintf(stderr, "open error for %s\n", fname);
        exit(1);
    }

    // fd1
    count = read(fd1, buf, 25); // test.txt의 첫번째 줄 읽어옴
    buf[count] = '\0'; // printf()를 통해 문자열을 출력해야하므로, 문자열 마지막에 널문자 추가
    printf("fd1's first printf: %s\n", buf); // 출력
    lseek(fd1, 1, SEEK_CUR); // 개행문자를 무시하기 위해 오프셋 위치 한 칸 이동

    count = read(fd1, buf, 24);
    buf[count] = '\0';
    printf("fd1's second printf: %s\n", buf);

    // fd2
    count = read(fd2, buf, 25);
    buf[count] = '\0';
    printf("fd2's first printf: %s\n", buf);
    lseek(fd2, 1, SEEK_CUR);

    count = read(fd2, buf, 24);
    buf[count] = '\0';
    printf("fd2's second printf: %s\n", buf);

    exit(0);
}