#include <stdio.h>
#define LEN sizeof(struct test)

struct test
{
    char riqi[11];
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
            scanf("%s", head->riqi);
            p1 = head;
        }
        else
        {
            p2 = malloc(LEN);
            scanf("%s", p2->riqi);
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

void pr(struct test *head, int k)
{
    struct test *p = head;
    int count = 0;
    while (p->next != NULL)
    {
        count++;
        if (count == k)
            break;
        p = p->next;
    }
    if (count == k)
        printf("%s", p->riqi);
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
            if (str(p2, p3) > 0)
            {
                head = re(p1, p2, p3, head);
                struct test *temp = p2;
                p2 = p3;
                p3 = temp;
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
    pr(head, k);
    return 0;
}