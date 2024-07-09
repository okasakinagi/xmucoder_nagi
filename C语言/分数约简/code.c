#include <stdio.h>
int main()
{
    int T = 0, t = 0, a = 0, b = 0, r = 0;
    scanf("%d", &T);
    for (; t < +T; t += 1)
    {
        scanf("%d %d", &a, &b);
        if (b < 1e-12)
        {
            printf("Error!\n");
        }
        else
        {
            if (a % b == 0)
            {
                r = a / b;
                printf("%d\n", r);
            }
            else
            {
                int a1 = a, b1 = b, c = b;
                while (c != 0)
                {
                    b1 = c;
                    c = a1 % b1;
                    a1 = b1;
                }
                printf("%d/%d\n", a / b1, b / b1);
            }
        }
    }
    return 0;
}