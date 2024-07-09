#include <algorithm>
#include <bitset>
#include <vector>
#include <iostream>
#include <cmath>
using namespace std;

int lowbit(int n)
{
    return n & -n;
}

int main()
{
    int input = 0;
    cin >> input;
    cout << log2(lowbit(input)) << endl;
    return 0;
}