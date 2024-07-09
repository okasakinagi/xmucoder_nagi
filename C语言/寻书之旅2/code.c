#include <stdio.h>

int main()
{
    int N = 0, k = 0, I = 0;
    scanf("%d %d", &N, &k);
    int a[N], temp = 0;
    for (int n = 0; n < N; n++)
    {
        scanf("%d", &a[n]);
    }
    for (int i = 0; i < N; i++)
    {
        if (a[i] == k)
        {
            I = i + 1;
            break;
        }
        else if (a[i] < k)
        {
            ;
        }
        else
        {
            I = -1;
            break;
        }
    }
    if (I == -1)
    {
        printf("Error!");
    }
    else
    {
        printf("%d", I);
    }
    return 0;
}