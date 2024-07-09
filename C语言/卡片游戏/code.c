#include <stdio.h>

int main()
{
    int N = 0, k = 0, flag = 0;
    scanf("%d %d", &N, &k);
    int a[N];
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &a[i]);
        if (i == 0)
        {
            continue;
        }
        else
        {
            for (int j = 0; j < i + 1; j++)
            {
                if (a[i] + a[j] == k)
                {
                    flag = 1;
                    break;
                }
                else
                {
                    flag = 0;
                }
            }
        }
        if (flag == 1)
        {
            printf("Yes");
            break;
        }
    }
    if (flag == 0)
        printf("No");
    return 0;
}