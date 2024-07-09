#include <stdio.h>

void MingPick(int left, int k, int turn);
void QiangPick(int left, int k, int turn);

void MingPick(int left, int k, int turn)
{
    if (left >= (turn * k))
    {
        left -= turn * k;
        turn++;
        QiangPick(left, k, turn);
    }
    else
    {
        printf("MING!\n");
        printf("%d", turn);
    }
}

void QiangPick(int left, int k, int turn)
{
    if (left >= (turn * k))
    {
        left -= turn * k;
        turn++;
        MingPick(left, k, turn);
    }
    else
    {
        printf("QIANG!\n");
        printf("%d", turn);
    }
}

int main()
{
    int n, k;
    scanf("%d%d", &n, &k);
    MingPick(n, k, 1);
    return 0;
}