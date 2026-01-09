#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct
{
    int at; // Arrival Time
    int st; // Service Time
} Process;

int Find_Min(int *arr, int n);
int Find_Max_Float(float *arr, int n);

void FCFS(Process **p, int n, int *res_ct);
void RR(Process **p, int n, int *res_ct, int time_quantum);
void SPN(Process **p, int n, int *res_ct);
void SRT(Process **p, int n, int *res_ct);
void HRRN(Process **p, int n, int *res_ct);

int main()
{
    Process *p[5];

    // 定义5个进程
    p[0] = (Process *)malloc(sizeof(Process));
    p[0]->at = 0, p[0]->st = 3;
    p[1] = (Process *)malloc(sizeof(Process));
    p[1]->at = 2, p[1]->st = 6;
    p[2] = (Process *)malloc(sizeof(Process));
    p[2]->at = 4, p[2]->st = 4;
    p[3] = (Process *)malloc(sizeof(Process));
    p[3]->at = 6, p[3]->st = 5;
    p[4] = (Process *)malloc(sizeof(Process));
    p[4]->at = 8, p[4]->st = 2;

    int *res_ct = (int *)malloc(5 * sizeof(int)); // Completion Time
    memset(res_ct, 0, 5 * sizeof(int));

    FCFS(p, 5, res_ct);
    printf("FCFS:\n");
    printf("Process\tCT\tTAT\tRR\n");
    for (int i = 0; i < 5; i++)
        printf("%c\t%d\t%d\t%f\n", i + 'A', res_ct[i], res_ct[i] - p[i]->at,
               (float)(res_ct[i] - p[i]->at) / p[i]->st);
    memset(res_ct, 0, 5 * sizeof(int));

    RR(p, 5, res_ct, 1);
    printf("\nRR (Time Quantum = 1):\n");
    printf("Process\tCT\tTAT\tRR\n");
    for (int i = 0; i < 5; i++)
        printf("%c\t%d\t%d\t%f\n", i + 'A', res_ct[i], res_ct[i] - p[i]->at,
               (float)(res_ct[i] - p[i]->at) / p[i]->st);
    memset(res_ct, 0, 5 * sizeof(int));

    SPN(p, 5, res_ct);
    printf("\nSPN:\n");
    printf("Process\tCT\tTAT\tRR\n");
    for (int i = 0; i < 5; i++)
        printf("%c\t%d\t%d\t%f\n", i + 'A', res_ct[i], res_ct[i] - p[i]->at,
               (float)(res_ct[i] - p[i]->at) / p[i]->st);
    memset(res_ct, 0, 5 * sizeof(int));

    SRT(p, 5, res_ct);
    printf("\nSRT:\n");
    printf("Process\tCT\tTAT\tRR\n");
    for (int i = 0; i < 5; i++)
        printf("%c\t%d\t%d\t%f\n", i + 'A', res_ct[i], res_ct[i] - p[i]->at,
               (float)(res_ct[i] - p[i]->at) / p[i]->st);
    memset(res_ct, 0, 5 * sizeof(int));

    HRRN(p, 5, res_ct);
    printf("\nHRRN:\n");
    printf("Process\tCT\tTAT\tRR\n");
    for (int i = 0; i < 5; i++)
        printf("%c\t%d\t%d\t%f\n", i + 'A', res_ct[i], res_ct[i] - p[i]->at,
               (float)(res_ct[i] - p[i]->at) / p[i]->st);
    memset(res_ct, 0, 5 * sizeof(int));

    for (int i = 0; i < 5; i++)
        free(p[i]);
    free(res_ct);
    return 0;
}

int Find_Min(int *arr, int n)
{
    int min_idx = -1;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] != -1)
        {
            if (min_idx == -1 || arr[i] < arr[min_idx])
                min_idx = i;
        }
    }
    return min_idx;
}

int Find_Max_Float(float *arr, int n)
{
    int max_idx = -1;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] != -1.0f)
        {
            if (max_idx == -1 || arr[i] > arr[max_idx])
                max_idx = i;
        }
    }
    return max_idx;
}

