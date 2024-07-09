#include <stdio.h>

int n = 0, count = 0, a[15];

void pr()
{
    for (int i = 1; i <= n; i++)
    {
        printf("%d", a[i]);
    }
    printf("\n");
    count++;
}

void dfs(int i, int j)
{
    a[j] = i;
    if (i == 0 && j <= n)
    {
        for (int r = 0; r <= 1; r++)
        {
            dfs(r, j + 1);
        }
        if (j == n)
            pr();
    }
    else if (i == 1 && j <= n)
    {
        dfs(0, j + 1);
        if (j == n)
            pr();
    }
    else
    {
        ;
    }
}

int main()
{
    int i, j;
    scanf("%d", &n);
    for (i = 0; i <= 1; i++)
        dfs(i, 1);
    printf("%d", count);
}