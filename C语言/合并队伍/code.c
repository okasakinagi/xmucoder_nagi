#include <stdio.h>

int main()
{
    int N, M, temp = 0;
    scanf("%d %d", &N, &M);
    int sum[M + N];
    for (int i = 0; i < M + N; i++)
    {
        scanf("%d", &sum[i]);
    }
    for (int i = 0; i < M + N - 1; i++)
    {
        for (int j = 0; j < M + N - 1 - i; j++)
        {
            if (sum[j] > sum[j + 1])
            {
                temp = sum[j];
                sum[j] = sum[j + 1];
                sum[j + 1] = temp;
            }
            else
            {
                ;
            }
        }
    }
    for (int i = M + N - 1; i >= 0; i--)
    {
        printf("%d ", sum[i]);
    }
    return 0;
}