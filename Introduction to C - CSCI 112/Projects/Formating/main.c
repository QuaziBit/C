#include <stdio.h>

int main(void)
{
    //%d -> placeholder
    //%4d -> 4 mins spacing or columns

    int a = 10;
    float b = 10.05;
    double c = 10.100090912;
    char d = 'c';
    char e[] = "string";
    printf("\n\nFormated output\n\n");

    printf("int: %d\n", a);
    printf("float: %.2f\n", b);
    printf("double: %lf\n", c);
    printf("char: %c\n", d);
    printf("string: %s\n\n", e);

    printf("\n\nHEX: %04x\n\n", &d);

    system("PAUSE");

    return 0;
}