#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;

typedef pair<char, char> pcc;
typedef vector<pcc> vpcc;

struct graph_node
{
    int data;
    graph_node *next;
};

struct graph
{
    string v;
    vpcc vr;
    vector<graph_node> list;
};

void CreateGraph(graph &G, char *V, vpcc VR)
{
    G.v = string(V);
    G.vr = VR;
    for (int i = 0; i < strlen(V); i++)
    {
        graph_node *p = new graph_node, *head = p;
        p->data = i;
        for (int j = 0; j < VR.size(); j++)
        {
            if (VR[j].first == V[i])
            {
                graph_node *temp = new graph_node;
                temp->data = G.v.find(VR[j].second);
                p->next = temp;
                p = p->next;
            }
            else if (VR[j].second == V[i])
            {
                graph_node *temp = new graph_node;
                temp->data = G.v.find(VR[j].first);
                p->next = temp;
                p = p->next;
            }
        }
        p->next = NULL;
        G.list.push_back(*head);
    }
}

void DestroyGraph(graph &G)
{
    G.v.clear();
    G.vr.clear();
    for (int i = 0; i < G.list.size(); i++)
    {
        graph_node *p = &G.list[i];
        p = p->next;
        while (p != NULL)
        {
            graph_node *temp = p;
            p = p->next;
            delete temp;
        }
    }
    G.list.clear();
}

char LocateVex(graph G, char u)
{
    for (int i = 0; i < G.list.size(); i++)
    {
        if (u == G.v[i])
            return G.v[i];
    }
    return 0;
}

char GetVex(graph G, char v)
{
    return v;
}

bool PutVex(graph &G, char v, char value)
{
    int i = G.v.find(v);
    if (i != string::npos)
    {
        G.v[i] = value;
        return true;
    }
    return false;
}

char FirstAdjVex(graph G, char v)
{
    int i = G.v.find(v);
    if (i != string::npos)
    {
        graph_node *p = &G.list[i];
        if (p->next != NULL)
            return G.v[p->next->data];
        else
            return 0;
    }
    return 0;
}

char NextAdjVex(graph G, char v, char w)
{
    int i = G.v.find(v), j = G.v.find(w);
    if (i != string::npos && j != string::npos)
    {
        graph_node *p = &G.list[i];
        while (p->next != NULL && p->next->data != j)
            p = p->next;
        if (p->next != NULL)
            return G.v[p->next->data];
        else
            return 0;
    }
    return 0;
}

void InsertVex(graph &G, char v)
{
    G.v.push_back(v);
    graph_node *node = new graph_node;
    node->data = G.v.find(v);
    node->next = NULL;
    G.list.push_back(*node);
}

bool DeleteVex(graph &G, char v)
{
    int i = G.v.find(v);
    if (i == string::npos)
        return false;
    G.v.erase(i, 1);
    graph_node *p = &G.list[i];
    p = p->next;
    while (p->next != NULL)
    {
        graph_node *temp = p;
        p = p->next;
        delete temp;
    }
    G.list.erase(remove_if(G.list.begin(), G.list.end(), [i](graph_node &x)
                           { return x.data == i; }),
                 G.list.end());

    return true;
}
bool InsertArc(graph &G, char v, char w)
{
    int i = G.v.find(v), j = G.v.find(w);
    if (i == string::npos)
        return false;
    graph_node *p = &G.list[i];
    while (p->next != NULL && p->next->data != j)
        p = p->next;
    if (p->next == NULL)
    {
        graph_node *temp = new graph_node;
        temp->data = j;
        temp->next = NULL;
        p->next = temp;
    }
    return true;
}

bool DeleteArc(graph &G, char v, char w)
{
    int i = G.v.find(v), j = G.v.find(w);
    if (i == string::npos)
        return false;
    graph_node *p = &G.list[i];
    while (p->next != NULL && p->next->data != j)
        p = p->next;
    if (p->next != NULL)
    {
        graph_node *q = p->next;
        p->next = q->next;
    }
    p = &G.list[j];
    while (p->next != NULL && p->next->data != i)
        p = p->next;
    if (p->next != NULL)
    {
        graph_node *q = p->next;
        p->next = q->next;
    }
    return true;
}

int display(char v)
{
    cout << v;
    return 0;
}

void DFSTraverse(graph G, int (*Visit)(char v), char v = 0, int *visited = NULL)
{
    if (visited == NULL)
    {
        visited = new int[G.v.size()];
        memset(visited, 0, sizeof(int) * G.v.size());
    }
    if (v == 0)
    {
        for (int i = 0; i < G.v.size(); i++)
        {
            if (visited[i] == 0)
                DFSTraverse(G, Visit, G.v[i], visited);
        }
        delete[] visited;
    }
    else
    {
        Visit(v);
        visited[G.v.find(v)] = 1;
        graph_node *p = &G.list[G.v.find(v)];
        while (p->next != NULL)
        {
            if (!visited[p->next->data])
                DFSTraverse(G, Visit, G.v[p->next->data], visited);
            p = p->next;
        }
    }
}

void BFSTraverse(graph G, int (*Visit)(char v))
{
    int *visited = new int[G.v.size()];
    memset(visited, 0, sizeof(int) * G.v.size());
    queue<char> q;
    q.push(G.v[0]);
    while (!q.empty())
    {
        char v = q.front();
        q.pop();
        if (!visited[G.v.find(v)])
        {
            Visit(v);
            visited[G.v.find(v)] = 1;
            graph_node *p = &G.list[G.v.find(v)];
            while (p->next != NULL)
            {
                if (!visited[p->next->data])
                    q.push(G.v[p->next->data]);
                p = p->next;
            }
        }
    }
    delete[] visited;
}

int main()
{
    char V[] = "ABCDEF";
    vpcc VR = {pcc('A', 'B'), pcc('A', 'C'), pcc('B', 'D'),
               pcc('B', 'E'), pcc('C', 'F'), pcc('E', 'F')};
    graph G;
    CreateGraph(G, V, VR);

    cout << "深度优先遍历结果: ";
    DFSTraverse(G, display);
    cout << endl;

    cout << "广度优先遍历结果: ";
    BFSTraverse(G, display);
    cout << endl;

    InsertVex(G, 'G');
    InsertArc(G, 'A', 'G');
    cout << "插入顶点G和边AG后的深度优先遍历结果: ";
    DFSTraverse(G, display);
    cout << endl;

    DeleteVex(G, 'B');
    cout << "删除顶点B后的广度优先遍历结果: ";
    BFSTraverse(G, display);
    cout << endl;

    DestroyGraph(G);
    return 0;
}