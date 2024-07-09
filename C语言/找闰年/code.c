#include <stdio.h>

int main()
{
    int m = 0, n = 0, count = 0;
    scanf("%d %d", &m, &n);
    for (int i = m; i <= n; i += 1)
    {
        if ((i % 4 == 0 && i % 100 != 0) || (i % 400 == 0))
        {
            printf("%d ", i);
            count += 1;
            if (count % 5 == 0)
            {
                printf("\n");
            }
        }
    }
    return 0;
}