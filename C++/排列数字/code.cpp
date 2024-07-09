#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> a;

void pr(int n)
{
    for (int i = 1; i <= n; i++)
        if ((count(a.begin(), a.end(), i)) >= 2)
            return;
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << ' ';
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
            a[time] = i;
            paixu(time + 1, n);
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