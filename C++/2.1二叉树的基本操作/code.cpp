#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

struct Node
{
    int data;
    Node *Lchild, *Rchild;
    Node()
    {
        data = 0;
        Lchild = NULL;
        Rchild = NULL;
    }
};

void InitBiTree(Node *&T)
{
    T = NULL;
}

void DestoryBiTree(Node *&T)
{
    Node *p = T;
    if (p != NULL)
    {
        if (p->Lchild != NULL)
        {
            DestoryBiTree(p->Lchild);
        }
        if (p->Rchild != NULL)
        {
            DestoryBiTree(p->Rchild);
        }
        delete p;
        T = NULL;
    }
    else
    {
        return;
    }
}

bool CreateBiTree(Node *&T, int *definition, int n) // 猜测definition是int数组，n是数组长度，并依据根左右的顺序创建二叉树
{
    if (n == 0)
        return false;
    if (T == NULL)
        T = new Node;
    T->data = definition[0];
    CreateBiTree(T->Lchild, definition + 1, (n - 1) / 2);
    CreateBiTree(T->Rchild, definition + (n - 1) / 2 + 1, n - 1 - (n - 1) / 2);
    return true;
}

void ClearBiTree(Node *&T)
{
    if (T != NULL)
    {
        ClearBiTree(T->Lchild);
        ClearBiTree(T->Rchild);
        delete T;
        T = NULL;
    }
}

bool BiTreeEmpty(Node *T)
{
    return T == NULL;
}

int BiTreeDepth(Node *T)
{
    if (T == NULL)
        return 0;
    int L = BiTreeDepth(T->Lchild);
    int R = BiTreeDepth(T->Rchild);
    return max(L, R) + 1;
}

Node *Root(Node *T)
{
    return T;
}

int Value(Node *T, Node *e)
{
    return e->data;
}

bool Assign(Node *T, Node *&e, int value)
{
    if (e == NULL)
        return false;
    e->data = value;
    return true;
}

Node *Parent(Node *T, Node *e)
{
    if (e == NULL)
        return NULL;
    if (e == T)
        return NULL;
    else if ((e == T->Lchild) || (e == T->Rchild))
        return T;
    else
    {
        Node *temp = Parent(T->Lchild, e);
        if (temp != NULL)
            return temp;
        return Parent(T->Rchild, e);
    }
}

Node *LeftChild(Node *T, Node *e)
{
    return e->Lchild;
}

Node *RightChild(Node *T, Node *e)
{
    return e->Rchild;
}

Node *LeftSibling(Node *T, Node *e)
{
    if (e == T || (e == T->Lchild))
        return NULL;
    else if (e == T->Rchild)
        return T->Lchild;
    else
    {
        Node *temp = LeftChild(T->Lchild, e);
        if (temp != NULL)
            return temp;
        else
            return LeftSibling(T->Rchild, e);
    }
}

Node *RightSibling(Node *T, Node *e)
{
    if (e == T || (e == T->Rchild))
        return NULL;
    else if (e == T->Lchild)
        return T->Rchild;
    else
    {
        Node *temp = RightChild(T->Rchild, e);
        if (temp != NULL)
            return temp;
        else
            return RightSibling(T->Lchild, e);
    }
}

bool InsertChild(Node *T, Node *p, int LR, Node *c) // 假定c的左右孩子为空
{
    if (c == NULL)
        return false;
    if (LR == 0)
    {
        if (p->Lchild == NULL)
            p->Lchild = c;
        else
        {
            c->Lchild = p->Lchild;
            p->Lchild = c;
        }
        return true;
    }
    else if (LR == 1)
    {
        if (p->Rchild == NULL)
            p->Rchild = c;
        else
        {
            c->Lchild = p->Rchild;
            p->Rchild = c;
        }
        return true;
    }
    else
        return false;
}

bool DeleteChild(Node *T, Node *p, int LR)
{
    if (LR == 0)
    {
        if (p->Lchild == NULL)
            return false;
        else
        {
            DestoryBiTree(p->Lchild);
            return true;
        }
    }
    else if (LR == 1)
    {
        if (p->Rchild == NULL)
            return false;
        else
        {
            DestoryBiTree(p->Rchild);
            return true;
        }
    }
    else
        return false;
}
int Display(Node *T)
{
    if (T == NULL)
    {
        cout << "NULL ";
        return 0;
    }
    cout << T->data << " ";
    return 0;
}

