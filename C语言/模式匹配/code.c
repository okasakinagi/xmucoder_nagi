#include <stdio.h>
#include <string.h>

int main()
{
    int N = 0, lx = 0, ls = 0, flag = 0, count = 0;
    char text[21], test[11];
    scanf("%d", &N);
    scanf("%s", text);
    lx = strlen(text);
    for (int n = 0; n < N; n++)
    {
        scanf("%s", test);
        ls = strlen(test);
        int i = 0;
        while (text[i] != test[0] && i < lx)
            i++;
        if (i == lx)
            flag = 0;
        else if (ls == 1)
            flag = 1;
        else if (lx - i >= ls)
        {
            i++;
            for (int j = 1; j < ls; i++, j++)
            {
                if (text[i] != test[j])
                {
                    flag = 0;
                    break;
                }
                else
                {
                    flag = 1;
                    continue;
                }
            }
        }
        else
        {
            flag = 0;
        }
        if (flag == 1)
            count++;
        else
        {
            ;
        }
    }
    printf("%d", count);
    return 0;
}