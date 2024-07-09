#include <stdio.h>

int Ackermann(int m, int n)
{
    if (m == 0 && n > 0)
    {
        return n + 1;
    }
    else if (m == 0 && n == 0)
    {
        return 0;
    }
    else if (m > 0 && n == 0)
    {
        return Ackermann(m - 1, 1);
    }
    else if (m > 0 && n > 0)
    {
        return Ackermann(m - 1, n - 1) + n;
    }
}

int main()
{
    int T;
    scanf("%d", &T);
    int m[T], n[T];
    for (int i = 0; i < T; i++)
    {
        scanf("%d %d", &m[i], &n[i]);
    }
    for (int i = 0; i < T; i++)
    {
        printf("%d\n", Ackermann(m[i], n[i]));
    }
    return 0;
}