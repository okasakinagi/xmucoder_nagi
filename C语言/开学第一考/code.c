#include <stdio.h>

int main()
{
    int score;
    scanf("%d", &score);
    if (score >= 95 && score <= 100)
        printf("level4");
    else if (score >= 85 && score <= 95)
        printf("level3");
    else if (score >= 75 && score <= 85)
        printf("level2");
    else if (score >= 1 && score <= 75)
        printf("level1");
    else
        printf("Error!");
    return 0;
}