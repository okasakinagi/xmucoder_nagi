// 采用数组和结构体，加速运行过程，时间为STL版的十分之一，但内存消耗是三倍，可以ACxmuoj
#include <iostream>
#include <string>
#include <cstring>
#include <map>
#include <queue>
#include <algorithm>
#define MAX 505
using namespace std;

struct stone
{
    int X, Y, B; // 0为站立，1为横躺，2为竖躺
    stone(int x, int y, int b) { X = x, Y = y, B = b; }
    stone() { X = -1, Y = -1, B = -1; }
    bool operator==(stone &other) { return (X == other.X && Y == other.Y && B == other.B); }
};

int is[MAX][MAX][3] = {0};
int dist[MAX][MAX][3];
int dir_x[][4] = {{-2, 0, 0, 1}, {-1, 0, 0, 1}, {-1, 0, 0, 2}},
    dir_y[][4] = {{0, 1, -2, 0}, {0, 2, -1, 0}, {0, 1, -1, 0}},
    dir_b[][4] = {{2, 1, 1, 2}, {1, 0, 0, 1}, {0, 2, 2, 0}};
string court[MAX];
int N, M;
stone start, target;

int bfs()
{
    // init
    queue<stone> Queue;
    Queue.push(start);
    memset(dist, 0x3f, sizeof(dist));
    memset(is, 0, sizeof(is));
    is[start.X][start.Y][start.B] = 1;
    dist[start.X][start.Y][start.B] = 0;
    // start
    while (!Queue.empty())
    {
        stone temp = Queue.front();
        Queue.pop();
        for (int i = 0; i < 4; i++)
        {
            int x = temp.X + dir_x[temp.B][i], y = temp.Y + dir_y[temp.B][i], b = dir_b[temp.B][i];
            stone temp2 = stone(x, y, b);
            if (b == 0 && (x < 0 || y < 0 || x >= N || y >= M || court[x][y] == '#' || court[x][y] == 'E'))
                continue;
            else if (b == 1 && (x < 0 || y < 0 || x >= N || y >= M - 1 || court[x][y] == '#' || court[x][y + 1] == '#'))
                continue;
            else if (b == 2 && (x < 0 || y < 0 || x > N - 1 || y >= M || court[x][y] == '#' || court[x + 1][y] == '#'))
                continue;
            if (is[x][y][b])
                continue;
            else
                is[x][y][b] = 1;
            Queue.push(temp2);
            dist[x][y][b] = min(dist[x][y][b], dist[temp.X][temp.Y][temp.B] + 1);
        }
    }
    if (dist[target.X][target.Y][target.B] == 0x3f3f3f3f)
        return -1;
    else
        return dist[target.X][target.Y][target.B];
}

int main()
{
    while (cin >> N >> M, M != 0 && N != 0)
    {
        start = stone(-1, -1, -1);
        for (int i = 0; i < N; i++)
        {
            cin >> court[i];
            int temp = court[i].find('X');
            if (temp != string::npos)
            {
                if (start.B == -1)
                {
                    if (temp == court[i].rfind('X'))
                        start = stone(i, temp, 0);
                    else
                        start = stone(i, temp, 1);
                }
                else
                    start.B = 2;
            }
            temp = court[i].find('O');
            if (temp != string::npos)
            {
                target = stone(i, temp, 0);
            }
        }
        int output = bfs();
        if (output != -1)
            cout << output << endl;
        else
            cout << "Impossible" << endl;
    }
    return 0;
}