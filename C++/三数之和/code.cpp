#include <iostream>
using namespace std;

int main()
{
    int target = 0, N = 0;
    cin >> target >> N;
    int a[N];
    for (int i = 0; i < N; i++)
        cin >> a[i];
    int *p1, *p2, *p3;
    for (p1 = a; p1 - a < N - 1; p1++)
    {
        p2 = p1 + 1;
        p3 = a + N - 1;
        while (p2 != p3)
        {
            if (*p1 + *p2 + *p3 == target)
            {
                cout << *p1 << " " << *p2 << " " << *p3 << endl;
                p2++;
            }
            else if (*p1 + *p2 + *p3 > target)
            {
                p3--;
            }
            else if (*p1 + *p2 + *p3 < target)
            {
                p2++;
            }
        }
    }
    return 0;
}