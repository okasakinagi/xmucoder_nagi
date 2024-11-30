// 看错题后错误写下的可执行代码，原题为4.2图的邻接表和k长路径的存在
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
    int *w = new int[N], *visited = new int[N], *last_node = new int[N], index = a - 'A';
    memset(visited, 0, sizeof(int) * N);
    memset(last_node, -1, sizeof(int) * N);
    memset(w, 127, sizeof(int) * N);
    graph_node *p = &(G.list[index]);
    pair<int, int> next = {0xffff, 0xffff};
    visited[index] = 1;
    while (p != NULL)
    {
        w[p->data] = p->wight;
        if (next.first > w[p->data] && !visited[p->data])
        {
            last_node[p->data] = index;
            next.first = w[p->data];
            next.second = p->data;
        }
        p = p->next;
    }
    for (int i = 0; i < N - 1; i++)
    {
        index = next.second;
        p = &(G.list[index]);
        visited[index] = 1;
        while (p != NULL)
        {
            if (!visited[p->data] && (w[p->data] > (w[index] + p->wight)))
            {
                w[p->data] = w[index] + p->wight;
                last_node[p->data] = index;
            }
            p = p->next;
        }
        next.first = 0xffff;
        for (int i = 0; i < N; i++)
            if (w[i] < next.first && !visited[i])
            {
                next.first = w[i];
                next.second = i;
            }
    }
    stack<int> out;
    int temp = last_node[b - 'A'];
    while (temp != -1)
    {
        out.push(temp);
        temp = last_node[temp];
    }
    cout << "the min weight is:" << w[b - 'A'] << endl;
    cout << "the path is:";
    while (!out.empty())
    {
        cout << G.v[out.top()] << "->";
        out.pop();
    }
    cout << G.v[b - 'A'] << endl;
    return 0;
}