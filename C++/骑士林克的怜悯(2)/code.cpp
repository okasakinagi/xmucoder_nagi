#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <queue>
#define MAX 155
using namespace std;
typedef pair<int, int> PII;

int W, H;
PII target, start;
string court[MAX];
int dir_x[] = {1, -1, 2, -2, 2, -2, 1, -1},
    dir_y[] = {-2, -2, -1, -1, 1, 1, 2, 2};

int bfs()
{
    queue<PII> Queue;
    int res = MAX;
    int distance[MAX][MAX];
    // init
    memset(distance, -1, sizeof(distance));
    distance[start.first][start.second] = 0;
    Queue.push(start);
    // start
    while (!Queue.empty())
    {
        PII temp = Queue.front();
        Queue.pop();
        for (int i = 0; i < 8; i++)
        {
            int x = temp.first + dir_x[i], y = temp.second + dir_y[i];
            if (x < 0 || y < 0 || x >= H || y >= W)
                continue;
            if (court[x][y] != '.')
                continue;
            court[x][y] = 'K';
            distance[x][y] = distance[temp.first][temp.second] + 1;
            PII t(x, y);
            Queue.push(t);
            if (t == target)
            {
                res = min(res, distance[x][y]);
            }
        }
    }
    return res;
}

int main()
{
    cin >> W >> H;
    for (int i = 0; i < H; i++)
    {
        cin >> court[i];
        int temp;
        if (temp = court[i].find('K'), temp != string::npos)
        {
            start.first = i;
            start.second = temp - 1;
        }
        else if (temp = court[i].find('H'), temp != string::npos)
        {
            target.first = i;
            target.second = temp - 1;
        }
    }
    cout << bfs() << endl;
    return 0;
}