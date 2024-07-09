#include <stdio.h>
#include <string.h>

int main()
{
    int T = 0;
    scanf("%d", &T);
    for (int t = 0; t < T; t++)
    {
        char read[10000], s[4] = "sin";
        scanf("%s", read);
        int l = strlen(read);
        int i1 = 0, i2 = 0;
        for (i1 = 0; i1 < l; i1 += 4)
        {
            if (read[i1] == 'x')
            {
                printf("x");
                break;
            }
            else if (read[i1] == 's')
            {
                printf("sin(");
            }
            else if (read[i1] == 'c')
            {
                printf("sqrt(1-sin(");
            }
            else if (read[i1] == 't')
            {
                printf("1/sqrt(1/sin(");
            }
        }
        for (i2 = i1; i2 >= 0; i2 -= 4)
        {
            if (read[i2] == 'x')
            {
                // printf(")");
            }
            else if (read[i2] == 's')
            {
                printf(")");
            }
            else if (read[i2] == 'c')
            {
                printf(")^2)");
            }
            else if (read[i2] == 't')
            {
                printf(")^2-1)");
            }
        }
        printf("\n");
    }
    return 0;
}