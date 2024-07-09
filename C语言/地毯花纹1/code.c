#include <stdio.h>

int main()
{
    int n = 0, m = 0, flag = 0;
    scanf("%d %d", &n, &m);
    char s[n][m + 1];
    for (int i = 0; i < n; i++)
    {
        scanf("%s", s[i]);
    }
    for (int i1 = 0; i1 < n; i1++)
    {
        for (int i2 = 0; i2 < m; i2++)
        {
            int i11 = 10, i22 = 10;
            if (i1 == 0)
                i11 = 0;
            else if (i1 == n - 1)
                i11 = 1;
            else
            {
                ;
            }
            if (i2 == 0)
                i22 = 0;
            else if (i2 == m - 1)
                i22 = 1;
            else
            {
                ;
            }
            switch (i11)
            {
            case 1:
            {
                flag = ((s[i1][i2] == 'A' || s[i1][i2] == 'C') && (s[i1 - 1][i2] == 'B')) || ((s[i1][i2] == 'B') && s[i1 - 1][i2] != 'B');
                break;
            }
            case 0:
            {
                flag = ((s[i1][i2] == 'A' || s[i1][i2] == 'C') && (s[i1 + 1][i2] == 'B')) || ((s[i1][i2] == 'B') && s[i1 + 1][i2] != 'B');
                break;
            }
            default:
            {
                flag = ((s[i1][i2] == 'A' || s[i1][i2] == 'C') && (s[i1 + 1][i2] == 'B')) || ((s[i1][i2] == 'B') && s[i1 + 1][i2] != 'B') && ((s[i1][i2] == 'A' || s[i1][i2] == 'C') && (s[i1 - 1][i2] == 'B')) || ((s[i1][i2] == 'B') && s[i1 - 1][i2] != 'B');
            }
            }
            if (!flag)
                break;
            switch (i22)
            {
            case 0:
            {
                flag = ((s[i1][i2] == 'A' || s[i1][i2] == 'C') && (s[i1][i2 + 1] == 'B')) || ((s[i1][i2] == 'B') && s[i1][i2 + 1] != 'B');
                break;
            }
            case 1:
            {
                flag = ((s[i1][i2] == 'A' || s[i1][i2] == 'C') && (s[i1][i2 - 1] == 'B')) || ((s[i1][i2] == 'B') && s[i1][i2 - 1] != 'B');
                break;
            }
            default:
                flag = ((s[i1][i2] == 'A' || s[i1][i2] == 'C') && (s[i1][i2 + 1] == 'B')) || ((s[i1][i2] == 'B') && s[i1][i2 + 1] != 'B') && ((s[i1][i2] == 'A' || s[i1][i2] == 'C') && (s[i1][i2 - 1] == 'B')) || ((s[i1][i2] == 'B') && s[i1][i2 - 1] != 'B');
            }
            if (!flag)
                break;
        }
        if (!flag)
            break;
    }
    if (flag)
    {
        printf("valid");
    }
    else
    {
        printf("invalid");
    }

    return 0;
}