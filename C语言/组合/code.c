#include <stdio.h>

int N = 0, M = 0, a[10];
int pr()
{
    for (int i = 1; i <= M; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}
int m(int now, int time)
{
    a[time] = now;
    if (time == M)
    {
        pr();
        return 0;
    }
    else
    {
        for (int i = now + 1; i <= N; i++)
        {
            m(i, time + 1);
        }
    }
}
int main()
{
    scanf("%d %d", &N, &M);
    for (int i = 1; i <= N - M + 1; i++)
        m(i, 1);
    return 0;
}