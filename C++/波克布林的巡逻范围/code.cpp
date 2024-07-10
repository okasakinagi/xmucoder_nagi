#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    int K, M, N, count = 0;
    cin >> K >> M >> N;
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if ((i / 10 + j / 10 + i % 10 + j % 10) <= K)
                count++;
        }
    }
    cout << count << endl;
    return 0;
}