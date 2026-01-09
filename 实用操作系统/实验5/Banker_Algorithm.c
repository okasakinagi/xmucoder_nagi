#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct Resources{
    int sourceA, sourceB, sourceC, sourceD;
    int sourceCount;
    struct Resources* next;
} Resources;

void init_resources(Resources* res , int a, int b, int c, int d) 
{
    res->sourceA = a;
    res->sourceB = b;
    res->sourceC = c;
    res->sourceD = d;
    res->sourceCount = a + b + c + d;
    res->next = NULL;
}

void pr(Resources* res,const char* msg) 
{
    if(res == NULL)
        return;
    if(strcmp(msg, "All Resources") == 0 || strcmp(msg, "Available") == 0)
        printf("Resource Type:\tA\tB\tC\tD\n");
    printf("%s:\t%d\t%d\t%d\t%d\n", msg, res->sourceA, res->sourceB, res->sourceC, res->sourceD);
}

Resources* Make_head(Resources* old_head)//头结点模拟MAX矩阵
{
    Resources* new_head = (Resources*)malloc(sizeof(Resources));
    new_head->next = old_head;
    Resources *p = old_head;
    while (p != NULL) {
        new_head->sourceA += p->sourceA;
        new_head->sourceB += p->sourceB;
        new_head->sourceC += p->sourceC;
        new_head->sourceD += p->sourceD;
        p = p->next;
    }
    new_head->sourceCount = new_head->sourceA + new_head->sourceB + new_head->sourceC + new_head->sourceD;
    return new_head;
}

void fr(Resources* res)
{
    Resources* p = res;
    while (p != NULL) {
        Resources* temp = p;
        p = p->next;
        free(temp);
    }
}

void pr_allocation(Resources* Available,Resources** need,Resources** process,int n)
{
    pr(Available,"Available");
    Resources *allo = (Resources *)malloc(sizeof(Resources));
    init_resources(allo,0,0,0,0);
    for(int i = 0; i < n; i++)
    {
        char proc_name[100];
        sprintf(proc_name, "P%d allocation", i + 1);
        allo->sourceA = process[i]->sourceA - need[i]->sourceA;;
        allo->sourceB = process[i]->sourceB - need[i]->sourceB;;
        allo->sourceC = process[i]->sourceC - need[i]->sourceC;;
        allo->sourceD = process[i]->sourceD - need[i]->sourceD;;
        pr(allo, proc_name);
    }
    free(allo);
}

void got_resources(Resources* need,Resources* p)
{
    need->sourceA -= p->sourceA;
    need->sourceB -= p->sourceB;
    need->sourceC -= p->sourceC;
    need->sourceD -= p->sourceD;
    need->sourceCount = need->sourceA + need->sourceB + need->sourceC + need->sourceD;
}

void return_resources(Resources* need,Resources* p)
{
    need->sourceA += p->sourceA;
    need->sourceB += p->sourceB;
    need->sourceC += p->sourceC;
    need->sourceD += p->sourceD;
    need->sourceCount = need->sourceA + need->sourceB + need->sourceC + need->sourceD;
}

int is_safe(Resources* Available,Resources** need,Resources **Max,int n,int cur,char *order,int *finish)//递归检查安全性
{
    int flag = 0;
    if(finish == NULL)
    {
        flag = 1;
        finish = (int *)malloc(n * sizeof(int));
        for(int i = 0; i < n; i++)
            finish[i] = 0;
    }
    if(cur == n)
        return 1;
    for(int i = 0; i < n; i++)
    {
        if(finish[i]==0 && need[i]->sourceA <= Available->sourceA && need[i]->sourceB <= Available->sourceB &&
           need[i]->sourceC <= Available->sourceC && need[i]->sourceD <= Available->sourceD)
        {
            //可以分配资源，则该进程完成，释放全部资源
            got_resources(Available,need[i]);
            return_resources(Available,Max[i]);
            finish[i] = 1;
            //递归检查下一个进程
            if(is_safe(Available,need,Max,n,cur + 1,order,finish))
            {
                order[cur] = '1' + i;
                got_resources(Available,Max[i]);//假想释放回滚
                return_resources(Available,need[i]);//假想分配回滚
                if(flag == 1)
                    free(finish);//创建者释放finish数组
                return 1;
            }
            finish[i] = 0;
            //回滚资源分配
            got_resources(Available,Max[i]);
            return_resources(Available,need[i]);
        }
    }
    if(flag == 1)
        free(finish);//创建者释放finish数组
    return 0;//无安全序列
}

