# lseek()

> [!note]  
> 본 문서는 숭실대학교 컴퓨터학부 홍지만 교수님의 2024년 1학기 리눅스시스템프로그래밍 수업을 듣고 정리한 내용입니다. 모든 내용은 개인적으로 정리한 것으로, 틀린 부분이 있을 수 있습니다.

<br>

```c
#include <sys/types.h> // 타입 off_t 정의 (off_t 타입이 정의되기 전까지는 long 타입 사용)
#include <unistd.h> // lseek(), whence 인자에 사용되는 플래그 정의

off_t lseek(int filedes, off_t offset, int whence);
```

- `filedes`: 오프셋 위치를 변경할 파일을 가리키는 파일 디스크립터
- `offset`: 오프셋을 이동시킬 양
- `whence`: 오프셋을 이동시킬 때 기준 위치
- reture 값: 성공 시 변경된 새로운 파일 오프셋, 실패 시 -1 반환 및 errno 설정

<br>

[lseek()](./lseek2.c)은 **오픈된 파일의 오프셋 위치를 명시적으로 변경할 때 사용하는 시스템콜 함수**로, 커널 내부에서 현재 파일의 오프셋 위치만을 변경할 수 있다. 오프셋 위치의 기본 값은 `open()`에서 `O_APPEND` 상태 플래그를 적용되지 않는 한 **파일이 오픈될 때 0으로 초기화**된다. `lseek()`는 입출력 함수임에도 불구하고 별도의 입출력을 하지는 않으며, [read()](https://github.com/junghyun21/ssu-os-lab/tree/main/university_courses/2024-linux-system-programming/02-file-io/read)와 [write()](https://github.com/junghyun21/ssu-os-lab/tree/main/university_courses/2024-linux-system-programming/02-file-io/write)를 호출할 때 같이 사용된다. (`read()`와 `write()`는 파일의 현재 오프셋 위치부터 수행되며, 입출력 동작 후 새로운 오프셋의 위치는 이전 오프셋에 지정된 바이트 수만큼 더해진 값으로 갱신된다.)

<br><br>

### whence 인자

오프셋을 이동시킬 때 기준이 되는 위치를 지정하는 인자로 `<unistd.h>`에 정의된 상수를 상태 플래그로 사용한다.

| 플래그 | 내용 |
| --- | --- |
| SEEK_SET | 기준 오프셋 위치는 **파일의 처음** |
| SEEK_CUR | 기준 오프셋 위치는 **파일의 현재 오프셋**|
| SEEK_END | 기준 오프셋 위치는 **파일의 끝** |

<br>

위의 플래그들을 활용하여 **파일의 현재 오프셋**과 **파일의 크기**를 구할 수 있으며, `O_APPEND` 플래그 없이도 **파일 끝에 내용 추가**가 가능하다.

```c
// 파일의 현재 오프셋
off_t currpos;
currpos = lseek(filedees, (off_t)0, SEEK_CUR);

// 파일의 크기
off_t fsize;
fsize = lseek(filedes, (off_t)0, SEEK_END);

// 파일 끝에 내용 추가 (O_APPEND 사용 x)
filedes = open(filename, O_RDWR);
lseek(filedes, (off_t)0, SEEK_END);
write(filedes, buf, BUFSIZE);

// 파일 끝에 내용 추가 (O_APPEND 사용 o)
filedes = open(filename, O_RDWR | O_APPEND);
write(filedes, buf, BUFSIZE);
```

[[source] lseek()을 통해 파일의 크기 출력](./lseek1.c)