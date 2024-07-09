#include <stdio.h>
#include <string.h>

int main()
{
    char a[10000];
    gets(a);
    for (int i = 0; i < 10000; i++)
    {
        if (a[i] >= 'a' && a[i] <= 'z')
        {
            a[i] = 'z' - a[i] + 'a';
        }
        else if ((a[i] >= 'A' && a[i] <= 'Z'))
        {
            a[i] = 'Z' - a[i] + 'A';
        }
        else
        {
            ;
        }
    }
    printf("%s", a);
    return 0;
}