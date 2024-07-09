#include <stdio.h>

int main()
{
    int x, g, f;
    scanf("%d", &x);
    g = x * x - 550;
    if (x < g)
        f = g + x + 4;
    else
        f = g - x;
    printf("%d", f);
    return 0;
}