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
        exit(0);
    }
    else if(pid > 0)
    {
        //父进程
        char *args[] = {"ps", "-o", "pid,ppid,state,tty,command", NULL};      //要执行的命令和参数       
        printf("Parent process is running.\n");
        sleep(2);
        execvp(args[0], args);
        printf("Parent process is exiting.\n");
    }
    else
    {
        //fork失败
        printf("Fork failed.\n");
        exit(1);
    }
    return 0;
}