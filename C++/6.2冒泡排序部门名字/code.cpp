#include <iostream>
#include <algorithm>
#include <cstring>
#include <random>
using namespace std;

void maopao_sort(char a[][25], int n)
{
    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = 0; j < n - i - 1; ++j)
        {
            if (strcmp(a[j], a[j + 1]) > 0)
                swap(a[j], a[j + 1]);
        }
    }
}

int main()
{
    char a[20][25] = {
        "人力资源部",
        "财务部",
        "市场部",
        "销售部",
        "研发部",
        "生产部",
        "质量管理部",
        "客户服务部",
        "信息技术部",
        "法务部",
        "公共关系部",
        "采购部",
        "战略规划部",
        "企业培训部",
        "健康与安全部"};
    int n = 15;

    cout << "排序前：" << endl;
    for (int i = 0; i < n; ++i)
        cout << a[i] << endl;

    maopao_sort(a, n);

    cout << endl
         << "排序后：" << endl;
    for (int i = 0; i < n; ++i)
        cout << a[i] << endl;

    cout << endl;
    system("pause");
    return 0;
}