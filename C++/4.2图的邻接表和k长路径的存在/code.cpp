#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <vector>
#include <stack>
using namespace std;

struct graph_node
{
    int wight;
    int data;
    graph_node *next;
};

struct graph
{
    string v;
    vector<graph_node> list;
};

bool dfs(graph G, int now, int end, int *visited, int res, int k)
{
    if (now == end)
        if (res == k)
            return true;
        else
            return false;
    visited[now] = 1;
    graph_node *p = &(G.list[now]);
    while (p != NULL)
    {
        if (visited[p->data] == 0)
            if (dfs(G, p->data, end, visited, res + p->wight, k))
                return true;
        p = p->next;
    }
    visited[now] = 0;
    return false;
}

// 采用输入图，输出最小生成树的边权和
int main()
{
    int N;
    cout << "please input the number of node:";
    cin >> N;
    graph G;
    for (int i = 0; i < N; i++)
    {
        G.v.push_back('A' + i);
        graph_node *temp = new graph_node;
        temp->data = i;
        temp->wight = 0;
        temp->next = NULL;
        G.list.push_back(*temp);
    }
    char a, b;
    int c;
    cout << "please input the edge and weight(.eg A B 6;end with 0 0 0):" << endl;
    while (1)
    {
        cin >> a >> b >> c;
        if (a == '0' && b == '0' && c == 0)
            break;
        // A->B
        graph_node *p = &(G.list[a - 'A']);
        while (p->next != NULL)
            p = p->next;
        p->next = new graph_node;
        p->next->data = b - 'A';
        p->next->wight = c;
        p->next->next = NULL;
        // B->A
        p = &(G.list[b - 'A']);
        while (p->next != NULL)
            p = p->next;
        p->next = new graph_node;
        p->next->data = a - 'A';
        p->next->wight = c;
        p->next->next = NULL;
    }
    cout << "please input the start node and termination node(.eg A B):";
    cin >> a >> b;
    int *visited = new int[N], index = a - 'A';
    memset(visited, 0, sizeof(int) * N);
    graph_node *p = &(G.list[index]);
    int k = 0;
    cout << "please input the length of the path:";
    cin >> k;
    if (dfs(G, index, b - 'A', visited, 0, k))
        cout << "there is a path from " << a << " to " << b << " with length " << k << "." << endl;
    else
        cout << "there is no path from " << a << " to " << b << " with length " << k << "." << endl;
    return 0;
}