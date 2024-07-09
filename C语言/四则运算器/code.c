#include <stdio.h>
int main()
{
    double a = 0, b = 0, aw = 0;
    char c;
    scanf("%lf %c %lf =", &a, &c, &b);
    switch (c)
    {
    case '+':
        aw = a + b;
        printf("%.4lf", aw);
        break;
    case '-':
        aw = a - b;
        printf("%.4lf", aw);
        break;
    case '*':
        aw = a * b;
        printf("%.4lf", aw);
        break;

    case '/':
        if (fabs(b) < 1e-12)
        {
            printf("Error!");
        }
        else
        {
            aw = a / b;
            printf("%.4lf", aw);
        }
        break;
    }

    return 0;
}