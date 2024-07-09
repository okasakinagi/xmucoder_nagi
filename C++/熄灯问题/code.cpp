#include <iostream>
#include <bitset>
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

inline void press_botton(vector<bitset<6>> &light, int i, int j)
{
    light[i][j].flip();
    if (i <= 3)
        light[i + 1][j].flip();
    if (i >= 1)
        light[i - 1][j].flip();
    if (j <= 4)
        light[i][j + 1].flip();
    if (j >= 1)
        light[i][j - 1].flip();
}

vector<bitset<6>> deal(vector<bitset<6>> &light, vector<bitset<6>> press)
{
    int count = 0;
    for (int k = 0; k < 64; k++)
    {
        vector<bitset<6>> light_copy(light), press_copy(press);
        bitset<6> one(k);
        press_copy[0] = one;
        for (int i = 0; i < 6; i++)
            if (one[i])
                press_botton(light_copy, 0, i);
        for (int i = 1; i < 5; i++)
        {
            for (int j = 5; j >= 0; j--)
            {
                if (light_copy[i - 1][j])
                {
                    press_copy[i][j].flip();
                    press_botton(light_copy, i, j);
                }
            }
        }
        bitset<6> zero(0);
        if (light_copy[4] == zero)
            return press_copy;
        else
            continue;
    }
    return press;
}

inline void print_light(vector<bitset<6>> &press)
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 5; j >= 0; j--)
        {
            cout << press[i][j] << " ";
        }
        cout << endl;
    }
}

int main()
{
    int T = 0;
    cin >> T;
    for (int t = 0; t < T; t++)
    {
        string s;
        vector<bitset<6>> light, press;
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 6; j++)
            {
                char temp;
                cin >> temp;
                s.push_back(temp);
            }
            s.push_back('\0');
            bitset<6> temp(s), temp_0;
            s.clear();
            light.push_back(temp);
            temp_0.reset();
            press.push_back(temp_0);
        }
        press = deal(light, press);
        cout << "PUZZLE #" << t + 1 << endl;
        print_light(press);
    }
    return 0;
}