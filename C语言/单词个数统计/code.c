#include <stdio.h>

int main()
{
    char s[100000];
    gets(s);
    int count = 0, i = -1, flag1 = 0, flag2 = 0;
    do
    {
        i++;
        if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))
        {
            flag1 = 1;
            continue;
        }
        else
        {
            flag2 = 1;
        }
        if (flag1 == 1 && flag2 == 1)
        {
            count++;
            flag1 = 0;
            flag2 = 0;
        }
    } while (s[i] != '\0');
    printf("%d", count);
    return 0;
}