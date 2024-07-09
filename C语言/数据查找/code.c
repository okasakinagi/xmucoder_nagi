#include <stdio.h>

struct huo
{
    int num;
    int rest;
    int price;
    int v
};

void pr(struct huo *p)
{
    printf("%d %d %d %d\n", p->num, p->rest, p->price, p->v);
}

int main()
{
    int N = 0;
    scanf("%d", &N);
    struct huo a[N];
    for (int n = 0; n < N; n++)
    {
        scanf("%d %d %d %d", &a[n].num, &a[n].rest, &a[n].price, &a[n].v);
    }
    int b = 0, c = 0, count = 0;
    scanf("%d %d", &b, &c);
    for (int i = 0; i < N; i++)
    {
        switch (b)
        {
        case 1:
        {
            if (a[i].rest >= c)
            {
                count++;
                pr(&a[i]);
            }
            break;
        }
        case 2:
        {
            if (a[i].price >= c)
            {
                count++;
                pr(&a[i]);
            }
            break;
        }
        case 3:
        {
            if (a[i].v >= c)
            {
                count++;
                pr(&a[i]);
            }
            break;
        }
        }
    }
    if (count == 0)
        printf("nothing");
    return 0;
}