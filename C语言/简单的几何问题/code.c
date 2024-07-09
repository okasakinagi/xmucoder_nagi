#include <stdio.h>

void GetInfo(double r, double result[])
{
    double pi = 3.14159;
    result[0] = 2 * pi * r;
    result[1] = pi * r * r;
    result[2] = 4 * pi * r * r;
    result[3] = (4 / 3.0) * pi * r * r * r;
    return 0;
}

int main()
{
    double r, result[4];
    scanf("%lf", &r);
    GetInfo(r, result);
    printf("%.2f\n%.2f\n%.2f\n%.2f", result[0], result[1], result[2], result[3]);
    return 0;
}