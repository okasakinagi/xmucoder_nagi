#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/wait.h>

struct Msg
{
    long mtype;
    char mtext[100];
} msg;

int main()
{
    pid_t pid_server = fork(), pid_client;
    int msgid = msgget(75,0666|IPC_CREAT);

    if(pid_server<0)
    {
        perror("fork error");
        exit(1);
    }
    else if(pid_server==0)//子进程
    {
        char buf[100];
        while(1)
        {
            int len = msgrcv(msgid,&msg,sizeof(msg.mtext),0,0);
            printf("(server)receive\n");
            if(msg.mtype == 1) break;
        }
    }
    else{
        pid_client = fork();
        if(pid_client<0)
        {
            perror("fork error");
            exit(1);
        }
        else if(pid_client==0)//子进程
        {
            for(int i=10;i>0;i--)
            {
                msg.mtype = i;
                sprintf(msg.mtext,"hello msg %d",i);
                msgsnd(msgid,&msg,sizeof(msg.mtext),0);
                printf("(client)send\n");
            }
        }
        else
        {
            waitpid(pid_client,NULL,0);
            waitpid(pid_server,NULL,0);
            msgctl(msgid,IPC_RMID,NULL);
        }
    }
    return 0;
}