#include <string>
#include <iostream>
using namespace std;

string getin[9];

void print(string str[])
{
    for (int i = 0; i < 9; ++i)
    {
        for (int j = 0; j < 9; ++j)
            cout << str[i][j];
        cout << endl;
    }
}

bool search(int x, int y)
{
    if (x > 8)
        return true;
    if (getin[x][y] != '0')
    {
        if (y >= 8)
        {
            if (search(x + 1, 0))
                return true;
            return false;
        }
        else
        {
            if (search(x, y + 1))
                return true;
            return false;
        }
    }
    for (int i = 1; i <= 9; i++)
    {
        char temp = '0' + i;
        int flag = 0;
        if (getin[x].find(temp) != string::npos)
            continue;
        for (int j = 0; j < 9; j++)
            if (i == getin[j][y] - '0')
            {
                flag = 1;
                break;
            }
        if (flag)
            continue;
        for (int j = x - x % 3; j < x + 3 - x % 3; j++)
        {
            for (int k = y - y % 3; k < y + 3 - y % 3; k++)
            {
                if (i == getin[j][k] - '0')
                {
                    flag = 1;
                    break;
                }
            }
            if (flag)
                break;
        }
        if (flag)
            continue;
        getin[x][y] = i + '0';
        if (y >= 8)
        {
            if (search(x + 1, 0))
                return true;
        }
        else
        {
            if (search(x, y + 1))
                return true;
        }
        getin[x][y] = '0';
    }
    return false;
}

int main()
{
    for (int i = 0; i < 9; i++)
        cin >> getin[i];
    search(0, 0);
    print(getin);
    return 0;
}