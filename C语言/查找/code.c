#include <stdio.h>

void find_two_largest(int a[], int n, int *largest, int *second_largest)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (a[j] > a[j + 1])
            {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
    *largest = a[n - 1];
    *second_largest = a[n - 2];
    return;
}

int main()
{
    int i, n, arr[100], largest, second_largest;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    find_two_largest(arr, n, &largest, &second_largest);
    printf("%d %d", largest, second_largest);
    return 0;
}