void PreOrderTraverse(Node *T, int (*vistit)(Node *temp))
{
    if (T != NULL)
    {
        vistit(T);
        PreOrderTraverse(T->Lchild, vistit);
        PreOrderTraverse(T->Rchild, vistit);
    }
    else
        return;
}

void InOrderTraverse(Node *T, int (*vistit)(Node *temp))
{
    if (T != NULL)
    {
        InOrderTraverse(T->Lchild, vistit);
        vistit(T);
        InOrderTraverse(T->Rchild, vistit);
    }
    else
        return;
}

void PostOrderTraverse(Node *T, int (*vistit)(Node *temp))
{
    if (T != NULL)
    {
        PostOrderTraverse(T->Lchild, vistit);
        PostOrderTraverse(T->Rchild, vistit);
        vistit(T);
    }
    else
        return;
}

void LevelOrderTraverse(Node *T, int (*vistit)(Node *temp))
{
    queue<Node *> p;
    p.push(T);
    while (!p.empty())
    {
        Node *temp = p.front();
        p.pop();
        vistit(temp);
        if (temp->Lchild != NULL)
            p.push(temp->Lchild);
        if (temp->Rchild != NULL)
            p.push(temp->Rchild);
    }
}

int main()
{
    Node *root = NULL;
    int definition[] = {1, 2, 4, 5, 3, 6, 7}; // 用于创建二叉树的数组
    int n = sizeof(definition) / sizeof(int); // 数组长度

    // 测试初始化函数
    InitBiTree(root);
    if (BiTreeEmpty(root))
    {
        cout << "BiTree initialized successfully." << endl;
    }

    // 测试创建二叉树函数
    CreateBiTree(root, definition, n);
    cout << "BiTree created with root value: " << root->data << endl;

    // 测试二叉树深度函数
    int depth = BiTreeDepth(root);
    cout << "Depth of the BiTree: " << depth << endl;

    // 测试获取根节点函数
    Node *rootCopy = Root(root);
    cout << "Root of the BiTree: " << rootCopy->data << endl;

    // 测试获取节点值函数
    cout << "Value of the root: " << Value(root, root) << endl;

    // 测试赋值函数
    int newValue = 8;
    Assign(root, root, newValue);
    cout << "New value of the root: " << root->data << endl;

    // 测试获取父节点函数
    Node *parent = Parent(root, LeftChild(root, root));
    cout << "Parent of the left child of the root: ";
    Display(parent);
    cout << endl;

    // 测试获取左/右孩子节点函数
    cout << "Left child of the root: ";
    Display(LeftChild(root, root));
    cout << endl;
    cout << "Right child of the root: ";
    Display(RightChild(root, root));
    cout << endl;

    // 测试获取左/右兄弟节点函数
    cout << "Left sibling of the right child of the root: ";
    Display(LeftSibling(root, RightChild(root, root)));
    cout << endl;
    cout << "Right sibling of the left child of the root: ";
    Display(RightSibling(root, LeftChild(root, root)));
    cout << endl;

    // 测试插入孩子节点函数
    Node *newNode = new Node();
    newNode->data = 9;
    InsertChild(root, LeftChild(root, root), 1, newNode);
    cout << "Inserted new node as right child of left child of root." << endl;

    // 测试删除孩子节点函数
    DeleteChild(root, LeftChild(root, root), 1);
    cout << "Deleted right child of left child of root." << endl;

    // 测试前序、中序、后序和层序遍历函数
    cout << "Pre-order traversal: ";
    PreOrderTraverse(root, Display);
    cout << endl;

    cout << "In-order traversal: ";
    InOrderTraverse(root, Display);
    cout << endl;

    cout << "Post-order traversal: ";
    PostOrderTraverse(root, Display);
    cout << endl;

    cout << "Level-order traversal: ";
    LevelOrderTraverse(root, Display);
    cout << endl;

    // 测试清除二叉树函数
    ClearBiTree(root);
    if (BiTreeEmpty(root))
    {
        cout << "BiTree cleared successfully." << endl;
    }
    return 0;
}