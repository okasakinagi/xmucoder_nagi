#include <stdio.h>
#include <math.h>

int zhan(int b1)
{
    if (b1 == 1)
        return 0;
    int temp = 1, b2 = b1 - 1;
    while (temp != 0 && b2 != 1)
    {
        temp = b1 % b2;
        b2--;
    }
    if (b2 == 1 && temp != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int primes(int a[], int n)
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if (zhan(a[i]))
        {
            count++;
        }
        else
        {
            ;
        }
    }
    return count;
}

int main()
{
    int i, n;
    int a[10000];
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }
    printf("%d", primes(a, n));
    return 0;
}