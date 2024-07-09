#include <stdio.h>
#include <string.h>

int print(char a[], int l)
{
    for (int i = 0; i < l; i++)
    {
        if (a[i] == 0)
            continue;
        else
            printf("%c", a[i]);
    }
}

int main()
{
    char s[1001], t[1001];
    gets(t);
    gets(s);
    int ls = strlen(s), lt = strlen(t);
    for (int i = 0, j = 0; i < lt; i++)
    {
        if (t[i] != s[j])
        {
            j = 0;
            continue;
        }
        else
        {
            j++;
        }
        if (j == ls)
        {
            for (int k = 0; k < ls; k++)
                t[i - k] = 0;
            j = 0;
        }
        else
        {
            ;
        }
    }
    print(t, lt);
    return 0;
}