#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main()
{
    int fd[2];
    pid_t pid;
    char buffer[22];
    if(pipe(fd) < 0)
    {
        perror("pipe");
        exit(-1);
    }

    //创建一个新进程，如果失败，则输出错误信息退出程序
    pid = fork();
    if(pid < 0)
    {
        perror("fork");
        exit(-1);
    }
    else if(pid > 0)  //父进程
    {
        close(fd[0]);  //关闭管道读端
        printf("this is father process, pid=%d\n", getpid());
        write(fd[1], "hello, child process\n", 22);
    }
    else
    {
        //子进程
        close(fd[1]);  //关闭管道写端
        printf("this is child process, pid= %d\n", getpid());
        read(fd[0],buffer, 22);
        printf("Message from parent process is %s", buffer); 
        close(fd[0]);   //关闭管道读端
    }
    return 0;
}