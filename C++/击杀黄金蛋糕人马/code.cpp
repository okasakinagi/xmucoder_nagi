#include <iostream>
#include <vector>
#include <algorithm>
#define MAX 20
using namespace std;

int W, H, M;
int memory[20][20][400] = {0}; // 建立数据库

int search(int m, int x, int y)
{
    if (m <= 0)
        return x * y;
    if (memory[x][y][m] != 0)
        return memory[x][y][m]; // 读取数据库
    // 横切
    int Min = 400;
    for (int i = 1; i < y; i++)
    {
        for (int j = 0; j <= m - 1; j++)
        {
            int m1, m2;
            m1 = search(j, x, i);
            m2 = search(m - 1 - j, x, y - i);
            Min = min(Min, max(m1, m2));
        }
    }
    if (x == y)
        return memory[x][y][m] = Min;
    // 纵切
    for (int i = 1; i < x; i++)
    {
        for (int j = 0; j <= m - 1; j++)
        {
            int m1, m2;
            m1 = search(j, i, y);
            m2 = search(m - 1 - j, x - i, y);
            Min = min(Min, max(m1, m2));
        }
    }
    return memory[x][y][m] = Min;
}

int main()
{
    cin >> W >> H >> M;
    while (W > 0 && H > 0 && M > 0)
    {
        cout << search(M - 1, H, W) << endl;
        cin >> W >> H >> M;
    }
    return 0;
}