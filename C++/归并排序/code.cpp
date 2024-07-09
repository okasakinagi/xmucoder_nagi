#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

void merge_sort(int values[], int result[], int low, int high)
{
    if (low >= high)
        return;
    int mid = high + low >> 1;
    merge_sort(values, result, low, mid);
    merge_sort(values, result, mid + 1, high);
    int i = low, j = mid + 1;
    int time = 0;
    while (i <= mid && j <= high)

        result[time++] = values[i] <= values[j] ? values[i++] : values[j++];

    while (i <= mid)
        result[time++] = values[i++];
    while (j <= high)
        result[time++] = values[j++];
    for (int i = low, j = 0; i <= high; i++, j++)
        values[i] = result[j];
}

int main()
{
    int N = 0;
    scanf("%d", &N);
    int values[N], result[N];
    for (int i = 0; i < N; i++)
        scanf("%d", &values[i]);
    merge_sort(values, result, 0, N - 1);
    for (int i = 0; i < N; i++)
        printf("%d ", values[i]);
}