#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

void Tree_select_sort(int *a, int n)
{
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n / 2; i++)
        {
            for (int j = k; j < n; j += int(pow(2, i + 1)))
            {
                if (int(j + pow(2, i)) < n && a[j] > a[int(j + pow(2, i))])
                {
                    swap(a[j], a[(int(j + pow(2, i)))]);
                }
            }
        }
}

int main()
{
    int a[13] = {
        3,
        1,
        4,
        1,
        5,
        9,
        2,
        6,
        5,
        6,
        4,
        7,
        8,
    };
    cout << "排序前：";
    for (int i = 0; i < 13; i++)
        cout << a[i] << " ";
    Tree_select_sort(a, 13);
    cout << endl
         << "排序后：";
    for (int i = 0; i < 13; i++)
        cout << a[i] << " ";
    cout << endl;
    system("pause");
    return 0;
}