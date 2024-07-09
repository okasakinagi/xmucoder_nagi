#include <stdio.h>
#define LEN sizeof(struct test)

struct test
{
    char num[15];
    int chin;
    int math;
    int eng;
    int phy;
    int cha;
    int bio;
    int jishu;
    struct test *next;
};

struct test *get(int i)
{
    int n = 1;
    struct test *head = NULL, *p1, *p2;
    while (i--)
    {
        if (head == NULL)
        {
            head = malloc(LEN);
            scanf("%s %d %d %d %d %d %d", head->num, &head->chin, &head->math, &head->eng, &head->phy, &head->cha, &head->bio);
            head->jishu = n++;
            p1 = head;
        }
        else
        {
            p2 = malloc(LEN);
            scanf("%s %d %d %d %d %d %d", p2->num, &p2->chin, &p2->math, &p2->eng, &p2->phy, &p2->cha, &p2->bio);
            p2->jishu = n++;
            p1->next = p2;
            p1 = p2;
        }
    }
    p1->next = NULL;
    return head;
}

struct test *re(struct test *p1, struct test *p2, struct test *p3, struct test *head)
{
    if (p2 == head)
    {
        p2->next = p3->next;
        p3->next = p2;
        head = p3;
    }
    else
    {
        p1->next = p3;
        p2->next = p3->next;
        p3->next = p2;
    }
    return head;
}

void pr(struct test *head)
{
    struct test *p = head;
    while (p != NULL)
    {
        printf("%d\n", p->jishu);
        p = p->next;
    }
}

int str(char *p1, char *p2)
{
    int count = 0;
    while (*p1 == *p2 && count < 15)
    {
        p1++;
        p2++;
        count++;
    }
    return *p1 - *p2;
}

int main()
{
    int N = 0, k = 0;
    scanf("%d", &N);
    struct test *head = get(N), *p1 = head, *p2 = p1, *p3 = p1->next;
    scanf("%d", &k);
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N - 1 - i; j++)
        {
            switch (k)
            {
            case 1:
            {
                if ((p2->chin < p3->chin) || ((p2->chin == p3->chin) && (str(p2->num, p3->num) > 0)))
                {
                    head = re(p1, p2, p3, head);
                    struct test *temp = p2;
                    p2 = p3;
                    p3 = temp;
                }
                break;
            }
            case 2:
            {
                if ((p2->math < p3->math) || ((p2->math == p3->math) && (str(p2->num, p3->num) > 0)))
                {
                    head = re(p1, p2, p3, head);
                    struct test *temp = p2;
                    p2 = p3;
                    p3 = temp;
                }
                break;
            }
            case 3:
            {
                if ((p2->eng < p3->eng) || ((p2->eng == p3->eng) && (str(p2->num, p3->num) > 0)))
                {
                    head = re(p1, p2, p3, head);
                    struct test *temp = p2;
                    p2 = p3;
                    p3 = temp;
                }
                break;
            }
            case 4:
            {
                if ((p2->phy < p3->phy) || ((p2->phy == p3->phy) && (str(p2->num, p3->num) > 0)))
                {
                    head = re(p1, p2, p3, head);
                    struct test *temp = p2;
                    p2 = p3;
                    p3 = temp;
                }
                break;
            }
            case 5:
            {
                if ((p2->cha < p3->cha) || ((p2->cha == p3->cha) && (str(p2->num, p3->num) > 0)))
                {
                    head = re(p1, p2, p3, head);
                    struct test *temp = p2;
                    p2 = p3;
                    p3 = temp;
                }
                break;
            }
            case 6:
            {
                if ((p2->bio < p3->bio) || ((p2->bio == p3->bio) && (str(p2->num, p3->num) > 0)))
                {
                    head = re(p1, p2, p3, head);
                    struct test *temp = p2;
                    p2 = p3;
                    p3 = temp;
                }
                break;
            }
            }
            if (p2 == head)
                p1 = head;
            else
                p1 = p2;
            p2 = p3;
            p3 = p3->next;
        }
        p1 = p2 = head;
        p3 = p2->next;
    }
    pr(head);
    return 0;
}