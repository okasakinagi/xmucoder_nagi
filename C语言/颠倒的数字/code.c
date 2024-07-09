#include <stdio.h>

void re(char str[], int count, int a)
{
    int temp = 0;
    for (int i = a; i < (count - a) / 2 + a; i++)
    {
        temp = str[i];
        str[i] = str[count + (a - 1) - i];
        str[count + (a - 1) - i] = temp;
    }
    printf("%s\n", str);
}

void inverse(int n)
{
    char str[9];
    int l = 0;
    sprintf(str, "%d", n);
    for (int i = 0; i < 9; i++)
    {
        if (str[i] == '\0')
            break;
        else
            l++;
    }
    if (n >= 0)
    {
        re(str, l, 0);
    }
    else
    {
        re(str, l, 1);
    }
}

int main()
{
    int T, n;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n);
        inverse(n);
    }
    return 0;
}