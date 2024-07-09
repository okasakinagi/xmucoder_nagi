#include <cstring>
#include <map>
#include <iostream>
#include <algorithm>
#define MAX 27
using namespace std;

int dir_x[] = {-1, 1, -2, 2, -2, 2, -1, 1}, dir_y[] = {-2, -2, -1, -1, 1, 1, 2, 2}; // 优先靠左的格子
int court[MAX][MAX];
int W, H;
int out_x[MAX * MAX], out_y[MAX * MAX];

void print_true()
{
    for (int i = 0; i < W * H; i++)
    {
        char temp = out_y[i] + 'A';
        cout << temp << out_x[i] + 1;
    }
    cout << endl;
}

int search(int cur_x, int cur_y, int time)
{
    court[cur_x][cur_y] = 1;
    out_x[time] = cur_x, out_y[time] = cur_y;
    if (time == W * H - 1)
        return true;
    for (int i = 0; i < 8; i++)
    {
        int x = cur_x + dir_x[i], y = cur_y + dir_y[i];
        if (((x >= 0 && y >= 0) && (x < H && y < W)) && court[x][y] == 0)
        {
            if (search(x, y, time + 1))
                return true;
        }
    }
    court[cur_x][cur_y] = 0;
    return false;
}

int main()
{
    int N = 0;
    cin >> N;
    for (int k = 0; k < N; k++)
    {

        memset(&court[0][0], 0, MAX * MAX);
        cin >> H >> W;
        int flag = 0;
        for (int i = 0; i < H; i++)
        {
            for (int j = 0; j < W; j++)
            {
                if (search(i, j, 0))
                {
                    flag = 1;
                    break;
                }
            }
            if (flag)
                break;
        }
        cout << '#' << k + 1 << ':' << endl;
        if (flag)
            print_true();
        else
            cout << "none" << endl;
    }
    return 0;
}