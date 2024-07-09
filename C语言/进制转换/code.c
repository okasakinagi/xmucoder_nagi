#include <stdio.h>
#include <string.h>

int main()
{
    int N = 0, p = 1, b = 0, i = 0, T = 0;
    char a[32];
    scanf("%d", &N);
    for (int n = 0; n < N; n++)
    {
        p = 1;
        b = 0;
        i = 0;
        scanf("%s", a);
        T = strlen(a);
        for (int t = T - 1; t >= 0; t--)
        {
            if (a[t] == '1')
            {
                b += 1 * p;
            }
            else
            {
                ;
            }
            p *= 2;
        }
        printf("%d\n", b);
    }
    return 0;
}