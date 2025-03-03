#include <easyx.h>
#include <conio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#pragma comment(lib, "MSIMG32.LIB")
using namespace std;

struct node // 节点定义
{
    int order;
    int x, y;
    wchar_t s[30];
    int active = 0; // int代bool
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

struct edge // 边定义
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

void transparentimage3(IMAGE* dstimg, int x, int y, IMAGE* srcimg) // png透明背景插入
{
    HDC dstDC = GetImageHDC(dstimg);
    HDC srcDC = GetImageHDC(srcimg);
    int w = srcimg->getwidth();
    int h = srcimg->getheight();
    BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
    AlphaBlend(dstDC, x, y, w, h, srcDC, 0, 0, w, h, bf);
}

void delete_node(vector<node>& active_vex, node delete_vex) // 激活节点删除
{
    active_vex.erase(remove(active_vex.begin(), active_vex.end(), delete_vex), active_vex.end());
}

void clear_or_init(const vector<node> vex, int n) // 绘制或重绘函数
{
    IMAGE background;
    loadimage(&background, _T("picture\\map.jpg"), 1280, 720);
    putimage(0, 0, &background);

    setfillcolor(BLUE); // 设置颜色
    setlinecolor(BLUE);
    setbkmode(TRANSPARENT); // 透明文字背景
    settextcolor(WHITE);    // 文字颜色
    settextstyle(20, 0, _T("黑体"));

    for (int i = 0; i < n; i++)
    {
        fillcircle(vex[i].x, vex[i].y, 15);
        outtextxy(vex[i].x - 35, vex[i].y + 20, vex[i].s);
    }

    outtextxy(1080, 0, L"按 ESC 键退出程序");
    outtextxy(0, 0, L"请直接点击想要去往或途径的景点，程序将自动计算路径");
}

void change_vexcolor(vector<node> active_vex) // 更改激活节点函数
{
    setfillcolor(RED);
    setlinecolor(RED);
    for (int i = 0; i < active_vex.size(); i++)
    {
        fillcircle(active_vex[i].x, active_vex[i].y, 15);
    }
}

void put_route(int from, int to) // 放置路径
{
    IMAGE route;
    wchar_t s[30];
    if (from > to) // 根据路径命名调整顺序并构造文件名
        swap(from, to);
    swprintf(s, 30, _T("picture\\route\\%d-%d.png"), from, to);
    loadimage(&route, s, 1280, 720);
    transparentimage3(NULL, 0, 0, &route);
}

inline double distance(node from, node to) // 两点距离计算认为是图中边的权重
{
    return (sqrt((from.x - to.x) * (from.x - to.x) + (from.y - to.y) * (from.y - to.y)));
}

void prim(vector<node> active_vex) // prim最小生成路径
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
    initgraph(1280, 720, EX_NOCLOSE); // 窗口初始化和位置调整
    HWND hwnd = GetHWnd();
    MoveWindow(hwnd, 100, 100, 1280, 720, TRUE);

    vector<node> vex = {
        node(0, 150, 540, _T("信息学院")),
        node(1, 240, 250, _T("二期运动场")),
        node(2, 255, 335, _T("丰庭食堂")),
        node(3, 315, 95, _T("国光学生公寓")),
        node(4, 595, 115, _T("思源餐厅")),
        node(5, 720, 485, _T("德旺图书馆")),
        node(6, 670, 165, _T("爱秋体育馆")),
        node(7, 755, 145, _T("游泳馆")),
        node(8, 1125, 270, _T("一期运动场")),
        node(9, 1055, 165, _T("竟丰食堂")) };
    int n = 10;
    clear_or_init(vex, n);

    ExMessage m;             // 定义消息变量
    vector<node> active_vex; // 定义被点击的活动点

    while (true)
    {
        // 获取一条鼠标或按键消息
        m = getmessage(EX_MOUSE | EX_KEY);
        switch (m.message)
        {

        case WM_LBUTTONDOWN: // 按下左键
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
                cleardevice(); // 重绘，由于选择三方库限制可能闪屏
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
                change_vexcolor(active_vex); // 更改选中点颜色
                prim(active_vex);
            }
            else
            {
                continue;
            }
        }
        case WM_KEYDOWN: // 按 ESC 键退出程序,且为唯一出口
            if (m.vkcode == VK_ESCAPE)
            {
                closegraph();
                return 0;
            }
        }
    }
}