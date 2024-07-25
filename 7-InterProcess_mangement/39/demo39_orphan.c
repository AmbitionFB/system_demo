#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    pid_t pid = fork();
    if(pid == 0)
    {
        //子进程
        printf("child process is running\n");
        printf("child process wake pid: %d ppid: %d\n", getpid(), getppid());
        sleep(10); //子进程休眠10s
        printf("child process is exiting.\n");
        printf("child process wake pid: %d ppid: %d\n", getpid(), getppid());
    }
    else if(pid > 0)
    {
        printf("parent process is running\n");
        sleep(2);
        printf("parent process is exiting.\n");
    }
    else
    {
        printf("fork failed.\n");
        exit(1);
    }
    return 0;
}