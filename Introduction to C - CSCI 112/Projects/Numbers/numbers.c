#include <stdio.h>

int main()
{
    int a = 10, b = 20, c = 30;

    printf("[a: %d] --- [b: %d] --- [c: %d]\n", a, b, c);
    printf("The average number is: %d\n\n", ((a + b + c)/3));

    printf("Enter new value for [a]: ");
    scanf("%d", &a);
    printf("Enter new value for [b]: ");
    scanf("%d", &b);
    printf("Enter new value for [c]: ");
    scanf("%d", &c);
    printf("[a: %d] --- [b: %d] --- [c: %d]\n\n", a, b, c);
    printf("The average number is: %d\n\n", ((a + b + c)/3));

    system("PAUSE");

    return 0;
}
