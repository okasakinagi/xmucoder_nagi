#include <stdio.h>

void change(int *a, int *b, int flag)
{
    if (flag > 0)
    {
        *a = abs(*a);
        *b = abs(*b);
        return;
    }
    else if (flag == 0)
    {
        return;
    }
    else
    {
        int temp = 0;
        temp = *a;
        *a = *b;
        *b = temp;
        return;
    }
}

int main()
{
    int t, a, b, flag;
    void change(int *a, int *b, int flag);
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d%d%d", &a, &b, &flag);
        change(&a, &b, flag);
        printf("%d %d\n", a, b);
    }
    return 0;
}