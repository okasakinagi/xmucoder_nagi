#include <stdio.h>

int main()
{
    int k = 0, w = 0, j = 0;
    double m = 0;
    scanf("%d %d", &k, &w);
    switch (k)
    {
    case 1:
        if (w > 0 && w <= 100)
        {
            j = (int)(w / 20.0 + 0.99);
            m = j * 0.8;
        }
        else if (w > 100 && w <= 2000)
        {
            j = (int)((w - 100) / 100.0 + 0.99);
            m = j * 1.2 + 4;
        }
        break;
    case 2:
        if (w > 0 && w <= 100)
        {
            j = (int)(w / 20.0 + 0.99);
            m = j * 1.2;
        }
        else if (w > 100 && w <= 2000)
        {
            j = (int)((w - 100) / 100.0 + 0.99);
            m = j * 2 + 6;
        }
        break;
    }
    printf("%.2lf", m);
    return 0;
}