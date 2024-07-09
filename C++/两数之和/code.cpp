#include <iostream>
using namespace std;

int main()
{
    int target = 0, N = 0;
    cin >> target >> N;
    int a[N];
    for (int i = 0; i < N; i++)
        cin >> a[i];
    int *p1, *p2;
    for (p1 = a; p1 - a < N; p1++)
    {
        for (p2 = (p1 + 1); p2 - a < N; p2++)
        {
            if (*p1 + *p2 == target)
                cout << p1 - a << ' ' << p2 - a << endl;
        }
    }
    return 0;
}