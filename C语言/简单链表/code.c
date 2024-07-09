#include <stdio.h>
#define LEN sizeof(struct test)

struct test
{
    int data;
    struct test *next;
};

int get()
{
    struct test *head = NULL, *p1, *p2;
    while (1)
    {
        if (head == NULL)
        {
            head = malloc(LEN);
            scanf("%d", &head->data);
            p1 = head;
        }
        else
        {
            p2 = malloc(LEN);
            scanf("%d", &p2->data);
            if (p2->data == 0)
            {
                p1->next = NULL;
                break;
            }
            p1->next = p2;
            p1 = p2;
        }
    }
    return head;
}

int main()
{
    struct test *head = get(), *p = head;
    int count = 0;
    while (p != NULL)
    {
        if (p->data % 2 == 0)
        {
            printf("%d ", p->data);
            count++;
        }
        p = p->next;
    }
    if (count == 0)
        printf("Empty");
    return 0;
}