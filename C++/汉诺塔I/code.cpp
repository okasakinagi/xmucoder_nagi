#include <iostream>
using namespace std;

void move(int N, char x, char y, char z)
{
    if (N == 1)
    {
        cout << x << "->" << y << endl;
        return;
    }
    else
    {
        move(N - 1, x, z, y);
        cout << x << "->" << y << endl;
        move(N - 1, z, y, x);
    }
}

int main()
{
    int N = 0, a[3] = {0};
    cin >> N;
    a[0] = N;
    move(N, 'A', 'C', 'B');
    return 0;
}