#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long LL;

LL merge_sort(int values[], int result[], int low, int high)
{
    if (low >= high)
        return 0;
    int mid = low + high >> 1;
    LL res = merge_sort(values, result, low, mid) + merge_sort(values, result, mid + 1, high);
    int k = 0, i = low, j = mid + 1;
    while (i <= mid && j <= high)
        if (values[i] <= values[j])
            result[k++] = values[i++];
        else
        {
            result[k++] = values[j++];
            res += mid - i + 1;
        }
    while (i <= mid)
        result[k++] = values[i++];
    while (j <= high)
        result[k++] = values[j++];
    for (i = low, j = 0; i <= high; i++, j++)
        values[i] = result[j];
    return res;
}

int main()
{
    int N = 0;
    scanf("%d", &N);
    int values[N], results[N];
    for (int i = 0; i < N; i++)
        scanf("%d", &values[i]);
    cout << merge_sort(values, results, 0, N - 1);
}