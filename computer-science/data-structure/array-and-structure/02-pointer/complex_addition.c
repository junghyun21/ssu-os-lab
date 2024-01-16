#include <stdio.h>

typedef struct{
    double re;
    double im;
}Complex;

void assign(Complex *, double, double);
void add(Complex *, Complex *, Complex *);

int main()
{
    Complex c1, c2, c3; // c1, c2: 피연산자 , c3: 결과값

    assign(&c1, 1.0, 2.0); // c1 = 1 + 2i
    assign(&c2, 3.0, 4.0); // c2 = 3 + 4i

    add(&c3, &c1, &c2);

    printf("%f + %fi\n", c3.re, c3.im);

    return 0;
}

void assign(Complex *p, double real, double imag)
{
    p->re = real;
    p->im = imag;
}

void add(Complex *res, Complex * p, Complex *q)
{
    res->re = p->re + q->re;
    res->im = p->im + q->im;
}