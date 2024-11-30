#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

struct Node
{
    int data;
    Node *Lchild, *Rchild;
    Node() : data(0), Lchild(NULL), Rchild(NULL) {}
    Node(int data) : data(data), Lchild(NULL), Rchild(NULL) {}
};

struct compare
{
    bool operator()(const Node *a, const Node *b)
    {
        return a->data > b->data;
    }
};

void visit(int n, int *save, Node *root)
{
    if (root == NULL)
        return;
    if (root->Lchild == NULL && root->Rchild == NULL)
    {
        cout << root->data << ": ";
        for (int i = 0; i < n; i++)
            cout << save[i];
        cout << endl;
    }
    if (root->Lchild != NULL)
    {
        save[n] = 0;
        visit(n + 1, save, root->Lchild);
    }
    if (root->Rchild != NULL)
    {
        save[n] = 1;
        visit(n + 1, save, root->Rchild);
    }
}

int main()
{
    priority_queue<Node *, vector<Node *>, compare> queue;
    cout << "Please give the all number(end with -1):";
    int getin = 0;
    cin >> getin;
    while (getin != -1)
    {
        Node *node = new Node(getin);
        queue.push(node);
        cin >> getin;
    }
    int n = queue.size();
    if (n <= 1)
    {
        cout << "Please input at least two numbers." << endl;
        return 0;
    }
    while (queue.size() > 1)
    {
        Node *nodeL = queue.top();
        queue.pop();
        Node *nodeR = queue.top();
        queue.pop();
        Node *nodep = new Node(nodeL->data + nodeR->data);
        nodep->Lchild = nodeL;
        nodep->Rchild = nodeR;
        queue.push(nodep);
    }
    Node *root = queue.top();
    queue.pop();
    cout << "The code of the each number inputed is:" << endl;
    int *save = new int[n];
    visit(0, save, root);
    return 0;
}