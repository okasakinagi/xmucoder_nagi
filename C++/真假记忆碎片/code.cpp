#include <string>
#include <iostream>
using namespace std;

string stdan[9] = {"530070000", "600195000", "098000060", "800060003", "400803001", "700020006", "060000280", "000419005", "000080079"};
string getin[9];

inline bool putin(bool x[], char ch)
{
    if (x[ch - '0' - 1])
        return false;
    else
    {
        x[ch - '0' - 1] = true;
        return true;
    }
}

bool check()
{
    for (int i = 0; i < 9; i++)
    {
        if (getin[i].size() != 9)
            return false;
        bool found[9] = {0};
        for (int j = 0; j < 9; j++)
        {
            if (getin[i][j] != stdan[i][j] && stdan[i][j] != '0')
                return false;
            else if (getin[i][j] == stdan[i][j])
            {
                if (!putin(found, stdan[i][j]))
                    return false;
                continue;
            }
            else
            {
                if (!putin(found, getin[i][j]))
                    return false;
            }
        }
    }
    return true;
}