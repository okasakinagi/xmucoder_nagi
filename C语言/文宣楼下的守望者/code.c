#include <stdio.h>
#include <math.h>

int main()
{
    int T = 0;
    scanf("%d", &T);
    for (int t = 0; t < T; t++)
    {
        int a = 0, b = 0, c = 0, d = 0;
        scanf("%d %d %d %d", &a, &b, &c, &d);
        double result = 1;
        int p = 0;
        p = (d / b >= 1) ? 1 : 0;
        result *= pow((1 - a / 100.0), d);
        result *= pow((1 - c / 100.0), p);
        result *= 100;
        printf("%.2lf%%\n", result);
    }
    return 0;
}