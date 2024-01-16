#include <stdio.h>
#include <stdlib.h> // exit()
#include <string.h>

#define MAX_SIZE 25

void insertString(char *, char *, int);

int main()
{
    int idx = 1; // 삽입할 위치(인덱스)

    char str1[MAX_SIZE] = {"amobile"};
    char str2[MAX_SIZE] = {"uto"};

    insertString(str1, str2, idx);

    printf("%s\n", str1);

    return 0;
}

void insertString(char *str1, char *str2, int idx)
{
    char temp[MAX_SIZE];
    
    memset(temp, 0, MAX_SIZE); // temp의 MAX_SIZE 바이트를 0으로 설정

    // strlen(str): str의 길이 반환(널문자 제외한 길이)
    if(idx < 0 && idx > strlen(str1)){
        fprintf(stderr, "Position is out of bounds\n");
        exit(1);
    }
    
    // str1 내부에 아무 값도 없다면 str1의 값을 str2의 값으로 변경
    if(!strlen(str1))
        strcpy(str1, str2);
    // str2 내부에 값이 없으면 str1은 기존과 그대로 같은 값을 가짐
    else if(strlen(str2)){
        strncpy(temp, str1, idx); // str1 중 idx개의 문자를 값을 temp에 복사
        strcat(temp, str2); // temp 뒤에 str2 연결
        strcat(temp, str1 + idx); // temp 뒤에 str1 중 idx개 이후의 문자들 연결
        strcpy(str1, temp); // temp에 저장된 문자열을 str1에 복사
    }

    return;
}