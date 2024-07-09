#include <stdio.h>

int main()
{
    int N = 0;
    scanf("%d", &N);
    int a[N], count1 = 0, count2 = 0;
    for (int n = 0; n < N; n++)
    {
        scanf("%d", &a[n]);
        if ((n + 1) % 2 == 0)
        {
            count2 += a[n];
        }
        else
        {
            count1 += a[n];
        }
    }
    printf("%d", count1);
    printf("\n");
    printf("%d", count2);
    return 0;
}