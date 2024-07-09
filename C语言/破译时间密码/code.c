#include <stdio.h>
#include <string.h>

int main()
{
    char s[1001];
    gets(s);
    int len = strlen(s), n = 0, q = 0, m = 0, d = 0;
    for (int i = 0; i < len; i++)
    {
        if (s[i] >= '0' && s[i] <= '9')
            n = n * 10 + s[i] - '0';
    }
    q = (n * 3) % 1131 + 101;
    m = q / 100;
    d = q % 38;
    printf("%d %d %d %d\n", n, q, m, d);
    switch (m)
    {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
    {
        if (d > 31 || d <= 0)
            goto end2;
        else
            goto end1;
    }
    case 2:
    {
        if (d > 28 || d <= 0)
            goto end2;
        else
            goto end1;
    }
    case 4:
    case 6:
    case 9:
    case 11:
    {
        if (d > 30 || d <= 0)
            goto end2;
        else
            goto end1;
    }
    }
    if (0)
    {
    end1:
        printf("%d.%d", m, d);
    }
    if (0)
    {
    end2:
        printf("input error!");
    }
    return 0;
}