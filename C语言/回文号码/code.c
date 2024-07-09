#include <stdio.h>
#include <string.h>

int main()
{
    int N = 0, flag = 0, count = 0;
    scanf("%d", &N);
    char s[N][12];
    for (int n = 0; n < N; n++)
    {
        scanf("%s", s[n]);
        for (int i = 0; i < 11; i++)
        {
            if (s[n][i] != s[n][10 - i])
            {
                flag = 0;
                break;
            }
            else
            {
                flag = 1;
            }
        }
        if (flag == 1)
        {
            count++;
        }
        else
        {
            ;
        }
    }
    printf("%d", count);
    return 0;
}