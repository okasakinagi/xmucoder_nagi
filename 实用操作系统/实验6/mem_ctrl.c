#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define CACHE 4

int OPT(int *order, int n);
int FIFO(int *order, int n);
int LRU(int *order, int n);

int main()
{
    int execution_order[] = {1, 5, 3, 4, 2, 1, 3, 4, 5, 7, 9, 5, 9, 2, 1};
    int n = sizeof(execution_order) / sizeof(execution_order[0]);
    int hits = OPT(execution_order, n);
    // 输出总页数
    printf("Total pages: %d\n", n);
    // 输出OPT算法的缺页数、缺页率和命中率
    printf("OPT - Hits: %d, Misses: %d, Hit Rate: %.2f%%, Miss Rate: %.2f%%\n",
           hits, n - hits, (float)hits / n * 100, (float)(n - hits) / n * 100);
    hits = FIFO(execution_order, n);
    // 输出FIFO算法的缺页数、缺页率和命中率
    printf("FIFO - Hits: %d, Misses: %d, Hit Rate: %.2f%%, Miss Rate: %.2f%%\n",
           hits, n - hits, (float)hits / n * 100, (float)(n - hits) / n * 100);
    hits = LRU(execution_order, n);
    // 输出LRU算法的缺页数、缺页率和命中率
    printf("LRU - Hits: %d, Misses: %d, Hit Rate: %.2f%%, Miss Rate: %.2f%%\n",
           hits, n - hits, (float)hits / n * 100, (float)(n - hits) / n * 100);
    return 0;
}

int OPT(int *order, int n)
{
    int cache[CACHE] = {0};
    int hits = 0, misses = 0;
    for (int i = 0; i < n; i++)
    {
        int found = 0;
        for (int j = 0; j < CACHE; j++)
        {
            if (cache[j] == order[i])
            {
                hits++;
                found = 1;
                break;
            }
        }
        if (!found)
        {
            misses++;
            int replace_index = -1;
            int farthest = -1;
            for (int j = 0; j < CACHE; j++)
            {
                int k;
                for (k = i + 1; k < n; k++)
                {
                    if (cache[j] == order[k])
                        break;
                }
                if (k > farthest)
                {
                    farthest = k;
                    replace_index = j;
                }
            }
            cache[replace_index] = order[i];
        }
    }
    return hits;
}

int FIFO(int *order, int n)
{
    int cache[CACHE] = {0};
    int hits = 0, misses = 0;
    int next_replace = 0;
    for (int i = 0; i < n; i++)
    {
        int found = 0;
        for (int j = 0; j < CACHE; j++)
        {
            if (cache[j] == order[i])
            {
                hits++;
                found = 1;
                break;
            }
        }
        if (!found)
        {
            misses++;
            cache[next_replace] = order[i];
            next_replace = (next_replace + 1) % CACHE;
        }
    }
    return hits;
}

int LRU(int *order, int n)
{
    int cache[CACHE] = {0};
    int hits = 0, misses = 0;
    int last_used[CACHE] = {0};
    for (int i = 0; i < n; i++)
    {
        int found = 0;
        for (int j = 0; j < CACHE; j++)
        {
            if (cache[j] == order[i])
            {
                hits++;
                last_used[j] = 0;
                found = 1;
            }
            last_used[j]++;
        }
        if (!found)
        {
            misses++;
            int lru_index = 0;
            for (int j = 1; j < CACHE; j++)
            {
                if (last_used[j] > last_used[lru_index])
                    lru_index = j;
            }
            cache[lru_index] = order[i];
            last_used[lru_index] = 0;
        }
    }
    return hits;
}
