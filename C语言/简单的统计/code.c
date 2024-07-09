#include <stdio.h>

int CalcNum(int A[], int n, int K)
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if (A[i] == K)
        {
            count++;
        }
        else
        {
            ;
        }
    }
    return count;
}

int main()
{
    int n, K, i, A[10000];
    scanf("%d", &n);
    for (i = 0; i < n; i++)
        scanf("%d", &A[i]);
    scanf("%d", &K);
    printf("%d\n", CalcNum(A, n, K));
    return 0;
}