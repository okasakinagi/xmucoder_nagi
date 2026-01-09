#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define block_size 2     // Size of each block in kB
#define total_blocks 500 // Total number of blocks in the file system

// 选择使用位表
int FileSystem[total_blocks]; // Bitmap to track free/used blocks

typedef struct
{
    char filename[20];
    double size; // Size in blocks
    int *blocks;
    int index;
} Fileinfo;

typedef struct Node
{
    Fileinfo file;
    struct Node *next;
} Node;

void initializeFileSystem()
{
    for (int i = 0; i < total_blocks; i++)
    {
        FileSystem[i] = 0; // 0 indicates free block
    }
}

int getRandomSize()
{
    return (rand() % 9 + 2); // Random size between 2 and 10 kB
}

void free_Blocks(int *blocks, int index)
{
    for (int i = 0; i < index; i++)
    {
        if (blocks[i] >= 0 && blocks[i] < total_blocks)
            FileSystem[blocks[i]] = 0; // Mark block as free
    }
    free(blocks);
}

int allocateBlocks(Fileinfo *file)
{
    file->index = (int)ceil(file->size / 2.0);
    file->blocks = (int *)malloc(file->index * sizeof(int));
    int allocated = 0;
    for (int j = 0; j < total_blocks && allocated < file->size; j++)
    {
        if (FileSystem[j] == 0)
        {
            FileSystem[j] = 1; // Mark block as used
            file->blocks[(allocated / 2)] = j;
            allocated += 2;
        }
    }

    if (allocated < file->size) // Not enough space
    {
        printf("Not enough space to allocate file %s\n", file->filename);
        free_Blocks(file->blocks, allocated / 2);
        return 0; // Allocation failed
    }
    return 1; // Allocation successful
}

void printFileSystemStatus()
{
    int i = 0;
    while (i < total_blocks)
    {
        for (int j = 0; j < 32 && i < total_blocks; ++i, ++j)
        {
            printf("%d", FileSystem[i]);
        }
        printf("\n");
    }
}

int main()
{
    initializeFileSystem();
    srand((unsigned int)time(NULL));

    Node *head = NULL;

    for (int i = 0; i < 50; ++i)
    {
        Node *newNode = (Node *)malloc(sizeof(Node));
        newNode->next = head;
        head = newNode;

        sprintf(head->file.filename, "%d.txt", i + 1);
        head->file.size = getRandomSize();
        // head->file.size = 20;// Fixed size 20 kB for testing
        if (!allocateBlocks(&head->file))
        {
            head = head->next;
            free(newNode);
            continue; // Allocation failed, skip this file
        }
    }

    printf("删除前文件系统状态:\n");
    printFileSystemStatus();

    // delete all odd file
    Node *current = head;
    Node *prev = NULL;
    while (current != NULL)
    {
        int file_number;
        sscanf(current->file.filename, "%d.txt", &file_number);
        if (file_number % 2 != 0) // Odd file
        {
            if (prev == NULL)
            {
                head = current->next;
            }
            else
            {
                prev->next = current->next;
            }
            free_Blocks(current->file.blocks, current->file.index);
            Node *temp = current;
            current = current->next;
            free(temp);
        }
        else
        {
            prev = current;
            current = current->next;
        }
    }

    printf("删除后文件系统状态:\n");
    printFileSystemStatus();

    // add consistent file A.txt B.txt C.txt D.txt E.txt with fixed size 7kB,5kB,2kB,9kB,3.5kB
    Node *newnode = (Node *)malloc(sizeof(Node));
    newnode->next = head;
    head = newnode;
    sprintf(head->file.filename, "A.txt");
    head->file.size = 7; // 7 kB
    if (!allocateBlocks(&head->file))
    {
        head = head->next;
        free(newnode);
    }
    else
    {
        printf("成功分配文件 %s，占用块数: %d\n块号:", head->file.filename, head->file.index);
        for (int i = 0; i < head->file.index; i++)
        {
            printf("%d ", head->file.blocks[i]);
        }
        printf("\n");
    }

    newnode = (Node *)malloc(sizeof(Node));
    newnode->next = head;
    head = newnode;
    sprintf(head->file.filename, "B.txt");
    head->file.size = 5; // 5 kB
    if (!allocateBlocks(&head->file))
    {
        head = head->next;
        free(newnode);
    }
    else
    {
        printf("成功分配文件 %s，占用块数: %d\n块号:", head->file.filename, head->file.index);
        for (int i = 0; i < head->file.index; i++)
        {
            printf("%d ", head->file.blocks[i]);
        }
        printf("\n");
    }

    newnode = (Node *)malloc(sizeof(Node));
    newnode->next = head;
    head = newnode;
    sprintf(head->file.filename, "C.txt");
    head->file.size = 2; // 2 kB
    if (!allocateBlocks(&head->file))
    {
        head = head->next;
        free(newnode);
    }
    else
    {
        printf("成功分配文件 %s，占用块数: %d\n块号:", head->file.filename, head->file.index);
        for (int i = 0; i < head->file.index; i++)
        {
            printf("%d ", head->file.blocks[i]);
        }
        printf("\n");
    }

    newnode = (Node *)malloc(sizeof(Node));
    newnode->next = head;
    head = newnode;
    sprintf(head->file.filename, "D.txt");
    head->file.size = 9; // 9 kB
    if (!allocateBlocks(&head->file))
    {
        head = head->next;
        free(newnode);
    }
    else
    {
        printf("成功分配文件 %s，占用块数: %d\n块号:", head->file.filename, head->file.index);
        for (int i = 0; i < head->file.index; i++)
        {
            printf("%d ", head->file.blocks[i]);
        }
        printf("\n");
    }

    newnode = (Node *)malloc(sizeof(Node));
    newnode->next = head;
    head = newnode;
    sprintf(head->file.filename, "E.txt");
    head->file.size = 3.5; // 3.5 kB
    if (!allocateBlocks(&head->file))
    {
        head = head->next;
        free(newnode);
    }
    else
    {
        printf("成功分配文件 %s，占用块数: %d\n块号:", head->file.filename, head->file.index);
        for (int i = 0; i < head->file.index; i++)
        {
            printf("%d ", head->file.blocks[i]);
        }
        printf("\n");
    }
    printf("最终文件系统状态:\n");
    printFileSystemStatus();

    // Free all allocated memory
    current = head;
    while (current != NULL)
    {
        free_Blocks(current->file.blocks, current->file.index);
        Node *temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}