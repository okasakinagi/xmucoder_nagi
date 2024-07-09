#include <cstdio>
#include <map>
#include <iostream>
#include <algorithm>
using namespace std;
#define MAX 50

typedef int LL;
int dir_x[3] = {0, 1, 0}, dir_y[3] = {1, 0, -1};

LL search(int court[][MAX], int cur_x, int cur_y, int n)
{
    if (n <= 0)
        return 1;
    LL res = 0;
    for (int i = 0; i < 3; i++)
    {
        int x = cur_x + dir_x[i], y = cur_y + dir_y[i];
        if (court[x][y])
            continue;
        else
        {
            court[x][y] = 1;
            res += search(court, x, y, n - 1);
            court[x][y] = 0;
        }
    }
    return res;
}

int main()
{
    int N = 0;
    cin >> N;
    int court[MAX][MAX] = {0};
    court[0][MAX >> 1] = 1;
    cout << search(court, 0, MAX >> 1, N);
    return 0;
}