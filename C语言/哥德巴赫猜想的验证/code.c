#include <stdio.h>
#include <math.h>

int isPrime(int num)
{
    for (int i = num - 1; i > 0; i--)
    {
        if (num % i == 0 && i != 1)
            return 0;
    }
    return num;
}

void OddDiv(int n)
{
    int p = 0, count = 0, su[1229];
    for (int i = 2; i <= n - 2; i++)
    {
        p = isPrime(i);
        if (p == 0)
            continue;
        else
        {
            su[count] = p;
            count++;
        }
    }
    for (int i1 = 0; i1 < count; i1++)
    {
        for (int i2 = i1; i2 < count; i2++)
        {
            for (int i3 = i2; i3 < count; i3++)
            {
                if (n == (su[i1] + su[i2] + su[i3]))
                {
                    printf("%d=%d+%d+%d", n, su[i1], su[i2], su[i3]);
                    return 0;
                }
                else
                {
                    ;
                }
            }
        }
    }
}

void EvenDiv(int n)
{
    int p = 0, count = 0, su[1229];
    for (int i = 2; i <= n - 2; i++)
    {
        p = isPrime(i);
        if (p == 0)
            continue;
        else
        {
            su[count] = p;
            count++;
        }
    }
    for (int i = 0; i < count; i++)
    {
        for (int j = i; j < count; j++)
        {
            if (n == (su[i] + su[j]))
            {
                printf("%d=%d+%d", n, su[i], su[j]);
                return;
            }
            else
            {
                ;
            }
        }
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    (n % 2 == 0) ? EvenDiv(n) : OddDiv(n);
    return 0;
}