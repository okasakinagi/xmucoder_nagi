#include <stdio.h>

int main()
{
    int T = 0;
    scanf("%d", &T);
    for (int t = 0; t < T; t++)
    {
        char a[9] = {
            '\0',
            '\0',
            '\0',
            '\0',
            '\0',
            '\0',
            '\0',
            '\0',
            '\0',
        };
        scanf("%s", a);
        for (int i = 8; i >= 0; i--)
        {
            if (a[i] != '\0')
            {
                switch (a[i])
                {
                case '0':
                    printf("zero ");
                    break;
                case '1':
                    printf("one ");
                    break;
                case '2':
                    printf("two ");
                    break;
                case '3':
                    printf("three ");
                    break;
                case '4':
                    printf("four ");
                    break;
                case '5':
                    printf("five ");
                    break;
                case '6':
                    printf("six ");
                    break;
                case '7':
                    printf("seven ");
                    break;
                case '8':
                    printf("eight ");
                    break;
                case '9':
                    printf("nine ");
                    break;
                }
            }
        }
        printf("\n");
    }
    return 0;
}