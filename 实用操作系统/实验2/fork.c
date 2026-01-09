#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>

void killChildProcess(pid_t pid, int childNumber) {
    if (kill(pid, SIGKILL) == 0) {
        printf("子进程%d被父进程杀死\n", childNumber);
    } else {
        perror("杀死子进程失败");
    }
}

int main() {
    pid_t pid1, pid2;

    // 创建第一个子进程
    pid1 = fork();

    if (pid1 < 0) {
        perror("创建子进程1失败");
        exit(EXIT_FAILURE);
    } else if (pid1 == 0) {
        // 子进程1
        while (1) {
            printf("子进程1正在执行…..\n");
            sleep(1);
        }
    } else {
        // 父进程
        // 创建第二个子进程
        pid2 = fork();

        if (pid2 < 0) {
            perror("创建子进程2失败");
            exit(EXIT_FAILURE);
        } else if (pid2 == 0) {
            // 子进程2
            while (1) {
                printf("子进程2正在执行…..\n");
                sleep(1);
            }
        } else {
            // 父进程
            for (int i = 0; i < 5; ++i) {
                printf("父进程正在执行…..\n");
                sleep(1);
            }

            // 杀死子进程
            killChildProcess(pid1, 1);
            killChildProcess(pid2, 2);

            printf("父进程结束\n");
        }
    }

    return 0;
}