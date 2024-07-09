// 此题无确定主函数，仅含有指定填写函数
int lowbit(int n)
{
    return n & -n;
}
int NumberOf1(int n)
{
    int res = 0;
    while (n)
    {
        n -= lowbit(n);
        res += 1;
    }
    return res;
}