#include <stdio.h>
#define LEN sizeof(struct test)

struct test
{
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
            head->jishu = n++;
            p1 = head;
        }
        else
        {
            p2 = malloc(LEN);
            p2->jishu = n++;
            p1->next = p2;
            p1 = p2;
        }
    }
    p1->next = head;
    return head;
}

void delete(struct test *p1, struct test *p2)
{
    printf("%d ", p2->jishu);
    p1->next = p2->next;
    free(p2);
}

int main()
{
    int N = 0, M = 0, count = 1;
    scanf("%d %d", &N, &M);
    struct test *head = get(N), *p1 = head, *p2 = head;
    while (p1->next != p1)
    {
        if (count++ == M)
        {
            delete (p1, p2);
            p2 = p1->next;
            count = 1;
        }
        else
        {
            p1 = p2;
            p2 = p2->next;
        }
    }
    printf("%d", p1->jishu);
    return 0;
}