int handle_request(Resources* Available, Resources* Request,Resources **need,Resources **Max,int proc_id,int n,char *order)
{
    //资源请求判断和假设分配
    if(Request->sourceA > Available->sourceA || Request->sourceB > Available->sourceB ||
       Request->sourceC > Available->sourceC || Request->sourceD > Available->sourceD)
    {
        return 0;//资源请求超过可用资源，拒绝请求
    }
    got_resources(Available,Request);//假设分配资源
    got_resources(need[proc_id],Request);
    //安全性检查
    if(is_safe(Available,need,Max,n,0,order,NULL))
    {
        return 1;//请求被批准
    }
    else
    {
        //回滚资源分配
        return_resources(Available,Request);
        return_resources(need[proc_id],Request);
        return 0;//请求被拒绝
    }

}


int main() {
    //资源总量设定
    Resources *AllResources = (Resources *)malloc(sizeof(Resources));
    init_resources(AllResources, 10, 5, 7, 8);

    //可用资源链表
    Resources *AvailableResources = (Resources *)malloc(sizeof(Resources));
    init_resources(AvailableResources, 10, 5, 7, 8);

    int n=4; //进程数量
    Resources* P_Resources[n];

    //进程P1请求资源列表,链表模拟3次请求
    P_Resources[0] = (Resources *)malloc(sizeof(Resources));
    init_resources(P_Resources[0], 3, 1, 5, 2);
    P_Resources[0]->next = (Resources *)malloc(sizeof(Resources));
    init_resources(P_Resources[0]->next, 2, 0, 0, 2);
    P_Resources[0]->next->next = (Resources *)malloc(sizeof(Resources));
    init_resources(P_Resources[0]->next->next, 3, 0, 2, 0);
    P_Resources[0] = Make_head(P_Resources[0]);

    //进程P2请求资源列表,链表模拟2次请求
    P_Resources[1] = (Resources *)malloc(sizeof(Resources));
    init_resources(P_Resources[1], 3, 0, 2, 1);
    P_Resources[1]->next = (Resources *)malloc(sizeof(Resources));
    init_resources(P_Resources[1]->next, 7, 3, 0, 2);
    P_Resources[1] = Make_head(P_Resources[1]);

    //进程P3请求资源列表,链表模拟4次请求
    P_Resources[2] = (Resources *)malloc(sizeof(Resources));
    init_resources(P_Resources[2], 2, 0, 2, 0);
    P_Resources[2]->next = (Resources *)malloc(sizeof(Resources));
    init_resources(P_Resources[2]->next, 1, 0, 0, 2);
    P_Resources[2]->next->next = (Resources *)malloc(sizeof(Resources));
    init_resources(P_Resources[2]->next->next, 0, 1, 1, 0);
    P_Resources[2]->next->next->next = (Resources *)malloc(sizeof(Resources));
    init_resources(P_Resources[2]->next->next->next, 0, 0, 0, 1);
    P_Resources[2] = Make_head(P_Resources[2]);
    
    //进程P4请求资源列表,用户可选自定义请求，至多4次请求
    printf("银行家算法模拟器已启动。\n");
    printf("系统总资源如下：\n");
    pr(AllResources, "All Resources");
    printf("是否需要增加进程P4的资源请求？(y/n): ");
    char choice[100];//增加缓冲区防止输入过长
    fgets(choice, sizeof(choice), stdin);
    P_Resources[3] = NULL;
    if (choice[0] == 'y' || choice[0] == 'Y') {
        P_Resources[3] = (Resources *)malloc(sizeof(Resources));
        printf("请注意，最多可输入4次请求，输入-1结束输入。\n");
        int a, b, c, d;
        Resources *current = P_Resources[3];
        for(int i = 0; i < 4; i++) 
        {
            printf("请输入第%d次请求的资源数量 (格式: A B C D, 输入-1结束): ", i + 1);
            scanf("%d", &a);
            if (a == -1) {
                if(i == 0) {
                    free(P_Resources[3]);
                    P_Resources[3] = NULL;
                    n=3;
                    printf("您已拒绝增加进程P4的资源请求。\n");
                }
                break;
            }
            scanf(" %d %d %d", &b, &c, &d);
            if(i != 0)
            {
                current->next = (Resources *)malloc(sizeof(Resources));
                current = current->next;
            }
            init_resources(current, a, b, c, d);
        }
        P_Resources[3] = Make_head(P_Resources[3]);
    }
    else {
        n=3;
        printf("您已拒绝增加进程P4的资源请求。\n");
    }

    //增加need矩阵
    Resources* Need[n];
    for(int i = 0; i < n; i++) {
        if(P_Resources[i] != NULL) {
            Need[i] = (Resources *)malloc(sizeof(Resources));
            init_resources(Need[i], P_Resources[i]->sourceA, P_Resources[i]->sourceB, P_Resources[i]->sourceC, P_Resources[i]->sourceD);
        }
    }

    //安全序列记录
    char order[n];

    printf("--------------------------------\n");

    //打印资源信息
    printf("初始资源和进程需要总资源列表如下：\n");
    pr(AllResources, "All Resources");
    for(int i = 0; i < n; i++) {
        char proc_name[100];
        sprintf(proc_name, "P%d Need", (i + 1));
        pr(Need[i], proc_name);
    }

    printf("--------------------------------\n");
    if(is_safe(AvailableResources,Need,P_Resources,n,0,order,NULL))
    {
        printf("系统初始状态为安全状态。\n");
        printf("安全序列为：");
        for(int i = 0; i < n-1; i++)
            printf("P%c->", order[i]);
        printf("P%c", order[n-1]);
        printf("\n");
    }
    else
    {
        printf("系统初始状态为不安全状态，程序终止。\n");
        return 0;
    }
    printf("--------------------------------\n");
    printf("开始处理资源请求...\n");

    //请求资源
    Resources* Request[4];
    for(int i = 0; i < n; i++)
        Request[i] = P_Resources[i]->next; //指向每个进程的第一次请求

    while(1)
    {
        printf("进程的下次请求资源列表如下：\n");
        pr(AvailableResources, "Available");
        int count = 0;
        for(int i = 0; i < n; i++) 
        {
            if(Request[i] == NULL) {
                count++;
                printf("P%d Request:\t%d\t%d\t%d\t%d\tfinished\n", (i + 1) , 0, 0, 0, 0);
                return_resources(AvailableResources, P_Resources[i]);//释放该进程已分配资源
                continue;
            }
            char proc_name[100];
            sprintf(proc_name, "P%d Request", i + 1);
            pr(Request[i], proc_name);
        }

        if(count == n) {
            printf("所有进程均已完成资源请求，退出请求处理。\n");
            break;
        }

        printf("请选择下次请求的进程编号 (1-%d), 输入0退出: ", n);
        scanf("%s", choice);//按行解析
        if(choice[0] == '0') {
            break;
        }
        int proc_id = choice[0] - '1';
        if(Request[proc_id] == NULL) {
            printf("进程P%d已无更多资源请求，跳过该进程。\n", proc_id + 1);
            continue;
        }
        if(handle_request(AvailableResources, Request[proc_id], Need, P_Resources,proc_id, n, order))
        {
            printf("进程P%d的资源请求被批准。\n", proc_id + 1);
            printf("当前系统安全，安全序列为：");
            for(int i = 0; i < n-1; i++)
            printf("P%c->", order[i]);
            printf("P%c\n", order[n-1]);
            pr_allocation(AvailableResources, Need, P_Resources, n);
            //更新下一次请求
            if(Request[proc_id]!= NULL) {
                Request[proc_id] = Request[proc_id]->next;
            } 
        }
        else
        {
            printf("无安全序列，进程P%d的资源请求被拒绝。\n", proc_id + 1);
            pr_allocation(AvailableResources, Need, P_Resources, n);
        }

    }

    printf("退出资源请求处理。\n");
    fr(AllResources);
    fr(AvailableResources);
    for(int i = 0; i < n; i++) {
        fr(P_Resources[i]);
        free(Need[i]);
    }
    return 0;
}