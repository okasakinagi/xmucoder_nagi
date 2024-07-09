#include <stdio.h>

int main()
{
    int N = 0, n = 0;
    double a = 0, sum = 0;
    scanf("%d", &N);
    for (int n = 1; n < N + 1; n += 1)
    {
        a = n / 2.0;
        sum += a;
    }
    printf("%.4lf", sum);
    return 0;
}