#include <stdio.h>
#include <string.h>

// 大整数相加函数
void multiply(char num1[], char num2[], char result[])
{
    int l1 = 0, l2 = 0, min = 0, max = 0, r = 0, temp = 0, flag = 0;
    l1 = strlen(num1);
    l2 = strlen(num2);
    max = l1 > l2 ? l1 : l2;
    min = l1 < l2 ? l1 : l2;
    memset(result, 0, 2002);
    for (int i1 = min - 1; i1 >= 0; i1--)
    {
        for (int i2 = max - 1, i3 = 0; i2 >= 0; i2--, i3++)
        {
            if (min == l1)
            {
                r = (num1[i1] - '0') * (num2[i2] - '0');
            }
            else
            {
                r = (num1[i2] - '0') * (num2[i1] - '0');
            }
            result[i3 + (min - 1 - i1)] += r;
            if (result[i3 + (min - 1 - i1)] > 9)
            {
                temp = (int)result[i3 + (min - 1 - i1)];
                result[i3 + (min - 1 - i1)] %= 10;
                result[i3 + (min - 1 - i1) + 1] += temp / 10;
            }
        }
    }
    for (int i = 0; i < l1 + l2; i++)
    {
        result[i] += '0';
    }
    if (!(result[l1 + l2 - 1] - '0'))
    {
        flag = 1;
        result[l1 + l2 - 1] = '\0';
    }
    else
    {
        flag = 0;
    }
    for (int i = 0; i < (l1 + l2) / 2; i++)
    {
        temp = result[i];
        result[i] = result[l1 + l2 - 1 - flag - i];
        result[l1 + l2 - 1 - flag - i] = temp;
    }
}

int main()
{
    char num1[1001];
    char num2[1001];
    char result[2002];
    scanf("%s", num1);
    scanf("%s", num2);
    if (strcmp(num1, "0") == 0 || strcmp(num2, "0") == 0)
    {
        printf("0\n");
        return 0;
    }
    multiply(num1, num2, result);
    printf("%s\n", result);
    return 0;
}