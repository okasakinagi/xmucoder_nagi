#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

string moves[9] = {"ABDE", "ABC", "BCEF", "ADG", "BDEFH", "CFI", "DEGH", "GHI", "EFHI"};
vector<int> move_time(9);
vector<int> output_time;
vector<int> stdan;
int out_time = 10000;

void move_n(int n, vector<int> &clocks)
{
    if (n >= 9)
    {
        vector<int> clocks_copy(clocks);
        int time = 0;
        for (int i = 0; i < 9; i++)
        {
            if (move_time[i] >= 1)
            {
                for (int k = 0; k < moves[i].size(); k++)
                {
                    clocks_copy[moves[i][k] - 'A'] = (clocks_copy[moves[i][k] - 'A'] + move_time[i]) % 4;
                    time += move_time[i];
                }
            }
        }
        if (clocks_copy == stdan)
        {
            if (out_time >= time)
            {
                out_time = time;
                output_time = move_time;
            }
        }
        return;
    }
    else
    {
        for (int i = 0; i < 4; i++)
        {
            move_time[n] = i;
            move_n(n + 1, clocks);
        }
        return;
    }
}

int main()
{
    vector<int> clocks;
    int temp = 0;
    for (int i = 0; i < 9; i++)
    {
        cin >> temp;
        clocks.push_back(temp);
        stdan.push_back(0);
    }
    move_n(0, clocks);
    for (int i = 0; i < output_time.size(); i++)
    {
        if (output_time[i] >= 1)
            for (int j = 0; j < output_time[i]; j++)
                cout << i + 1 << ' ';
    }
    return 0;
}