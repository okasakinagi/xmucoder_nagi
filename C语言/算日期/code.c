#include <stdio.h>
int main()
{
    int y = 0, m = 0, d = 0, sum = 0;
    scanf("%d/%d/%d", &y, &m, &d);
    m -= 1;
    switch (m)
    {
    case 12:
        sum += 31;
    case 11:
        sum += 30;
    case 10:
        sum += 31;
    case 9:
        sum += 30;
    case 8:
        sum += 31;
    case 7:
        sum += 31;
    case 6:
        sum += 30;
    case 5:
        sum += 31;
    case 4:
        sum += 30;
    case 3:
        sum += 31;
    case 2:
        sum += 28;
    case 1:
        sum += 31;
    default:
        sum += d;
    }
    if (m + 1 > 2)
    {
        if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0))
        {
            sum += 1;
        }
        else
        {
            ;
        }
    }
    else
    {
        ;
    }
    printf("%d", sum);
    return 0;
}