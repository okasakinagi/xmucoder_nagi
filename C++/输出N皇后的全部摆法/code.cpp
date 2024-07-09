#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
using namespace std;

vector<int> a;

inline bool xiexian(int x, int y)
{
    return fabs((a[x] - a[y]) / ((x - y) * 1.0)) == 1;
}

void pr(int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << a[i];
    }
    cout << endl;
}

void paixu(int time, int n)
{
    if (time >= n)
    {
        pr(n);
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
    int N = 0;
    cin >> N;
    for (int i = 0; i < N; i++)
        a.push_back(0);
    paixu(0, N);
    return 0;
}