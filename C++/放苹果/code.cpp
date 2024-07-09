#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

int put(int x, int y)
{
    if (x < y)
    {
        return put(x, x);
    }
    else if (x == 0)
    {
        return 1;
    }
    else if (y <= 0)
    {
        return 0;
    }
    else
    {
        return put(x, y - 1) + put(x - y, y);
    }
}

int main()
{
    int T = 0;
    cin >> T;
    for (int t = 0; t < T; t++)
    {

        int M = 0, N = 0;
        cin >> M >> N;
        if ((M == 0 && N != 0) || (M == 0 && N == 0))
        {
            cout << '1' << endl;
            continue;
        }
        else if (M != 0 && N == 0)
        {
            cout << '0' << endl;
            continue;
        }
        else
        {
            cout << put(M, N) << endl;
        }
    }
    return 0;
}