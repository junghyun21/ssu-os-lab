#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define TABLE_SIZE 128
#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
    static struct{
        long offset;
        int length;   
    }table[TABLE_SIZE];
    char buf[BUFFER_SIZE];
    long offset;
    int entry;
    int i;
    int length;
    int fd;

    if(argc < 2){
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        exit(1);
    }

    // argv[1]에 해당하는 파일이 존재하지 않는 경우 -1 리턴
    if((fd = open(argv[1], O_RDONLY)) < 0){
        fprintf(stderr, "open error for %s\n", argv[1]);
        exit(1);
    }

    entry = 0;
    offset = 0;
    while((length = read(fd, buf, BUFFER_SIZE)) > 0){
        // 입력받은 바이트 수만큼 반복
        // 개행문자를 기준으로 나누어 테이블 엔트리에 저장
        for(i = 0; i < length; i++){
            table[entry].length++;
            offset++;

            // 개행문자를 읽은 경우에는 다음 테이블 엔트리에 데이터를 저장해야됨
            // 각각의 엔트리를 가리키는 테이블의 인덱스인 entry 증가
            // 이 전까지 읽은 총 바이트 수는 다음 테이블 엔트리의 시작 바이트이므로, offset 값을 지금까지의 바이트 수로 갱신
            if(buf[i] == '\n')
                table[++entry].offset = offset;
        }
    }

// 디버그 모드일 때 실행
#ifdef DEBUG
    for(i = 0; i < entry; i++)
        printf("%d: %ld, %d\n", i + 1, table[i].offset, table[i].length);
#endif

    while(1){
        printf("Enter line number: ");
        scanf("%d", &length);

        // 사용자 입장에서 첫번째 줄은 실제로는 0번 인덱스에 저장되어 있음
        if(--length < 0)
            break;

        lseek(fd, table[length].offset, SEEK_SET);

        // 읽고자하는 오프셋이 파일의 범위를 넘어갔거나, 파일을 읽을 수 없다면 다시 출력한 줄의 번호를 입력받음
        if(read(fd, buf, BUFFER_SIZE) <= 0)
            continue;

        // 첫번째 length는 사용자가 입력한 출력한 줄의 번호
        // 두번째 length는 해당 줄의 바이트 수
        // printf()를 통해 출력하기 위해서는 문자열의 마지막 문자는 널문자여야 함
        // table에 데이터를 저장할 때 개행문자까지 같이 저장했기 때문에 출력 시 개행문자를 추가하지 않아도 됨
        buf[table[length].length] = '\0';
        printf("%s", buf);
    }

    close(fd);
    exit(0);
}