#include <stdio.h>

int main()
{
    int add(int x, int y);
    int a = 0, b = 0, r = 0;
    scanf("%d %d", &a, &b);
    r = add(a, b);
    printf("%d", r);
    return 0;
}

int add(int x, int y)
{
    int z = 0, i = 1;
    while (x > 0 || y > 0)
    {
        z = z + ((x % 10 + y % 10) % 10 * i);
        i = i * 10;
        x = x / 10;
        y = y / 10;
    }
    return z;
}