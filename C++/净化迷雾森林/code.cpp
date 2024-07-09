#include <cstring>
#include <map>
#include <iostream>
#include <algorithm>
#define MAX 27
using namespace std;

typedef long long LL;
int dir_x[4] = {-1, 0, 1, 0}, dir_y[4] = {0, 1, 0, -1}; // 上右下左
char court[MAX][MAX];
int W, H;
int search(int cur_x, int cur_y)
{
    court[cur_x][cur_y] = '#';
    int res = 1;
    for (int i = 0; i < 4; i++)
    {
        int x = cur_x + dir_x[i], y = cur_y + dir_y[i];
        if (((x >= 0 && y >= 0) && (x < H && y < W)) && court[x][y] == '.')
        {
            res += search(x, y);
        }
    }
    return res;
}

int main()
{
    cin >> W >> H;
    while (W != 0 && H != 0)
    {
        int cur_x = 0, cur_y = 0;
        for (int i = 0; i < H; i++)
        {
            for (int j = 0; j < W; j++)
            {
                cin >> court[i][j];
                if (court[i][j] == '@')
                {
                    cur_x = i;
                    cur_y = j;
                }
            }
        }
        cout << search(cur_x, cur_y) << endl;
        cin >> W >> H;
    }
    return 0;
}