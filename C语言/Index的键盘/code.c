#include <stdio.h>

int main()
{
    char put[] = "INDEXZPCHKABFGJLMOQRSTUVWY";
    char get = 0;
    get = getchar();
    for (int i = 0; i < 26; i++)
    {
        if (get == put[i] && (get != 'I' && get != 'A' && get != 'R'))
        {
            printf("%c", put[i - 1]);
            break;
        }
        else if (get == 'I' || get == 'A' || get == 'R')
        {
            printf("-");
            break;
        }
        else
            continue;
    }
    return 0;
}