#include <iostream>
using namespace std;

void move(int N, char x, char y, char z, int name[])
{
    if (N == 1)
    {
        cout << name[N - 1] << ':' << x << "->" << y << endl;
        return;
    }
    else
    {
        move(N - 1, x, z, y, name);
        cout << name[N - 1] << ':' << x << "->" << y << endl;
        move(N - 1, z, y, x, name);
    }
}

int main()
{
    int N = 0;
    char a[3] = {0};
    cin >> N >> a[0] >> a[1] >> a[2];
    int name[N];
    for (int i = 1; i <= N; i++)
        name[i - 1] = i;
    move(N, a[0], a[2], a[1], name);
    return 0;
}