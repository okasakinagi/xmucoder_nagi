#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int T = 0;
    cin >> T;
    for (int t = 0; t < T; t++)
    {
        int N = 0;
        cin >> N;
        vector<int> vec;
        for (int i = 0; i < N; i++)
        {
            int temp = 0;
            cin >> temp;
            vec.push_back(temp);
        }
        sort(vec.begin(), vec.end());
        for (int i = 0; i < N - 1; i++)
        {
            cout << vec[i] << ' ';
        }
        cout << vec[N - 1] << endl;
    }
    return 0;
}