#include <iostream>
#include <algorithm>
#include <cstring>
#include <random>
#define RED 0
#define WHITE 1
#define BLUE 2
using namespace std;

void jishu_sort(int a[], int n)
{
    int Min = 0xffff, Max = 0;
    for (int i = 0; i < n; i++) // 考虑数据特殊性，此步甚至可省略，但考虑复用性未省
    {
        if (a[i] > Max)

            Max = a[i];

        if (a[i] < Min)

            Min = a[i];
    }
    int *s = new int[Max - Min + 1];
    memset(s, 0, sizeof(int) * (Max - Min + 1));
    for (int i = 0; i < Max - Min + 1; i++)
        for (int j = 0; j < n; j++)
            if (a[j] == i + Min)
                s[i]++;
    for (int i = 0, j = 0; i < Max - Min + 1; i++)
    {
        while (s[i] > 0)
        {
            a[j++] = i + Min;
            s[i]--;
        }
    }
}

int main()
{
    int a[20], n = 20;

    mt19937 generate; // 随机生成20个颜色数据
    uniform_int_distribution<int> distribution(0, 2);

    for (int i = 0; i < n; i++)
    {
        a[i] = distribution(generate);
    }

    cout << "排序前：";
    for (int i = 0; i < n; i++)
    {
        if (a[i] == RED)
            cout << "R";
        else if (a[i] == WHITE)
            cout << "W";
        else
            cout << "B";
    }

    jishu_sort(a, n);

    cout << endl
         << "排序后：";
    for (int i = 0; i < n; i++)
    {
        if (a[i] == RED)
            cout << "R";
        else if (a[i] == WHITE)
            cout << "W";
        else
            cout << "B";
    }
    cout << endl;
    system("pause");
    return 0;
}