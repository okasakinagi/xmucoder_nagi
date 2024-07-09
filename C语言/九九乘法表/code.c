#include <stdio.h>

int main()
{
    int a = 0, b = 0, r = 0, n = 0;
    scanf("%d", &n);
    for (a = 1; a <= n; a++)
    {
        for (b = 1; b <= a; b++)
        {
            r = a * b;
            printf("%d*%d=%d ", b, a, r);
        }
        printf("\n");
    }
    return 0;
}