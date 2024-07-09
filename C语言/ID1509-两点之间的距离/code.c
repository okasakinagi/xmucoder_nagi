#include <stdio.h>
#include <math.h>

int main()
{
    double a, b, c, d, lenth;
    scanf("%lf %lf %lf %lf", &a, &b, &c, &d);
    lenth = sqrt((a - c) * (a - c) + (b - d) * (b - d));
    printf("%lf", lenth);
    return 0;
}