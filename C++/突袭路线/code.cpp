// 与厦门的Andy思路全同，仅部分变量和写法不同
#include <cstring>
#include <iostream>
#include <algorithm>
#define MAX 1000005
using namespace std;

int n, m;
int head[MAX], e[MAX], ne[MAX], idx = 0;
int q[MAX], d[MAX] = {0};

void add(int x, int y)
{
    e[idx] = y, ne[idx] = head[x], head[x] = idx++;
}

bool topsort()
{
    int phead = 0, ptail = -1;
    for (int i = 1; i <= n; i++)
        if (!d[i])
            q[++ptail] = i;
    while (phead <= ptail)
    {
        int t = q[phead++];
        for (int i = head[t]; i != -1; i = ne[i])
        {
            int j = e[i];
            d[j]--;
            if (d[j] == 0)
                q[++ptail] = j;
        }
    }
    return ptail == n - 1;
}

int main()
{
    cin >> n >> m;
    memset(head, -1, sizeof(head));
    int x, y;
    for (int i = 0; i < m; i++)
    {
        cin >> x >> y;
        add(x, y);
        d[y]++;
    }
    if (topsort())
        for (int i = 0; i < n; i++)
            printf("%d ", q[i]);
    else
        printf("-1");
    return 0;
}