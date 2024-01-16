# 2. 배열과 구조체

### 배열 (Array)

동일한 타입의 데이터들이 순차적/선형으로 저장되어 있는 자료구조로, 배열의 이름은 **배열의 시작주소**를 나타낸다. 각 요소는 인덱스를 사용하여 접근되며, 각 요소는 연속된 메모리 공간에 저장된다.

```c
#include <stdio.h>

int main()
{
    int array[] = {0, 1, 2, 3, 4};

    // 둘 다 array 배열의 시작주소 값을 출력함
    printf("0x%X\n", array);
    printf("0x%X\n", &array[0]);

    return 0;
}
```

<br><br>

### 구조체 (Struct)

다양한 타입의 데이터(멤버)들이 묶여 하나의 새로운 데이터 타입을 정의하는 사용자 정의 자료형이다. 보통 `typedef`와 같이 사용된다. 또한 **구조체 자체를 선언할 때에는 메모리가 할당되지 않는다.** 구조체 변수를 선언하거나 동적으로 할당할 때에 메모리가 할당된다. 즉, 구조체를 선언한다는 것은 해당 구조체의 크기와 멤버 구조를 정의한다는 것을 의미한다.

```c
// typedef를 사용하지 않음
struct Person{
    char name[10];
    int age;
};
struct Person p1, p2;

// typedef를 사용함
typedef struct{
    char name[10];
    int age;
}Person;
Person p1, p2;
```

구조체 자체를 비교할 수는 없으며, `==`와 같은 비교 연산자를 통해 각각의 멤버들을 비교해야 한다.

```c
int personEqual(Person p1, Person p2){
    // strcmp(a, b)는 두 개의 문자열을 비교하여 동일하면 0을 반환
    if(strcmp(p1.name, p2.name))
        return 0;
    if(p1.age != p2.age)
        return 0;

    return 1;
}
```

<br><br>

### 공용체 (Union)

구조체와 유사하지만 여러 개의 멤버들이 메모리 공간을 공용으로 사용한다는 특징을 가진 데이터 구조이다. 모든 멤버가 같은 메모리 영역을 공유하기 때문에, 하나의 멤버에 값을 할당하면 다른 멤버의 값도 동일하게 변경된다.

```c
#include <stdio.h>

// 공용체 정의
union MyUnion {
    int intValue;
    float floatValue;
    char stringValue[20];
};

int main() {
    // 공용체 변수 선언
    union MyUnion myUnion;

    // 각 멤버에 값 할당
    myUnion.intValue = 42;

    // 값 출력
    printf("정수 값: %d\n", myUnion.intValue);
    printf("실수 값: %f\n", myUnion.floatValue);  // 같은 메모리를 공유하므로 정수 값이 실수로 해석됨
    printf("문자열 값: %s\n", myUnion.stringValue);  // 같은 메모리를 공유하므로 정수 값이 문자열로 해석됨

    return 0;
}
```