# open()

> [!note]  
> 본 문서는 숭실대학교 컴퓨터학부 홍지만 교수님의 2024년 1학기 리눅스시스템프로그래밍 수업을 듣고 정리한 내용입니다. 모든 내용은 개인적으로 정리한 것으로, 틀린 부분이 있을 수 있습니다.

<br>

```c
#include <sys/types.h> // mode_t 정의
#include <sys/stat.h> // mode 인자에서 사용되는 플래그 정의
#include <fcntl.h> // file control -> oflag 인자에서 사용되는 플래그 정의

int open(const char *pathname, int oflag);
int open(const char *pathname, int oflag, mode_t mode);
```

- `pathname`: 오픈하거나 생성할 파일의 상대 경로 또는 절대 경로
- `oflag`: 오픈할 파일의 특성으로 하나 또는 여러 개를 논리합 연산으로 결합한 값 사용
- `mode`: 생성할 파일의 접근 권한으로 파일의 읽기, 쓰기, 실행 모드 지정 가능
- reture 값: 성공 시 해당 파일을 참조하기 위한 파일 디스크립터 반환, 실패 시 -1 반환 및 errno 설정

<br>

[open()](./open.c) 은 **파일을 오픈하거나 생성할 때 사용하는 시스템콜 함수**이며, 모든 파일은 사용되기 전 반드시 이를 호출해야 한다. `open()`이 호출되면 커널은 동일한 파일이 시스템에 존재하고 있는지 확인하고, 파일에 대한 올바른 접근 권한을 검사한 후, 파일 디스크립터를 리턴한다.

<br><br>

### oflag 인자

open()의 작동 방식을 결정하는 인자로 `<fcntl.h>`에 정의된 상수들 중 하나 또는 여러 개를 논리합(OR(|)) 연산으로 결합한 값을 인자로 사용한다. 이 때 인자로 사용되는 플래그(flag)[^1]는 반드시 상호배타적으로 하나 사용되어야 하는 플래그와 선택적으로 여러 개 사용할 수 있는 플래그로 나뉜다.

[^1]: 특정 상태를 나타내는 데 사용되는 변수 또는 비트

<br>

> 반드시 사용해야 하는 플래그

| 플래그 | 내용 |
| --- | --- |
| `O_RDONLY` | 파일을 읽기 전용으로 오픈 <br>오픈한 파일에 쓰기를 시도하면 에러 발생 |
| `O_WRONLY` | 파일을 쓰기 전용으로 오픈 <br>오픈한 파일에 읽기를 시도하면 에러 발생 |
| `O_RDWR` | 파일을 읽기와 쓰기가 모두 가능하도록 오픈 |

위의 플래그들은 반드시 사용되어야 하지만, 상호배타적으로 사용되어야 한다. 즉, 한 가지의 플래그만 지정할 수 있다.

<br>

> 선택적으로 사용할 수 있는 플래그 (일부)

| 플래그 | 내용 |
| --- | --- |
| `O_APPEND` | 파일에 기록 시 해당 파일의 오프셋(offset) 위치를 자동으로 파일의 끝(EOF)으로 이동 <br>파일에 쓰기를 시도하기 전에 lseek()을 이용해 오프셋 위치를 파일의 끝으로 옮기는 작업과 동일|
| `O_CREAT` | 파일이 존재하지 않을 경우 동일한 이름의 파일 생성 <br>open()의 세번째 인자인 mode를 반드시 함께 지정 <br>주로 `O_EXCL` 또는 `O_TRUNC` 플래그와 함께 사용|
| `O_EXCL` | 단독으로 사용될 수 없으며, 반드시 `O_CREAT` 플래그와 함께 사용 <br>파일이 이미 존재한다면 open()은 실패 및 에러 리턴|
| `O_TRUNC` | 해당 파일이 이미 존재하는 경우 해당 파일의 크기를 0으로 변경되며 이전 데이터 전부 삭제 <br>파일 접근 권한이 O_RDONLY인 경우에는 파일을 지우는 작업 미수행|
| `O_NOCTTY` | 파일이 터미널 장치일 경우에 해당 장치를 이 프로세스의 제어 터미널로 미배정 |
| `O_NONBLOCK` | 입출력을 시도한 시점에서 블록 상태가 될 수 있는 장치라면 이후의 입출력 작업들에 대해 논블록 모드로 동작|

위의 플래그들은 선택적으로 사용할 수 있으며, 논리합(OR(|)) 연산을 통해 새로운 파일 특성을 지정할 수 있다.

<br><br>

### mode 인자

생성할 파일의 접근 권한을 나타내는 인자로 `<sys/stat.h>`에 정의된 상수 혹은 권한을 나타내는 8진수의 숫자를 인자로 사용한다. **O_CREAT 플래그를 사용할 때에는 반드시 mode 인자를 지정**해주어야 하지만, 그렇지 않은 경우에는 생략해도 된다. 또한 mode 인자는 논리합(OR(|)) 연산을 통해 여러 개의 플래그를 사용할 수 있다.  
(cf. mode 인자의 타입인 `mode_t`는 `<sys/types.h>`에 정의되어 있다.)

| 플래그 | 내용 |
| --- | --- |
| `S_IRWXU` | 파일 소유자의 읽기, 쓰기, 실행 권한 지정 (0700)|
| `S_IRUSR` | 파일 소유자의 읽기 권한 지정 (0400)|
| `S_IWUSR` | 파일 소유자의 쓰기 권한 지정 (0200)|
| `S_IXUSR` | 파일 소유자의 실행 권한 지정 (0100)|
| `S_IRWXG` | 소유 그룹의 읽기, 쓰기, 실행 권한 지정 (0070)|
| `S_IRGRP` | 소유 그룹의 읽기 권한 지정 (0040)|
| `S_IWGRP` | 소유 그룹의 쓰기 권한 지정 (0020)|
| `S_IXGRP` | 소유 그룹의 실행 권한 지정 (0010)|
| `S_IRWXO` | 다른 사용자의 읽기, 쓰기, 실행 권한 지정 (0007)|
| `S_IROTH` | 다른 사용자의 읽기 권한 지정 (0004)|
| `S_IWOTH` | 다른 사용자의 쓰기 권한 지정 (0002)|
| `S_IXOTH` | 다른 사용자의 실행 권한 지정 (0001)|