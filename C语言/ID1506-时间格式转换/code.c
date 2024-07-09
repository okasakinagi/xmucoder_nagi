#include <stdio.h>
int main()
{
    int h, min, s;
    scanf("%d", &s);
    min = s / 60;
    s = s - min * 60;
    h = min / 60;
    min = min - h * 60;
    printf("%d:%d:%d", h, min, s);
    return 0;
}
