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
    int in;
    int out;
} SharedData;

#define MUTEX_SEM "/mutex_sem"
#define EMPTY_SEM "/empty_sem"
#define FULL_SEM "/full_sem"

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

    SharedData *shared_data = (SharedData *)shmat(shm_id, NULL, 0);//附加共享内存
    if (shared_data == (SharedData *)-1)
    {
        perror("shmat failed");
        exit(EXIT_FAILURE);
    }

    shared_data->in = 0;
    shared_data->out = 0;

    sem_t *mutex = sem_open(MUTEX_SEM, O_CREAT, 0666, 1);
    sem_t *empty = sem_open(EMPTY_SEM, O_CREAT, 0666, BUFFER_SIZE);
    sem_t *full = sem_open(FULL_SEM, O_CREAT, 0666, 0);

    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
    else if(pid == 0)
    {
        for (int i = 0; i < ITEM_COUNT; i++)
        {
            sem_wait(full);
            sem_wait(mutex);
            
            char item = shared_data->data[shared_data->out];
            shared_data->out = (shared_data->out + 1) % BUFFER_SIZE;
            printf("Consumed: %c\n", item);

            sem_post(mutex);
            sem_post(empty);
        }
        printf("Consumer finished consuming.\n");

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
            for (int i = 0; i < ITEM_COUNT; i++)
            {
                char item = 'A' + (i % 26);

                sem_wait(empty);
                sem_wait(mutex);
                
                shared_data->data[shared_data->in] = item;
                shared_data->in = (shared_data->in + 1) % BUFFER_SIZE;
                printf("Produced: %c\n", item);

                sem_post(mutex);
                sem_post(full);
            }
            printf("Producer finished producing.\n");

            shmdt(shared_data);
        }
        else
        {
            wait(NULL);
            wait(NULL);

            sem_close(mutex);
            sem_close(empty);
            sem_close(full);

            sem_unlink(MUTEX_SEM);
            sem_unlink(EMPTY_SEM);
            sem_unlink(FULL_SEM);

            shmdt(shared_data);
            shmctl(shm_id, IPC_RMID, NULL);

            printf("Parent process cleaned up resources.\n");
        }
    }

    return 0;
}