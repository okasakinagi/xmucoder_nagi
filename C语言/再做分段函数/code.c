#include <stdio.h>
int main()
{
    int N = 0, n = 1, x = 0, y = 1;
    scanf("%d", &N);
    for (; n <= N; n += 1)
    {
        scanf("%d", &x);
        if (x >= 0)
        {
            y = 5 * x - 10000;
            printf("%d\n", y);
        }
        else
        {
            while (x < 0)
            {
                x = fabs(x);
                x = 5 * x - 10000;
            }
            x = fabs(x);
            y = 5 * x - 10000;
            printf("%d\n", y);
        }
    }
    return 0;
}