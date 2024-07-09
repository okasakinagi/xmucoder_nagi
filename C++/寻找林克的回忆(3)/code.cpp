// 相同与前一个回忆
// 枚举所有可能得出分数，输出最大的分数
#include <iostream>
#include <algorithm>
using namespace std;

int ones[1 << 9], map[1 << 9];
int row[9], col[9], cell[3][3];
int getin[9][9];
int max_score = -1;

inline int lowbit(int x)
{
    return x & -x;
}

void init()
{
    for (int i = 0; i < 9; i++)
        row[i] = col[i] = (1 << 9) - 1;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            cell[i][j] = (1 << 9) - 1;
}

inline int get_num(int x, int y)
{
    return row[x] & col[y] & cell[x / 3][y / 3];
}

void dfs(int cnt)
{
    if (!cnt)
    {
        int score = 0;
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++)
            {
                if (i == 0 || i == 8 || j == 0 || j == 8)
                    score += 6 * getin[i][j];
                else if (i == 1 || i == 7 || j == 1 || j == 7)
                    score += 7 * getin[i][j];
                else if (i == 2 || i == 6 || j == 2 || j == 6)
                    score += 8 * getin[i][j];
                else if (i == 3 || i == 5 || j == 3 || j == 5)
                    score += 9 * getin[i][j];
                else if (i == 4 && j == 4)
                    score += 10 * getin[i][j];
            }
        max_score = max(score, max_score);
        return;
    }
    int minv = 10;
    int x = 0, y = 0;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (getin[i][j] == 0)
            {
                int t = ones[get_num(i, j)];
                if (minv > t)
                {
                    minv = t;
                    x = i, y = j;
                }
            }
        }
    }
    for (int i = get_num(x, y); i; i -= lowbit(i))
    {
        int t = map[lowbit(i)];

        row[x] -= 1 << t;
        col[y] -= 1 << t;
        cell[x / 3][y / 3] -= 1 << t;
        getin[x][y] = t + 1;

        dfs(cnt - 1);

        row[x] += 1 << t;
        col[y] += 1 << t;
        cell[x / 3][y / 3] += 1 << t;
        getin[x][y] = 0;
    }
}

int main()
{
    for (int i = 0; i < 9; i++)
        map[1 << i] = i;
    for (int i = 0; i < 1 << 9; i++)
    {
        int s = 0;
        for (int j = i; j; j -= lowbit(j))
            s++;
        ones[i] = s;
    }
    init();
    int cnt = 0;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            int t;
            cin >> t;
            getin[i][j] = t;
            if (t == 0)
                cnt++;
            else
            {
                t--;
                row[i] -= 1 << t;
                col[j] -= 1 << t;
                cell[i / 3][j / 3] -= 1 << t;
            }
        }
    }
    dfs(cnt);
    cout << max_score << endl;
    return 0;
}