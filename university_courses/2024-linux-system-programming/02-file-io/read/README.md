# read()

> [!note]  
> 본 문서는 숭실대학교 컴퓨터학부 홍지만 교수님의 2024년 1학기 리눅스시스템프로그래밍 수업을 듣고 정리한 내용입니다. 모든 내용은 개인적으로 정리한 것으로, 틀린 부분이 있을 수 있습니다.

<br>

```c
#include <unistd.h>

ssize_t read(int filedes, void *buf, size_t nbytes);
```

- `filedes`: 읽을 파일을 가리키는 파일 디스크립터
- `buf`: 읽어온 데이터를 저장할 버퍼의 시작 주소로 다양한 종류의 데이터를 읽을 수 있도록 void * 타입으로 지정 (casting 필수)
- `nbytes`: 읽어올 최대 바이트 수
- reture 값: 성공 시 읽어온 바이트 수 또는 파일의 끝에 도달한 경우에는 0, 실패 시 -1 반환 및 errno 설정

<br>

[read()](./read2.c)는 **오픈한 파일에서 데이터를 읽을 때 사용하는 시스템콜 함수**로, 읽기 전용 또는 읽기 쓰기 혼용 접근 권한으로 오픈된 파일(filedes)로부터 지정된 메모리(buf)로 요청한 바이트(nbytes)만큼의 데이터를 읽어온다. 이 때 **실제로 읽은 바이트 수는 요청한 바이트 수보다 적을 수 있다.** 또한 `read()`는 파일의 실제 데이터가 저장된 블록 상태를 직접 다루는 것이 아닌, i-node를 통해 데이터에 접근한다. 따라서 데이터의 일관성을 위해 `read()` 호출 시, 커널은 호출이 수행되는 동안 i-node에 락(lock)을 걸고 해당 파일에 접근하려는 다른 모든 연산을 블록(block)시킨다. 즉, `read()`가 수행되는 동안은 해당 파일의 i-node에 대한 어떠한 접근도 허용하지 않는다.

<br><br>

### 실제로 읽은 바이트 수가 요청한 바이트 수보다 적은 경우

- 일반 파일에 요청된 수만큼의 바이트들을 읽기 전에 파일의 끝에 도달했을 때
- 터미널 파일에서 자료를 읽을 때
- 네트워크에서 자료를 읽을 때
- 파이프나 FIF에서 자료를 읽을 때
- 레코드 기반 장치에서 자료를 읽을 때
- 요청된 크기의 자료 중 일부만 읽은 상황에서 시그널에 의해 연산이 가로채였을 때

<br><br>

### 예제

- [[source] employeefile.txt 파일에 저장되어 있는 직원 정보를 구조체 단위로 출력](./read1.c)
- [[source] test.txt 파일의 내용을 한 글자씩 읽어 들여 출력](./read3A.c)
- [[source] test.txt 파일의 내용의 총 줄 수를 출력](./read3B.c)
- [[source] 인자로 입력받은 파일에서 입력받은 숫자에 해당하는 줄의 내용 출력](./read4.c)