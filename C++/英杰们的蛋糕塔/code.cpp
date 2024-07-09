// 非完全原创
#include <iostream>
#include <algorithm>
#include <cmath>
#define MAX 22
using namespace std;

int r[MAX] = {0}, h[MAX] = {0};
int Min = 100000;
int sumMinS[27], sumMinV[27];
int search(int time, int V, int N, int pre_res, int pre_r = -1, int pre_h = -1)
{
    if (N <= 0)
    {
        if (V == 0)
        {
            Min = min(Min, pre_res);
        }
        return 0;
    }
    if (pre_r > 1 && (2 * V / (pre_r - 1) + pre_res >= Min))
        return 0;
    if (V < sumMinV[N - 1])
        return 0;
    if (sumMinS[N] + pre_res >= Min)
        return 0;
    int res;
    for (int r = pre_r - 1; r >= N; r--)
    {
        int H_max = (1.0 * V / (r * r) + 1);
        if (H_max > pre_h - 1)
            H_max = pre_h - 1;
        for (int h = H_max; h >= N; h--)
        {
            if ((r * r * h > V) || (r * r * h == V && N != 1) || (r * r * h != V && N == 1))
                continue;
            res = 2 * h * r;
            if (time == 0)
                res += r * r;
            search(time + 1, V - r * r * h, N - 1, res + pre_res, r, h);
        }
    }
    return 0;
}

int main()
{
    int V = 0, N = 0;
    cin >> V >> N;
    sumMinS[0] = sumMinV[0] = 0;
    for (int i = 1; i < N; i++)
    {
        sumMinS[i] = sumMinS[i - 1] + 2 * i * i;
        sumMinV[i] = sumMinV[i - 1] + i * i * i;
    }
    search(0, V, N, 0, sqrt(double((V - sumMinV[N - 1]) + 1)), (V - sumMinV[N - 1] / (N * N) + 1));
    cout << (Min == 100000 ? 0 : Min) << endl;
    return 0;
}