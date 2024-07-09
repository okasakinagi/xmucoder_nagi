#include <stdio.h>
#include <string.h>

int main()
{
    int N = 0, flag = 0, count = 0;
    scanf("%d", &N);
    char s[N][10];
    for (int n = 0; n < N; n++)
    {
        scanf("%s", s[n]);
        if (n != 0)
        {
            for (int i = n - 1; i >= 0; i--)
            {
                if (!(strcmp(s[n], s[i])))
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
        else
        {
            count++;
        }
    }
    printf("%d", count);
    return 0;
}