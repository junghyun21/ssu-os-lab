#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "employee.h"

// 직원들의 정보가 record 단위로 파일에 순서대로 저장되어 있음
// 정보를 알고 싶은 직원의 순서를 입력받고 그 순서에 해당하는 직원 정보 출력
// (순서 = 파일에 저장된 순서(위치))
int main(int argc, char *argv[])
{
    struct employee record;
    int fd;
    int record_num;

    // 명령행 인자가 없으면 에러
    if(argc < 2){
        fprintf(stderr, "Usage : %s file\n", argv[0]);
        exit(1);
    }

    // 명령행 인자로 입력받은 파일 오픈
    if((fd = open(argv[1], O_RDONLY)) < 0){
        fprintf(stderr, "open error for %s\n", argv[1]);
        exit(1);
    }

    // 입력 받은 순서에 위치한 직원 정보를 record 변수에 저장하고 출력
    while(1){
        printf("Enter record number: ");
        scanf("%d", &record_num);

        // 음수 입력 시 종료
        if(record_num < 0)
            break;

        // lseek(): 성공 시 변경된 오프셋을, 실패 시 -1을 리턴
        // off_t는 long 또는 int와 같음
        if(lseek(fd, (long)record_num * sizeof(record), SEEK_SET) < 0){
            fprintf(stderr, "lseek error\n");
            exit(1);
        }

        // 1바이트 이상 읽어온 경우: 파일에서 읽어온 정보를 record에 저장 및 출력
        if(read(fd, (char *)&record, sizeof(record)) > 0)
            printf("Employee: %s Salart: %d\n", record.name, record.salary);
        // 파일의 끝에 도달하여 1바이트도 읽지 못한 경우 또는 에러가 발생한 경우
        else
            printf("Record %d not found\n", record_num);
    }

    close(fd);
    exit(0);
}