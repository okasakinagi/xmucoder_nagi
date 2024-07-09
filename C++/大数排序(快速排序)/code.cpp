#include <iostream>
#include <cstdio>
using namespace std;

inline void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

void quick_sort(int values[], int low, int high)
{
    if (low >= high)
        return;
    int a = low - 1, b = high + 1, temp = values[low + high >> 1];
    while (a < b)
    {
        do
            a++;
        while (values[a] < temp);

        do
            b--;
        while (values[b] > temp);
        if (a < b)
            swap(&values[a], &values[b]);
    }
    quick_sort(values, low, b);
    quick_sort(values, b + 1, high);
}

int main()
{
    int N = 0;
    scanf("%d", &N);
    int values[N];
    for (int i = 0; i < N; i++)
        scanf("%d", &values[i]);
    quick_sort(values, 0, N - 1);
    for (int i = 0; i < N; i++)
        printf("%d ", values[i]);
    return 0;
}