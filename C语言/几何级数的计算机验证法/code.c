#include <stdio.h>
#include <math.h>

int main()
{
    int T = 0;
    double x = 0;
    scanf("%d", &T);
    for (int t = 0; t < T; t++)
    {
        int n = -1;
        scanf("%lf", &x);
        double left = 0, right = 0;
        left = 1 / (1 - x);
        while (fabs(left - right) > (1e-6))
        {
            n += 1;
            right += pow(x, n);
        }
        printf("%d\n", n);
    }
    return 0;
}