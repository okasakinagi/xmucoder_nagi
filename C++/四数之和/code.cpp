#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int target = 0, N = 0;
    cin >> target >> N;
    vector<int> a;
    for (int i = 0; i < N; i++)
    {
        int temp = 0;
        cin >> temp;
        a.push_back(temp);
    }
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());
    int p1, p2, p3, p4;
    p1 = 0;
    p4 = a.size() - 1;
    for (p1 = 0; p1 < N - 1; p1++)
    {
        for (p4 = N - 1; p4 > p1; p4--)
        {
            p2 = p1 + 1;
            p3 = p4 - 1;
            while (p2 < p3)
            {
                if (a[p1] + a[p2] + a[p3] + a[p4] == target)
                {
                    cout << a[p1] << " " << a[p2] << " " << a[p3] << " " << a[p4] << endl;
                    p2++;
                }
                else if (a[p1] + a[p2] + a[p3] + a[p4] > target)
                {
                    p3--;
                }
                else if (a[p1] + a[p2] + a[p3] + a[p4] < target)
                {
                    p2++;
                }
            }
        }
    }
    return 0;
}