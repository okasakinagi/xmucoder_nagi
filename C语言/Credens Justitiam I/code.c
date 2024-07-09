#include <stdio.h>
#include <math.h>

double len(int a1, int b1, int a2, int b2)
{
    double l = 0;
    l = sqrt((a1 - a2) * (a1 - a2) + (b1 - b2) * (b1 - b2));
    return l;
}

int main()
{
    int a = 0, b = 0, x1 = 0, x2 = 0, y1 = 0, y2 = 0;
    scanf("%d %d %d %d %d %d", &x1, &y1, &x2, &y2, &a, &b);
    double l = 0;
    l = len(x1, y1, x2, y2);
    if (a - l >= 0)
    {
        printf("YES");
    }
    else if (b - l >= 0)
    {
        printf("NO");
    }
    else if (a > b)
    {
        printf("YES");
    }
    else if (a <= b)
    {
        printf("NO");
    }
    return 0;
}