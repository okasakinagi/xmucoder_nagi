#include <stdio.h>

int main()
{
    int T = 0, N = 0;
    scanf("%d", &T);
    for (int t = 1; t <= T; t++)
    {
        scanf("%d", &N);
        double a[N], average = 0, sum = 0;
        for (int n = 0; n < N; n++)
        {
            scanf("%lf", &a[n]);
            sum += a[n];
        }
        for (int n = 0; n < N - 1; n++)
        {
            for (int i = 0; i < N - 1 - n; i++)
            {
                if (a[i] > a[i + 1])
                {
                    double temp = 0;
                    temp = a[i];
                    a[i] = a[i + 1];
                    a[i + 1] = temp;
                }
            }
        }
        sum = sum - a[0] - a[N - 1];
        average = (sum * 1.0) / (N - 2);
        printf("%.2lf", average);
        printf("\n");
    }
    return 0;
}