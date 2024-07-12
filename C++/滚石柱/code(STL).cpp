#include <iostream>
#include <string>
#include <cstring>
#include <map>
#include <queue>
#include <algorithm>
#define MAX 505
using namespace std;

typedef pair<int, int> PII;
typedef pair<PII, int> PIIB; // 0为站立，1为横躺，2为竖躺

int dir_x[][4] = {{-2, 0, 0, 1}, {-1, 0, 0, 1}, {-1, 0, 0, 2}},
    dir_y[][4] = {{0, 1, -2, 0}, {0, 2, -1, 0}, {0, 1, -1, 0}},
    dir_b[][4] = {{2, 1, 1, 2}, {1, 0, 0, 1}, {0, 2, 2, 0}};
string court[MAX];
int N, M;
PIIB start, target;

int bfs()
{
    // init
    map<PIIB, bool> is;
    map<PIIB, int> dist;
    queue<PIIB> Queue;
    Queue.push(start);
    is[start] = true;
    dist[start] = 0;
    // start
    while (!Queue.empty())
    {
        PIIB temp = Queue.front();
        Queue.pop();
        for (int i = 0; i < 4; i++)
        {
            int x = temp.first.first + dir_x[temp.second][i], y = temp.first.second + dir_y[temp.second][i], b = dir_b[temp.second][i];
            PIIB temp2 = PIIB(PII(x, y), b);
            if (is.find(temp2) != is.end())
                continue;
            else
                is[temp2] = true;
            if (b == 0 && (x < 0 || y < 0 || x >= N || y >= M || court[x][y] == '#' || court[x][y] == 'E'))
                continue;
            else if (b == 1 && (x < 0 || y < 0 || x >= N || y >= M - 1 || court[x][y] == '#' || court[x][y + 1] == '#'))
                continue;
            else if (b == 2 && (x < 0 || y < 0 || x > N - 1 || y >= M || court[x][y] == '#' || court[x + 1][y] == '#'))
                continue;
            Queue.push(temp2);
            if (dist.find(temp2) != dist.end())
                dist[temp2] = min(dist[temp2], dist[temp] + 1);
            else
                dist[temp2] = dist[temp] + 1;
        }
    }
    if (dist.find(target) != dist.end())
        return dist[target];
    else
        return -1;
}

int main()
{
    freopen("1.in", "r", stdin);
    while (cin >> N >> M, M != 0 && N != 0)
    {
        start = PIIB(PII(-1, -1), -1);
        for (int i = 0; i < N; i++)
        {
            // court[i].clear();
            cin >> court[i];
            int temp = court[i].find('X');
            if (temp != string::npos)
            {
                if (start.second == -1)
                {
                    if (temp == court[i].rfind('X'))
                        start = PIIB(PII(i, temp), 0);
                    else
                        start = PIIB(PII(i, temp), 1);
                }
                else
                    start.second = 2;
            }
            temp = court[i].find('O');
            if (temp != string::npos)
            {
                target = PIIB(PII(i, temp), 0);
            }
        }
        int output = bfs();
        if (output != -1)
            cout << output << endl;
        else
            cout << "Impossible" << endl;
    }
}