#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <cmath>
#include <algorithm>
using namespace std;

void chai(int time, int N)
{
    if (N == 0)
        return;
    if (time > 0)
        cout << "+";
    int a = int(log2(N));
    if (a == 0)
    {
        cout << "2(0)";
        return;
    }
    else if (a == 1)
        cout << "2";
    else if (a == 2)
        cout << "2(2)";
    else
    {
        cout << "2(";
        chai(0, a);
        cout << ")";
    }
    chai(time + 1, N - pow(2, a));
}

int main()
{
    int N = 0;
    cin >> N;
    chai(0, N);
    return 0;
}