#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>
#define MAX 150050
using namespace std;

typedef pair<int, int> PII;

int head[MAX], e[MAX], wight[MAX], ne[MAX], idx = 0;
int dist[MAX];
bool is[MAX] = {false};
int N = 0, M = 0;

void add(int x, int y, int z)
{
    e[idx] = y, wight[idx] = z, ne[idx] = head[x], head[x] = idx++;
}

int bfs()
{
    priority_queue<PII, vector<PII>, greater<PII>> Queue;
    memset(dist, 0x3f, sizeof(dist));
    dist[1] = 0;
    Queue.push(PII(0, 1));
    while (!Queue.empty())
    {
        PII temp = Queue.top();
        Queue.pop();
        int sign = temp.second, dis = temp.first;
        if (is[sign])
            continue;
        is[sign] = true;
        for (int i = head[sign]; i != -1; i = ne[i])
        {
            int j = e[i];
            if (dist[j] <= dist[sign] + wight[i])
                continue;
            dist[j] = dist[sign] + wight[i];
            Queue.push(PII(dist[j], j));
        }
    }
    if (dist[N] == 0x3f3f3f3f)
        return -1;
    return dist[N];
}

int main()
{
    cin >> N >> M;
    int x, y, z;
    memset(head, -1, sizeof(head));
    for (int i = 0; i < M; i++)
    {
        scanf("%d %d %d", &x, &y, &z);
        add(x, y, z);
    }
    cout << bfs() << endl;
    return 0;
}