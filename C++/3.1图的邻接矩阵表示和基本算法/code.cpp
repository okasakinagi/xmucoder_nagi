#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;

typedef pair<char, char> pcc;
typedef vector<pcc> vpcc;

struct graph
{
    int *start;
    string v;
    vpcc vr;

    graph()
    {
        start = NULL;
        v = string();
        vr = vpcc();
    }
};

void CreateGraph(graph &G, char *V, vpcc VR)
{
    G.v = string(V);
    G.vr = VR;
    G.start = new int[G.v.size() * G.v.size()];
    memset(G.start, 0, G.v.size() * sizeof(int));
    for (int i = 0; i < G.vr.size(); i++)
    {
        G.start[G.v.find(G.vr[i].first) * G.v.size() + G.v.find(G.vr[i].second)] = 1;
        G.start[G.v.find(G.vr[i].second) * G.v.size() + G.v.find(G.vr[i].first)] = 1;
    }
}

void DestroyGraph(graph &G)
{
    delete[] G.start;
    G.v = string();
    G.vr = vpcc();
}

int LocateVex(graph G, char u)
{
    return G.v.find(u);
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
    for (int j = 0; j < G.v.size(); j++)
        if (G.start[i * G.v.size() + j] == 1)
            return G.v[j];
    return 0;
}

char NextAdjVex(graph G, char v, char w)
{
    int i = G.v.find(v);
    for (int j = 0; j < G.v.size(); j++)
        if (G.start[i * G.v.size() + j] == 1 && G.v[j] != w)
            return G.v[j];
    return 0;
}

void InsertVex(graph &G, char v)
{
    G.v.push_back(v);
    int *temp = G.start;
    G.start = new int[G.v.size() * G.v.size()];
    memset(G.start, 0, G.v.size() * sizeof(int));
    for (int i = 0; i < G.v.size() - 1; i++)
        for (int j = 0; j < G.v.size(); j++)
            G.start[i * G.v.size() + j] = temp[i * G.v.size() + j];
    delete[] temp;
}

bool DeleteVex(graph &G, char v)
{
    int i = G.v.find(v);
    if (i != string::npos)
    {
        G.v.erase(i, 1);
        int *temp = G.start;
        G.start = new int[G.v.size() * G.v.size()];
        memset(G.start, 0, G.v.size() * sizeof(int));
        for (int j = 0, nj = 0; j < G.v.size() + 1; j++)
        {
            if (j == i)
                continue;
            for (int k = 0, nk = 0; k < G.v.size() + 1; k++)
            {
                if (k == i)
                    continue;
                G.start[nj * G.v.size() + nk] = temp[j * G.v.size() + k];
                nk++;
            }
            nj++;
        }
        delete[] temp;
        return true;
    }
    return false;
}

void InsertArc(graph &G, char v, char w)
{
    int i = G.v.find(v);
    int j = G.v.find(w);
    if (i != string::npos && j != string::npos)
    {
        G.start[i * G.v.size() + j] = 1;
        G.start[j * G.v.size() + i] = 1;
    }
}

void DeleteArc(graph &G, char v, char w)
{
    int i = G.v.find(v);
    int j = G.v.find(w);
    if (i != string::npos && j != string::npos)
    {
        G.start[i * G.v.size() + j] = 0;
        G.start[j * G.v.size() + i] = 0;
    }
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
        memset(visited, 0, G.v.size() * sizeof(int));
    }
    if (v == 0)
    {
        for (int i = 0; i < G.v.size(); i++)
            if (!visited[i])
                DFSTraverse(G, Visit, G.v[i], visited);
        delete[] visited;
    }
    else
    {
        Visit(v);
        visited[G.v.find(v)] = 1;
        for (int i = 0; i < G.v.size(); i++)
            if (!visited[i] && G.start[G.v.find(v) * G.v.size() + i])
                DFSTraverse(G, Visit, G.v[i], visited);
    }
}

void BFSTraverse(graph G, int (*Visit)(char v))
{
    queue<char> q;
    int *visited = new int[G.v.size()];
    memset(visited, 0, G.v.size() * sizeof(int));
    for (int i = 0; i < G.v.size(); i++)
    {
        if (!visited[i])
        {
            q.push(G.v[i]);
            while (!q.empty())
            {
                char temp = q.front();
                q.pop();
                if (visited[G.v.find(temp)] == 1)
                    continue;
                Visit(temp);
                visited[G.v.find(temp)] = 1;
                for (int j = 0; j < G.v.size(); j++)
                    if (!visited[j] && G.start[G.v.find(temp) * G.v.size() + j])
                        q.push(G.v[j]);
            }
        }
        else
        {
            continue;
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