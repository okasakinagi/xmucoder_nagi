#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

vector<char> a;

void pr(string &s, int n)
{
    for (int i = 1; i <= n; i++)
        if ((count(a.begin(), a.end(), s[i - 1])) >= 2)
            return;
    for (int i = 0; i < n; i++)
    {
        cout << a[i];
    }
    cout << endl;
}

void paixu(int time, string &s, int n)
{
    if (time >= n)
    {
        pr(s, n);
        return;
    }
    else
    {
        for (int i = 1; i <= n; i++)
        {
            a[time] = s[i - 1];
            paixu(time + 1, s, n);
        }
    }
}

int main()
{
    string s;
    cin >> s;
    sort(s.begin(), s.end());
    int n = s.size();
    for (int i = 0; i < n; i++)
        a.push_back(0);
    paixu(0, s, n);
    return 0;
}