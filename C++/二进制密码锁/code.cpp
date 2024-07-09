#include <iostream>
#include <bitset>
#include <cmath>
#include <algorithm>
using namespace std;

int bitlock(bitset<32> num, bitset<32> stdan, int N)
{
    int count = 0;
    for (int i = N - 1; i >= 0; i--)
    {
        if (num[i] == stdan[i])
            continue;
        else
        {
            if (i == 0)
                return -1;
            else
            {
                num[i].flip();
                num[i - 1].flip();
                if (i == 1)
                {
                    ;
                }
                else
                    num[i - 2].flip();
                count++;
            }
        }
    }
    return count;
}

int main()
{
    string s1, s2;
    cin >> s1 >> s2;
    int N = s1.size();
    if (N == 1)
    {
        if (s1 == s2)
        {
            cout << "0" << endl;
            return 0;
        }
        else
        {
            cout << '1' << endl;
            return 0;
        }
    }
    bitset<32> num(s1), stdan(s2);
    int out = bitlock(num, stdan, s1.size());
    if (out == -1)
    {
        num[N - 1].flip();
        num[N - 2].flip();
        out = bitlock(num, stdan, s1.size());
        if (out == -1)
            cout << "impossible" << endl;
        else
            cout << out + 1 << endl;
    }
    else
        cout << out << endl;
    return 0;
}