#include <stdio.h>
#include <string.h>

int main()
{
    char s[1001], t[1001];
    fgets(t, 1001, stdin);
    fgets(s, 1001, stdin);
    int ls = strlen(s), lt = strlen(t), flag = 0;
    for (int i = 0, j = 0; i < lt; i++)
    {
        if (t[i] == s[j])
            j++;
        else
        {
            ;
        }
        if (j == ls)
        {
            flag = 1;
            break;
        }
    }
    printf("%d", flag);
    return 0;
}