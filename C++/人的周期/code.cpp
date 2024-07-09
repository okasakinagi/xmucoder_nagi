#include <iostream>
using namespace std;

int main()
{
    int p = 0, e = 0, i = 0, d = 0;
    cin >> p >> e >> i >> d;
    int count = 1;
    while (p != -1 && e != -1 && i != -1 && d != -1)
    {
        p %= 23, e %= 28, i %= 33;
        int j = d == 0 ? 1 : d;
        for (; j <= 21252; j++)
            if ((j - p) % 23 == 0)
                break;
        for (; j <= 21252; j += 23)
        {
            if ((j - e) % 28 == 0)
                break;
        }
        for (; j <= 21252; j += 23 * 28)
        {
            if ((j - i) % 33 == 0)
                break;
        }
        cout << "Case " << count << ": the next triple peak occurs in " << (j - d) << " days." << endl;
        count++;
        cin >> p >> e >> i >> d;
    }
    return 0;
}