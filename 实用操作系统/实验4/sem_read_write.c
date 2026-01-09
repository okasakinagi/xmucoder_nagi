#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 10
#define ITEM_COUNT 20

typedef struct
{
    char data[BUFFER_SIZE];
} SharedData;

#define WMUTEX_SEM "/wmutex_sem"
#define RMUTEX_SEM "/rmutex_sem"

void reader(int* reader_count,sem_t* rmutex,sem_t* wmutex,SharedData* shared_data)
{
    sem_wait(rmutex);
    if(*reader_count == 0)
    {
        // First reader locks the writer
        sem_wait(wmutex);
        sleep(1);//模拟读操作延迟仅第一次
    }
    (*reader_count)++;
    sem_post(rmutex);

    printf("Reader read data: %s\n", shared_data->data);
    (*reader_count)--;
    if((*reader_count) == 0)
    {
        // Last reader unlocks the writer
        sem_post(wmutex);
    }
}

void writer(char item,int shm_id,sem_t* rmutex,sem_t* wmutex,SharedData* shared_data)
{
    sem_wait(wmutex);
    snprintf(shared_data->data, BUFFER_SIZE, "Item %c", item);
    printf("Writer wrote data: %s\n", shared_data->data);
    sem_post(wmutex);
}

int main()
{
    key_t shm_key = ftok(".",1);//生成唯一键值
    if (shm_key == -1)
    {
        perror("ftok failed");
        exit(EXIT_FAILURE);
    }

    int shm_id = shmget(shm_key, sizeof(SharedData), IPC_CREAT | 0666);//创建共享内存
    if (shm_id == -1)
    {
        perror("shmget failed");
        exit(EXIT_FAILURE);
    }

    key_t shmc_key = ftok(".",2);//生成唯一键值
    if (shmc_key == -1)
    {
        perror("ftok failed");
        exit(EXIT_FAILURE);
    }

    int shmc_id = shmget(shmc_key, sizeof(int), IPC_CREAT | 0666);//创建共享读者计数器内存
    if (shmc_id == -1)
    {
        perror("shmget failed");
        exit(EXIT_FAILURE);
    }

    SharedData *shared_data = (SharedData *)shmat(shm_id, NULL, 0);//附加共享内存
    if (shared_data == (SharedData *)-1)
    {
        perror("shmat failed");
        exit(EXIT_FAILURE);
    }

    int* reader_count = (int*)shmat(shmc_id, NULL, 0);
    if (reader_count == (int *)-1)
    {
        perror("shmat failed");
        exit(EXIT_FAILURE);
    }

    *reader_count = 0;
    sprintf(shared_data->data, "Item A");

    sem_t *rmutex = sem_open(RMUTEX_SEM, O_CREAT, 0666, 1);
    sem_t *wmutex = sem_open(WMUTEX_SEM, O_CREAT, 0666, 1);


    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
    else if(pid == 0)
    {
        reader(reader_count, rmutex, wmutex, shared_data);
        shmdt(shared_data);
    }else
    {
        pid_t pid_2 = fork();
        if (pid_2 < 0)
        {
            perror("fork failed");
            exit(EXIT_FAILURE);
        }
        else if(pid_2 == 0)
        {
            writer('B', shm_id, rmutex, wmutex, shared_data);
            // reader(reader_count, rmutex, wmutex, shared_data);
            shmdt(shared_data);
        }
        else
        {
            pid_t pid_3 = fork();
            if (pid_3 < 0)
            {
                perror("fork failed");
                exit(EXIT_FAILURE);
            }
            else if(pid_3 == 0)
            {
                // writer('B', shm_id, rmutex, wmutex, shared_data);
                reader(reader_count, rmutex, wmutex, shared_data);
                shmdt(shared_data);
            }
            else
            {
                pid_t pid_4 = fork();
                if (pid_4 < 0)
                {
                    perror("fork failed");
                    exit(EXIT_FAILURE);
                }
                else if(pid_4 == 0)
                {
                    sleep(2);//模拟读者稍晚到达
                    reader(reader_count, rmutex, wmutex, shared_data);
                    shmdt(shared_data);
                }
                else
                {
                    wait(NULL);
                    wait(NULL);
                    wait(NULL);
                    wait(NULL);

                    sem_close(rmutex);
                    sem_close(wmutex);

                    sem_unlink(RMUTEX_SEM);
                    sem_unlink(WMUTEX_SEM);

                    shmdt(shared_data);
                    shmctl(shm_id, IPC_RMID, NULL);

                    printf("Parent process cleaned up resources.\n");
                }
            }
        }
    }
    
    return 0;
}