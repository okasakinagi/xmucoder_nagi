#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;

struct edge
{
    int u, v;
    int wight;
    bool operator<(const edge &a) const
    {
        return wight > a.wight;
    }
};

// 采用输入图，输出最小生成树的边权和
int main()
{
    int N;
    cout << "please input the number of node:";
    cin >> N;
    int *G = new int[N * N];
    memset(G, 0, sizeof(int) * (N * N));
    char a, b;
    int c;
    cout << "please input the edge and weight(eg A B 6;end with 0 0 0):" << endl;
    while (1)
    {
        cin >> a >> b >> c;
        if (a == '0' && b == '0' && c == 0)
            break;
        G[(a - 'A') * N + (b - 'A')] = c;
        G[(b - 'A') * N + (a - 'A')] = c;
    }
    int *visited = new int[N], sum = 0;
    memset(visited, 0, sizeof(int) * N);
    priority_queue<edge> q;
    for (int i = 0; i < N; i++)
    {
        if (G[0 * N + i] != 0)
        {
            q.push(edge{0, i, G[0 * N + i]});
        }
    }
    visited[0] = 1;
    while (!q.empty())
    {
        edge t = q.top();
        q.pop();
        if (visited[t.u] == 1 && visited[t.v] == 0)
        {
            sum += t.wight;
            visited[t.v] = 1;
            for (int i = 0; i < N; i++)
            {
                if (G[t.v * N + i] != 0 && visited[i] == 0)
                {
                    q.push(edge{t.v, i, G[t.v * N + i]});
                }
            }
        }
        else if (visited[t.u] == 0 && visited[t.v] == 0)
        {
            q.push(t);
        }
        else
            continue;
    }
    cout << "the sum of the minimum spanning tree is:" << sum << endl;
    return 0;
}