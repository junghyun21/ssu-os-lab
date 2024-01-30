#ifndef PRECEDENCE_H
#define PRECEDENCE_H

#define OPERATOR 9

// 올바른 토큰의 종류: (, ), +, -, *, /, %, ^, ., \0, 공백, 숫자
typedef enum Token{
    LPAREN, RPAREN, PLUS, MINUS, TIMES, DIVIDE, MOD, POWER, EOS, DOT, SPACE, NUM
}Token;

extern int isp[OPERATOR]; // 스택 내에 저장될 우선순위 값
extern int icp[OPERATOR]; // 스택에 넣기 전에 우선순위 비교 시에 사용될 우선순위 값

#endif