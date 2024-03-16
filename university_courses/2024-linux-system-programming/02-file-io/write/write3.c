#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // getpid()(해당 함수를 호출한 프로세스의 id 반환) 정의
#include <fcntl.h>
#include "employee.h"

int main(int argc, char *argv[])
{
    struct employee record;
    int fd;

    if(argc < 2){
        fprintf(stderr, "Usage : %s file\n", argv[0]);
        exit(1);
    }

    if((fd = open(argv[1], O_WRONLY | O_CREAT | O_EXCL, 0640)) < 0){
        fprintf(stderr, "open error for %s\n", argv[1]);
        exit(1);
    }

    // 입력받은 직원의 정보를 입력받은 순서대로 argv[1]에 해당하는 파일에 저장
    // 파일을 처음 오픈했을 때에는 오프셋은 0으로 초기화됨
    // write()가 끝나면, 이전의 오프셋에서 기록만 바이트만큼 더한 값이 새로운 오프셋이 됨
    while(1){
        // record 구조체 내의 데이터 입력받고 저장
        printf("Enter employee name <SPACE> salary: ");
        scanf("%s", record.name);

        // 이름에 '.'이 입력되면 프로그램 종료 
        if(record.name[0] == '.')
            break;

        scanf("%d", &record.salary);
        record.pid = getpid();

        if(write(fd, (char *)&record, sizeof(record)) != sizeof(record)){
            fprintf(stderr, "write error\n");
            exit(1);
        }
    }

    close(fd);
    exit(0);
}