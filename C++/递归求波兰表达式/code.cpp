#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <cstdio>
using namespace std;

inline double suan(double x, double y, char fu)
{
    switch (fu)
    {
    case '+':
        return x + y;
    case '-':
        return x - y;
    case '*':
        return x * y;
    case '/':
        return x / y;
    default:
        return -1;
    }
}

double get_a_num(char get)
{
    char temp[10000];
    int i = 0;
    temp[i++] = get;
    while (scanf("%c", &get) != EOF && get != ' ' && get != '\n')
    {
        temp[i++] = get;
    }
    temp[i++] = '\0';
    return atof(temp);
}

double calculate(char get)
{

    double first = 0, second = 0;
    char get_new;
    cin >> get_new;
    if (get_new >= '0' && get_new <= '9')
    {
        first = get_a_num(get_new);
        cin >> get_new;
        if (get_new >= '0' && get_new <= '9')
            second = get_a_num(get_new);
        else
            second = calculate(get_new);
    }
    else
    {
        first = calculate(get_new);
        cin >> get_new;
        if (get_new >= '0' && get_new <= '9')
            second = get_a_num(get_new);
        else
            second = calculate(get_new);
    }
    return suan(first, second, get);
}

int main()
{
    char get;
    cin >> get;
    printf("%lf\n", calculate(get));
    return 0;
}