#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
using namespace std;

vector<int> a;

struct tester
{
    vector<int> a;
} Array[100];

int jishu = 0;

void paixu(int time, int n)
{
    if (time >= n)
    {
        Array[jishu++].a = a;
        return;
    }
    else
    {
        for (int i = 1; i <= n; i++)
        {
            int j;
            for (j = 0; j < time; j++)
            {
                if (i == a[j] || abs(a[j] - i) == abs(time - j))
                    break;
            }
            if (j == time)
            {
                a[time] = i;
                paixu(time + 1, n);
            }
        }
    }
}

int main()
{
    a.resize(8);
    paixu(0, 8);
    int T = 0;
    cin >> T;
    for (int t = 0; t < T; t++)
    {
        int r = 0;
        cin >> r;
        for (int i = 0; i < 8; i++)
        {
            cout << Array[r - 1].a[i];
        }
        cout << endl;
    }
    return 0;
}