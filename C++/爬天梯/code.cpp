#include <iostream>
using namespace std;

int jishu = 0;

void move(int N)
{
    if (N <= 0)
    {
        jishu++;
        return;
    }
    else if (N == 1)
        move(N - 1);
    else
    {
        for (int i = 1; i <= 2; i++)
        {
            move(N - i);
        }
    }
}

int main()
{
    int N = 0;
    cin >> N;
    move(N);
    cout << jishu << endl;
    return 0;
}