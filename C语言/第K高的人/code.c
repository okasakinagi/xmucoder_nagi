#include <stdio.h>

int main()
{
    int N = 0, k = 0;
    scanf("%d %d", &N, &k);
    int a[N], temp = 0;
    for (int n = 0; n < N; n++)
    {
        scanf("%d", &a[n]);
    }
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N - i - 1; j++)
        {
            if (a[j] > a[j + 1])
            {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
            else
            {
                ;
            }
        }
    }
    printf("%d", a[N - k]);
    printf("\n");
    return 0;
}