void FCFS(Process **p, int n, int *res_ct)
{
    int current_time = 0;

    for (int i = 0; i < n; i++)
    {
        if (current_time < p[i]->at)
            current_time = p[i]->at; // 等待进程到达

        current_time += p[i]->st; // 处理进程
        res_ct[i] = current_time; // 记录完成时间
    }
}

void RR(Process **p, int n, int *res_ct, int time_quantum)
{
    int *rt = (int *)malloc(n * sizeof(int)); // Remaining Time
    int completed = 0;
    int current_time = 0;
    int tail = 0;
    int *queue = (int *)malloc(n * sizeof(int)); // Process Queue
    memset(queue, -1, n * sizeof(int));
    for (int i = 0; i < n; i++)
        rt[i] = p[i]->st;
    while (completed < n)
    {
        for (int i = 0; i < n; i++)
            if (p[i]->at <= current_time && rt[i] > 0 && queue[i] == -1)
                queue[i] = tail++;
        int idx = Find_Min(queue, n); // 找到队列头部进程
        if (idx == -1)
        {
            current_time++;
            continue;
        }
        if (rt[idx] > time_quantum)
        {
            current_time += time_quantum;
            rt[idx] -= time_quantum;
            queue[idx] = tail++; // 加回到队列尾
        }
        else
        {
            current_time += rt[idx];
            rt[idx] = 0;
            res_ct[idx] = current_time;
            completed++;
            queue[idx] = -1; // Remove from queue
        }
    }
}

void SPN(Process **p, int n, int *res_ct)
{
    int *st = (int *)malloc(n * sizeof(int));
    int *finished = (int *)malloc(n * sizeof(int));
    int completed = 0;
    int current_time = 0;
    memset(st, -1, n * sizeof(int));
    memset(finished, 0, n * sizeof(int));
    while (completed < n)
    {
        for (int i = 0; i < n; i++)
            if (p[i]->at <= current_time && st[i] == -1 && !finished[i])
                st[i] = p[i]->st;
        int idx = Find_Min(st, n);
        if (idx == -1)
        {
            current_time++;
            continue;
        }
        current_time += st[idx];
        res_ct[idx] = current_time;
        st[idx] = -1;
        finished[idx] = 1;
        completed++;
    }
}

void SRT(Process **p, int n, int *res_ct)
{
    int *rt = (int *)malloc(n * sizeof(int));
    int *finished = (int *)malloc(n * sizeof(int));
    int completed = 0;
    int current_time = 0;
    memset(rt, -1, n * sizeof(int));
    memset(finished, 0, n * sizeof(int));
    while (completed < n)
    {
        for (int i = 0; i < n; i++)
            if (p[i]->at <= current_time && rt[i] == -1 && !finished[i])
                rt[i] = p[i]->st;
        int idx = Find_Min(rt, n);
        if (idx == -1)
        {
            current_time++;
            continue;
        }
        rt[idx]--;
        current_time++;
        if (rt[idx] == 0)
        {
            res_ct[idx] = current_time;
            rt[idx] = -1;
            finished[idx] = 1;
            completed++;
        }
    }
}

void HRRN(Process **p, int n, int *res_ct)
{
    float *rr = (float *)malloc(n * sizeof(float));
    int *finshed = (int *)malloc(n * sizeof(int));
    int completed = 0;
    int current_time = 0;
    memset(rr, -1.0f, n * sizeof(float));
    memset(finshed, 0, n * sizeof(int));
    while (completed < n)
    {
        for (int i = 0; i < n; i++)
            if (p[i]->at <= current_time && !finshed[i])
                rr[i] = (float)(current_time - p[i]->at + p[i]->st) / p[i]->st;
        int idx = Find_Max_Float(rr, n);
        if (idx == -1)
        {
            current_time++;
            continue;
        }
        current_time += p[idx]->st;
        res_ct[idx] = current_time;
        rr[idx] = -1.0f;
        finshed[idx] = 1;
        completed++;
    }
}