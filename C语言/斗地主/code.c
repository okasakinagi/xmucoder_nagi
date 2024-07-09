#include <stdio.h>
#include <string.h>

int count[] = {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1}, len_1 = 0, len_2 = 0;

int f(char s[], int len)
{
    for (int i = 0; i < len;)
    {
        switch (s[i])
        {
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        {
            count[s[i] - '3']--;
            i++;
            break;
        }
        case '1':
        {
            count[7]--;
            i += 2;
            break;
        }
        case 'J':
        {
            count[8]--;
            i++;
            break;
        }
        case 'Q':
        {
            count[9]--;
            i++;
            break;
        }
        case 'K':
        {
            count[10]--;
            i++;
            break;
        }
        case 'A':
        {
            count[11]--;
            i++;
            break;
        }
        case '2':
        {
            count[12]--;
            i++;
            break;
        }
        case 'Y':
        {
            count[13]--;
            i++;
            break;
        }
        case 'X':
        {
            count[14]--;
            i++;
            break;
        }
        default:
        {
            i++;
            break;
        }
        }
    }
    return 0;
}

int pr(int n)
{
    switch (n)
    {
    case 0:
    {
        printf("3");
        break;
    }
    case 1:
    {
        printf("4");
        break;
    }
    case 2:
    {
        printf("5");
        break;
    }
    case 3:
    {
        printf("6");
        break;
    }
    case 4:
    {
        printf("7");
        break;
    }
    case 5:
    {
        printf("8");
        break;
    }
    case 6:
    {
        printf("9");
        break;
    }
    case 7:
    {
        printf("10");
        break;
    }
    case 8:
    {
        printf("J");
        break;
    }
    case 9:
    {
        printf("Q");
        break;
    }
    case 10:
    {
        printf("K");
        break;
    }
    case 11:
    {
        printf("A");
        break;
    }
    case 12:
    {
        printf("2");
        break;
    }
    case 13:
    {
        printf("Y");
        break;
    }
    case 14:
    {
        printf("X");
        break;
    }
    }
}

int main()
{
    char s1[55], s2[55];
    fgets(s1, 55, stdin);
    fgets(s2, 55, stdin);
    len_1 = strlen(s1);
    len_2 = strlen(s1);
    f(s1, len_1);
    f(s2, len_2);
    for (int i1 = 0; i1 < 15; i1++)
    {
        if (count[i1] == 0)
        {
            continue;
        }
        else
        {
            for (int i2 = 0; i2 < count[i1]; i2++)
            {
                pr(i1);
            }
        }
    }
    return 0;
}