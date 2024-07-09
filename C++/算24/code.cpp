#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <cmath>
#include <algorithm>
using namespace std;

inline double suan(double x, double y, char fu)
{
    switch (fu)
    {
    case '+':
        return x + y;
    case '-':
        return fabs(x - y);
    case '*':
        return x * y;
    case '/':
        return x / y;
    default:
        return -1;
    }
}

char fuhao[4] = {'+', '-', '*', '/'};
vector<int> num;
int xuan[4];

bool count24(int time, double sum)
{
    if (time >= 4)
        if (fabs(sum - 24) <= 1e-4)
            return true;
        else
            return false;
    for (int i = 0; i < 4; i++)
    {
        int j = 0;
        for (; j < time; j++)
            if (i + 1 == xuan[j])
                break;
        if (j < time)
            continue;
        xuan[time] = i + 1;
        if (time <= 0)
            if (count24(time + 1, num[i]))
                return true;
            else
            {
                ;
            }
        else
        {
            for (int k = 0; k < 4; k++)
            {

                if (count24(time + 1, suan(sum, num[i], fuhao[k])))
                {
                    return true;
                }
            }
        }
    }
    return false;
}

int main()
{
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    while (!(a == 0 && b == 0 && c == 0 && d == 0))
    {
        num.resize(4);
        num[0] = a, num[1] = b, num[2] = c, num[3] = d;
        if (count24(0, 0))
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
        num.clear();
        cin >> a >> b >> c >> d;
    }
    return 0;
}