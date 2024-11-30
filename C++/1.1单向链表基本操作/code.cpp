#include <iostream>
#include <algorithm>
using namespace std;

struct Node
{
    int data;
    Node *next;
};

struct LinkList
{
    Node *head;
    Node *tail;
    int size;
};

bool MakeNode(Node *&p, int data)
{
    Node *temp = new Node;
    temp->data = data;
    temp->next = NULL;
    p = temp;
    return true;
}

inline void FreeNode(Node *&p)
{
    delete p;
}

LinkList IninList(LinkList &L)
{
    L.head = L.tail = NULL;
    L.size = 0;
    return L;
}

void DestroyList(LinkList &L)
{
    Node *p = L.head;
    while (p != NULL)
    {
        L.head = p->next;
        FreeNode(p);
        p = L.head;
    }
}

LinkList ClearList(LinkList &L)
{
    Node *p = L.head;
    while (p != NULL)
    {
        L.head = p->next;
        FreeNode(p);
        p = L.head;
    }
    IninList(L);
    return L;
}

Node *InsFirst(Node *h, Node *s)
{
    s->next = h;
    return s;
}
Node *DelFirst(Node *h, Node *&q)
{
    q = h;
    h = h->next;
    return h;
}

LinkList Append(LinkList &L, Node *s)
{
    if (L.head == NULL)
        L.head = L.tail = s;
    else
    {
        L.tail->next = s;
        L.tail = s;
    }
    L.size++;
    return L;
}

LinkList Remove(LinkList &L, Node *&q)
{
    if (L.head == L.tail)
        if (L.size == 0)
        {
            q = NULL;
            return L;
        }
        else
        {
            q = L.head;
            return ClearList(L);
        }
    else
    {
        q = L.tail;
        L.tail = L.head;
        while (L.tail->next != q)
            L.tail = L.tail->next;
        L.tail->next = NULL;
        return L;
    }
}
LinkList InsBefore(LinkList &L, Node *&p, Node *s)
{
    if (p == L.head)
    {
        L.head = InsFirst(p, s);
        L.size++;
        return L;
    }
    else
    {
        Node *q = L.head;
        while (q->next != p)
            q = q->next;
        q->next = s;
        s->next = p;
        L.size++;
        p = s;
        return L;
    }
}

LinkList InsAfter(LinkList &L, Node *&p, Node *s)
{
    if (p == L.tail)
        return Append(L, s);
    else
    {
        s->next = p->next;
        p->next = s;
        p = s;
        L.size++;
        return L;
    }
}

Node *SetCurElem(Node *p, int data)
{
    p->data = data;
    return p;
}

int GetCurElem(Node *p)
{
    return p->data;
}

bool ListEmpty(LinkList &L)
{
    return L.size == 0;
}

int ListLength(LinkList &L)
{
    return L.size;
}

Node *GetHead(LinkList &L)
{
    return L.head;
}

Node *GetLast(LinkList &L)
{
    return L.tail;
}

Node *PriorPos(const LinkList L, Node *p)
{
    if (p == L.head)
        return NULL;
    else
    {
        Node *q = L.head;
        while (q->next != p)
            q = q->next;
        return q;
    }
}

Node *NextPos(const LinkList L, Node *p)
{
    if (p == L.tail)
        return NULL;
    else
        return p->next;
}

bool LocatePos(const LinkList L, Node *&p, int &i)
{
    Node *q = L.head;
    i = 1;
    while (q != NULL && q != p)
    {
        q = q->next;
        i++;
    }
    if (q == NULL)
    {
        i = -1;
        return false;
    }
    else
        return true;
}

int LocateElem(const LinkList L, int e)
{
    Node *p = L.head;
    int pos = 1;
    while (p != NULL && p->data != e)
    {
        p = p->next;
        pos++;
    }
    if (p == NULL)
        return -1;
    else
        return pos;
}

void ListTraverse(const LinkList L)
{
    Node *p = L.head;
    while (p != NULL)
    {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
}
int main()
{
    LinkList L;
    IninList(L); // 初始化链表

    // 创建节点
    Node *node1, *node2, *node3;
    MakeNode(node1, 1);
    MakeNode(node2, 2);
    MakeNode(node3, 3);

    // 插入节点
    L = Append(L, node1);
    L = Append(L, node2);
    L = Append(L, node3);

    cout << "Initial list: ";
    ListTraverse(L); // 遍历链表并打印

    // 插入节点到链表头部
    Node *newNode;
    MakeNode(newNode, 0);
    L.head = InsFirst(L.head, newNode);
    L.size++; // 由于函数限制，手动更新size

    cout << "After inserting 0 at the beginning: ";
    ListTraverse(L);

    // 删除链表头部节点
    Node *deletedNode;
    L.head = DelFirst(L.head, deletedNode);
    L.size--; // 由于函数限制，手动更新size

    cout << "After deleting the first node: ";
    ListTraverse(L);

    // 在特定位置插入节点
    Node *newNode2;
    MakeNode(newNode2, 1.5);
    L = InsBefore(L, node2, newNode2);

    cout << "After inserting 1.5 before 2: ";
    ListTraverse(L);

    // 删除尾部节点
    L = Remove(L, deletedNode);

    cout << "After removing the last node: ";
    ListTraverse(L);

    // 查找元素位置
    int position = LocateElem(L, 2);
    cout << "Position of 2: " << position << endl;

    // 遍历链表并打印每个节点的数据
    cout << "Traversing the list: ";
    ListTraverse(L);

    // 销毁链表
    DestroyList(L);

    system("pause");
    return 0;
}