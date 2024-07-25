#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
int main(int argc, char * argv[])
{
    pid_t pid;
    pid = fork();
    if(pid == -1)
    {
        printf("fork error\n");
        exit(1);
    }
    else if(pid == 0)
    {
        printf("child process:pi=%d\n", getpid());
    }
    else
    {
        printf("parent process pid=%d, childpid=%d\n", getpid(), pid);
    }
    return 0;
}
//为了避免不必要的延迟，会先执行父进程，再执行子进程