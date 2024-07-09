#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

char check_light(vector<string> &sleft, vector<string> &sright, vector<string> &sjudge)
{
    char p = 0;
    for (p = 'A'; p <= 'L'; p++)
    {
        int flag = 1;
        for (int i = 0; i < sjudge.size(); i++)
        {
            if (sjudge[i] == "even")
            {
                if (find(sleft[i].begin(), sleft[i].end(), p) != sleft[i].end() || find(sright[i].begin(), sright[i].end(), p) != sright[i].end())
                {
                    flag = 0;
                    break;
                }
            }
            else if (sjudge[i] == "up")
            {
                if (find(sright[i].begin(), sright[i].end(), p) == sright[i].end())
                {
                    flag = 0;
                    break;
                }
            }
            else if (sjudge[i] == "down")
            {
                if (find(sleft[i].begin(), sleft[i].end(), p) == sleft[i].end())
                {
                    flag = 0;
                    break;
                }
            }
            if (flag == 0)
                break;
        }
        if (flag == 1)
            return p;
    }
    return '\0';
}

char check_heavy(vector<string> &sleft, vector<string> &sright, vector<string> &sjudge)
{
    char p = 0;
    for (p = 'A'; p <= 'L'; p++)
    {
        int flag = 1;
        for (int i = 0; i < sjudge.size(); i++)
        {
            if (sjudge[i] == "even")
            {
                if ((find(sleft[i].begin(), sleft[i].end(), p) != sleft[i].end()) || (find(sright[i].begin(), sright[i].end(), p) != sright[i].end()))
                {
                    flag = 0;
                    break;
                }
            }
            else if (sjudge[i] == "down")
            {
                if (find(sright[i].begin(), sright[i].end(), p) == sright[i].end())
                {
                    flag = 0;
                    break;
                }
            }
            else if (sjudge[i] == "up")
            {
                if (find(sleft[i].begin(), sleft[i].end(), p) == sleft[i].end())
                {
                    flag = 0;
                    break;
                }
            }
            if (flag == 0)
                break;
        }
        if (flag == 1)
            return p;
    }
    return '\0';
}

int main()
{
    int T = 0;
    cin >> T;
    for (int t = 0; t < T; t++)
    {
        char coin = 0;
        vector<string> sleft, sright, sjudge;
        for (int i = 0; i < 3; i++)
        {
            string s1, s2, s3;
            cin >> s1 >> s2 >> s3;
            sleft.push_back(s1);
            sright.push_back(s2);
            sjudge.push_back(s3);
        }
        coin = check_light(sleft, sright, sjudge);
        if (coin)
            cout << coin << " is the counterfeit coin and it is light. " << endl;
        coin = check_heavy(sleft, sright, sjudge);
        if (coin)
            cout << coin << " is the counterfeit coin and it is heavy. " << endl;
    }
    return 0;
}