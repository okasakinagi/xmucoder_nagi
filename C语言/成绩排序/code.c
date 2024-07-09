#include <stdio.h>

int main()
{
    int N = 0;
    scanf("%d", &N);
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
    for (int i = N - 1; i >= 0; i--)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
    return 0;
}