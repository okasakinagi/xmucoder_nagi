#include <stdio.h>
int main()
{
    int pay = 0;
    scanf("%d", &pay);
    int pay100, pay50, pay20, pay10, pay5, pay2, pay1;
    pay100 = pay / 100;
    pay -= pay100 * 100;
    pay50 = pay / 50;
    pay -= pay50 * 50;
    pay20 = pay / 20;
    pay -= pay20 * 20;
    pay10 = pay / 10;
    pay -= pay10 * 10;
    pay5 = pay / 5;
    pay -= pay5 * 5;
    pay2 = pay / 2;
    pay -= pay2 * 2;
    pay1 = pay / 1;
    printf("100 - %d\n", pay100);
    printf("50 - %d\n", pay50);
    printf("20 - %d\n", pay20);
    printf("10 - %d\n", pay10);
    printf("5 - %d\n", pay5);
    printf("2 - %d\n", pay2);
    printf("1 - %d\n", pay1);
    return 0;
}