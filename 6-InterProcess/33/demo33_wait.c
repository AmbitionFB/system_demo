#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    pid_t pid = fork();
    if(pid < 0)
    {
        printf("fork error\n");
        exit(-1);
    }
    else if(pid == 0)
    {
        printf("child process, pid=%d\n", getpid());
        exit(42);
    }
    else
    {
        printf("parent process, parent pid=%d, child pid=%d\n", getpid(),pid);
        int status;
        wait(&status); //等待子进程退出，子进程的退出状态保存在status中
        if(WIFEXITED(status))
        {
            printf("child process exited with status code %d\n", WEXITSTATUS(status)); //打印获取到的子进程退出码
        }
        exit(0);
    }
        
    return 0;
}
