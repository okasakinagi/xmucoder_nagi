#include <stdio.h>
#include <math.h>

int center(int a[], int n)
{
    int k = 0, min = 100000, kr = 0;
    for (k = 1; k <= n; k++)
    {
        int s1 = 0, s2 = 0;
        for (int i = 1; i <= k; i++)
            s1 += a[i];
        for (int i = k + 1; i <= n; i++)
            s2 += a[i];
        if (fabs(s1 - s2) < min)
        {
            min = fabs(s1 - s2);
            kr = k;
        }
    }
    return kr;
}

int main()
{
    int i, n, a[10001];
    scanf("%d", &n);
    for (i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
    }
    printf("%d", center(a, n));
    return 0;
}