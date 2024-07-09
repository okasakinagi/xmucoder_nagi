#include <stdio.h>
#include <math.h>

int main()
{
    int N = 0, max = 0, temp = 0;
    scanf("%d", &N);
    int a[N];
    for (int n = 0; n < N; n++)
    {
        scanf("%d", &a[n]);
    }
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (i == j)
            {
                continue;
            }
            else
            {
                ;
            }
            if (a[i] > a[j])
            {
                temp = a[j] * (abs(j - i));
            }
            else
            {
                temp = a[i] * (abs(j - i));
            }
            if (max < temp)
            {
                max = temp;
            }
            else
            {
                ;
            }
        }
    }
    printf("%d", max);
    printf("\n");
    return 0;
}