#include <stdio.h>
#include <string.h>

int main()
{
    int N = 0;
    char ch[2];
    scanf("%d", &N);
    gets(ch);
    for (int n = 0; n < N; n++)
    {
        char t[100001], s[100001];
        gets(t);
        gets(s);
        long long int len_s = 0, len_t = 0, count = 0, flag = 0;
        len_t = strlen(t);
        len_s = strlen(s);
        for (int i = 0; i < len_t;)
        {
            if (i + len_s > len_t)
                break;
            for (int j = 0; j < len_s; j++)
            {
                if (t[i + j] == s[j])
                    flag = 1;
                else
                {
                    flag = 0;
                    break;
                }
            }
            if (flag == 1)
            {
                count++;
                i += len_s;
            }
            else
            {
                i++;
            }
        }
        printf("%d\n", count);
    }
    return 0;
}