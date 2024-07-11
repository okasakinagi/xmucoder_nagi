#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <queue>
#define MAX 1005
using namespace std;
typedef pair<int, int> PII;

int W, H;
string court[MAX];
int dist[MAX][MAX];
int dir_x[] = {0, 1, -1, 0},
    dir_y[] = {-1, 0, 0, 1};

void print()
{
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            cout << dist[i][j] << ' ';
            ;
        }
        cout << endl;
    }
}

void bfs()
{
    queue<PII> Queue;
    // init
    memset(dist, -1, sizeof(dist));
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            if (court[i][j] == '1')
            {
                dist[i][j] = 0;
                Queue.push(PII(i, j));
            }
        }
    }
    // start
    while (!Queue.empty())
    {
        PII temp = Queue.front();
        Queue.pop();
        for (int i = 0; i < 4; i++)
        {
            int x = temp.first + dir_x[i], y = temp.second + dir_y[i];
            if (x < 0 || y < 0 || x >= H || y >= W)
                continue;
            if (court[x][y] != '0')
                continue;
            court[x][y] = '1';
            dist[x][y] = dist[temp.first][temp.second] + 1;
            Queue.push(PII(x, y));
        }
    }
}

int main()
{
    cin >> H >> W;
    for (int i = 0; i < H; i++)
    {
        cin >> court[i];
    }
    bfs();
    print();
    return 0;
}