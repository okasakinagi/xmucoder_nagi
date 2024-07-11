#include <iostream>
#include <cstring>
#include <algorithm>
#define MAX 510
using namespace std;

int route[MAX][MAX];
int dist[MAX];
bool is[MAX] = {false};
int N = 0, M = 0;

int bfs()
{
    memset(dist, 0x3f, sizeof(dist));
    dist[1] = 0;
    for (int i = 0; i < N - 1; i++)
    {
        int t = -1;
        for (int j = 1; j <= N; j++)
            if (!is[j] && (t == -1 || dist[t] > dist[j]))
                t = j;
        for (int j = 1; j <= N; j++)
            dist[j] = min(dist[j], dist[t] + route[t][j]);
        is[t] = true;
    }
    if (dist[N] == 0x3f3f3f3f)
        return -1;
    return dist[N];
}

int main()
{
    cin >> N >> M;
    int x, y, z;
    memset(route, 0x3f, sizeof(route));
    for (int i = 0; i < M; i++)
    {
        scanf("%d %d %d", &x, &y, &z);
        if (route[x][y] == 0)
            route[x][y] = z;
        else
            route[x][y] = min(route[x][y], z);
    }
    cout << bfs() << endl;
    return 0;
}