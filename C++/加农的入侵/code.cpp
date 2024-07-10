#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <queue>
#define MAX 105
using namespace std;
typedef pair<int, int> PII;

int W, H;
string court[MAX];
int dir_x[] = {-1, -1, -1, 0, 0, 1, 1, 1}, dir_y[] = {1, 0, -1, 1, -1, 1, 0, -1};

int bfs(int x, int y)
{
    queue<PII> Queue;
    int res = 0;
    int distance[MAX][MAX];
    // init
    memset(distance, -1, sizeof(distance));
    distance[y - 1][x - 1] = 0;
    Queue.push(PII(x, y));
    // start
    while (!Queue.empty())
    {
        PII temp = Queue.front();
        Queue.pop();
        for (int i = 0; i < 8; i++)
        {
            int x = temp.first + dir_x[i], y = temp.second + dir_y[i];
            if (x <= 0 || y <= 0 || x > W || y > H)
                continue;
            if (court[y - 1][x - 1] != '.')
                continue;
            court[y - 1][x - 1] = 'M';
            distance[y - 1][x - 1] = distance[temp.second - 1][temp.first - 1] + 1;
            Queue.push(PII(x, y));
            res = max(res, distance[y - 1][x - 1]);
        }
    }
    return res;
}

int main()
{
    int x, y;
    cin >> W >> H >> x >> y;
    for (int i = 0; i < H; i++)
    {
        cin >> court[i];
    }
    cout << bfs(x, y) << endl;
    return 0;
}