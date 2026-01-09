#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main()
{
    int fds_to[2], fds_from[2];
    static char start_buf[]="hello pipe";
    char end_buf[20],temp_buf[20];

    if(pipe(fds_to)<0 || pipe(fds_from)<0)
    {
        perror("pipe error");
        exit(1);
    }
    
    pid_t pid = fork();//直接创建子进程,节省行数
    if(pid<0)
    {
        perror("fork error");
        exit(1);
    }
    else if(pid==0)//子进程
    {
        close(fds_from[1]);//关闭写端
        int len = read(fds_from[0],temp_buf,sizeof(temp_buf));
        close(fds_from[0]);

        for(int i=0;i<len/2;i++)
        {
            char temp = temp_buf[i];
            temp_buf[i] = temp_buf[len-2-i];
            temp_buf[len-2-i] = temp;
        }

        close(fds_to[0]);//关闭读端
        write(fds_to[1],temp_buf,len);
        close(fds_to[1]);
    }
    else//父进程
    {
        close(fds_from[0]);//关闭读端
        write(fds_from[1],start_buf,sizeof(start_buf));
        close(fds_from[1]);

        close(fds_to[1]);//关闭写端
        read(fds_to[0],end_buf,sizeof(end_buf));
        close(fds_to[0]);
        printf("result:%s\n",end_buf);
    }
    return 0;
}