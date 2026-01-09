#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/syscall.h>

#define MY_SYSCALL_NUM 548

int main(int argc, char *argv[])
{
    char buf[128];
    printf("Calling syscall %d...\n", MY_SYSCALL_NUM);
    long ret = syscall(MY_SYSCALL_NUM, buf, sizeof(buf));
    if (ret == -1)
    {
        perror("syscall");
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("Get size %ld\n", ret);
        printf("Get buf %s\n", buf);
        exit(EXIT_SUCCESS);
    }
}