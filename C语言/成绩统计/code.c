#include <stdio.h>

int main()
{
    int N = 0;
    scanf("%d", &N);
    int a[N], temp = 0, count[5] = {0, 0, 0, 0, 0}, sum = 0;
    for (int n = 0; n < N; n++)
    {
        scanf("%d", &a[n]);
        temp = a[n] / 10;
        switch (temp)
        {
        case 10:
        {
            ;
        }
        case 9:
        {
            count[0]++;
            break;
        }
        case 8:
        {
            count[1]++;
            break;
        }
        case 7:
        {
            count[2]++;
            break;
        }
        case 6:
        {
            count[3]++;
            break;
        }
        default:
        {
            count[4]++;
            break;
        }
        }
        sum += a[n];
    }
    double ave = 0;
    ave = (sum * 1.0) / N;
    printf("%.1lf %d %d %d %d %d", ave, count[0], count[1], count[2], count[3], count[4]);
    return 0;
}