#include <easyx.h>
#include <conio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#pragma comment(lib, "MSIMG32.LIB")
using namespace std;

struct node // �ڵ㶨��
{
    int order;
    int x, y;
    wchar_t s[30];
    int active = 0; // int��bool
    node()
    {
        order = x = y = active = 0;
    }
    node(int orderin, int xin, int yin, const wchar_t scopy[])
    {
        order = orderin;
        x = xin;
        y = yin;
        wcscpy_s(s, scopy);
        active = 0;
    }
    bool operator==(node x)
    {
        return this->order == x.order;
    }
};

struct edge // �߶���
{
    int u, v;
    double wight;
    edge()
    {
        u = v = wight = 0;
    }
    edge(int from, int to, double w)
    {
        u = from;
        v = to;
        wight = w;
    }
    bool operator<(const edge& a) const
    {
        return wight > a.wight;
    }
};

void transparentimage3(IMAGE* dstimg, int x, int y, IMAGE* srcimg) // png͸����������
{
    HDC dstDC = GetImageHDC(dstimg);
    HDC srcDC = GetImageHDC(srcimg);
    int w = srcimg->getwidth();
    int h = srcimg->getheight();
    BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
    AlphaBlend(dstDC, x, y, w, h, srcDC, 0, 0, w, h, bf);
}

void delete_node(vector<node>& active_vex, node delete_vex) // ����ڵ�ɾ��
{
    active_vex.erase(remove(active_vex.begin(), active_vex.end(), delete_vex), active_vex.end());
}

void clear_or_init(const vector<node> vex, int n) // ���ƻ��ػ溯��
{
    IMAGE background;
    loadimage(&background, _T("picture\\map.jpg"), 1280, 720);
    putimage(0, 0, &background);

    setfillcolor(BLUE); // ������ɫ
    setlinecolor(BLUE);
    setbkmode(TRANSPARENT); // ͸�����ֱ���
    settextcolor(WHITE);    // ������ɫ
    settextstyle(20, 0, _T("����"));

    for (int i = 0; i < n; i++)
    {
        fillcircle(vex[i].x, vex[i].y, 15);
        outtextxy(vex[i].x - 35, vex[i].y + 20, vex[i].s);
    }

    outtextxy(1080, 0, L"�� ESC ���˳�����");
    outtextxy(0, 0, L"��ֱ�ӵ����Ҫȥ����;���ľ��㣬�����Զ�����·��");
}

void change_vexcolor(vector<node> active_vex) // ���ļ���ڵ㺯��
{
    setfillcolor(RED);
    setlinecolor(RED);
    for (int i = 0; i < active_vex.size(); i++)
    {
        fillcircle(active_vex[i].x, active_vex[i].y, 15);
    }
}

void put_route(int from, int to) // ����·��
{
    IMAGE route;
    wchar_t s[30];
    if (from > to) // ����·����������˳�򲢹����ļ���
        swap(from, to);
    swprintf(s, 30, _T("picture\\route\\%d-%d.png"), from, to);
    loadimage(&route, s, 1280, 720);
    transparentimage3(NULL, 0, 0, &route);
}

inline double distance(node from, node to) // ������������Ϊ��ͼ�бߵ�Ȩ��
{
    return (sqrt((from.x - to.x) * (from.x - to.x) + (from.y - to.y) * (from.y - to.y)));
}

void prim(vector<node> active_vex) // prim��С����·��
{
    int n = active_vex.size();
    double* G = new double[n * n];
    memset(G, 0, sizeof(int) * (n * n));
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
        {
            double wight = distance(active_vex[i], active_vex[j]);
            G[(i)*n + (j)] = wight;
            G[(j)*n + (i)] = wight;
        }
    int* visited = new int[n];
    memset(visited, 0, sizeof(int) * n);
    priority_queue<edge> q;
    for (int i = 0; i < n; i++)
    {
        if (!fabs(G[0 * n + i]) <= 1e-4)
        {
            q.push(edge(0, i, G[0 * n + i]));
        }
    }
    visited[0] = 1;
    while (!q.empty())
    {
        edge t = q.top();
        q.pop();
        if (visited[t.u] == 1 && visited[t.v] == 0)
        {
            put_route(active_vex[t.u].order, active_vex[t.v].order);
            visited[t.v] = 1;
            for (int i = 0; i < n; i++)
                if (!fabs(G[t.v * n + i]) <= 1e-4 && visited[i] == 0)
                    q.push(edge(t.v, i, G[t.v * n + i]));
        }
        else if (visited[t.u] == 0 && visited[t.v] == 0)
        {
            q.push(t);
        }
        else
            continue;
    }
}

int main()
{
    initgraph(1280, 720, EX_NOCLOSE); // ���ڳ�ʼ����λ�õ���
    HWND hwnd = GetHWnd();
    MoveWindow(hwnd, 100, 100, 1280, 720, TRUE);

    vector<node> vex = {
        node(0, 150, 540, _T("��ϢѧԺ")),
        node(1, 240, 250, _T("�����˶���")),
        node(2, 255, 335, _T("��ͥʳ��")),
        node(3, 315, 95, _T("����ѧ����Ԣ")),
        node(4, 595, 115, _T("˼Դ����")),
        node(5, 720, 485, _T("����ͼ���")),
        node(6, 670, 165, _T("����������")),
        node(7, 755, 145, _T("��Ӿ��")),
        node(8, 1125, 270, _T("һ���˶���")),
        node(9, 1055, 165, _T("����ʳ��")) };
    int n = 10;
    clear_or_init(vex, n);

    ExMessage m;             // ������Ϣ����
    vector<node> active_vex; // ���屻����Ļ��

    while (true)
    {
        // ��ȡһ�����򰴼���Ϣ
        m = getmessage(EX_MOUSE | EX_KEY);
        switch (m.message)
        {

        case WM_LBUTTONDOWN: // �������
        {
            int flag = -1;
            for (int i = 0; i < 10; i++)
                if (abs(m.x - vex[i].x) <= 15 && abs(m.y - vex[i].y) <= 15)
                {
                    flag = vex[i].order;
                    break;
                }
            if (flag != -1)
            {
                cleardevice(); // �ػ棬����ѡ�����������ƿ�������
                clear_or_init(vex, n);
                if (vex[flag].active == 0)
                {
                    vex[flag].active = 1;
                    active_vex.push_back(vex[flag]);
                }
                else
                {
                    vex[flag].active = 0;
                    delete_node(active_vex, vex[flag]);
                }
                change_vexcolor(active_vex); // ����ѡ�е���ɫ
                prim(active_vex);
            }
            else
            {
                continue;
            }
        }
        case WM_KEYDOWN: // �� ESC ���˳�����,��ΪΨһ����
            if (m.vkcode == VK_ESCAPE)
            {
                closegraph();
                return 0;
            }
        }
    }
}