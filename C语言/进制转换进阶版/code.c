#include <stdio.h>
#include <string.h>

char ch[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

int convert(int n, int m, char result[])
{
    int temp = 0, l = 0;
    while (n != 0)
    {
        result[l] = ch[n % m];
        n /= m;
        l++;
    }
    for (int i = 0; i < l / 2; i++)
    {
        temp = result[i];
        result[i] = result[l - 1 - i];
        result[l - 1 - i] = temp;
    }
}

int main()
{
    int n, m, T;
    char result[1024];
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &n, &m);
        memset(result, 0, 1024);
        convert(n, m, result);
        printf("%s\n", result);
    }
    return 0;
}