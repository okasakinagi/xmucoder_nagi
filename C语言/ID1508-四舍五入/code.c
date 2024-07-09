#include <stdio.h>

int main()
{
    double a;
    scanf("%lf", &a);
    a = (int)(a * 100 + 0.5);
    a = a / 100;
    printf("%f", a);
    return 0;
}