#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <vector>
using namespace std;

int bisearch(int array[], int n, int key)
{
    if (!array)
        return -1;
    int l = 0, r = n - 1;
    while (l <= r)
    {
        int mid = int((l + r) / 2);
        if (array[mid] == key)
            return mid;
        else if (array[mid] > key)
            r = mid - 1;
        else
            l = mid + 1;
    }
    return -1;
}

int main()
{
    int N = 0;
    cout << "Enter the number of elements in array: ";
    cin >> N;
    int *array = new int[N];
    cout << "please enter the number of elements form the smallest element to the largest: ";
    for (int n = 0; n < N; ++n)
        cin >> array[n];
    int key = 0;
    cout << "Enter the number to be searched: ";
    cin >> key;
    int index = bisearch(array, N, key);
    if (index == -1)
        cout << "The number is not found in the array";
    else
        cout << "The number is found at index: " << index + 1;
    return 0;
}