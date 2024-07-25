#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main()
{
    int fd1[2];
    int fd2[2];
    pid_t pid;
    char buffer1[22];
    char buffer2[22];
    if(pipe(fd1) < 0)
    {
        perror("pipe1");
        exit(-1);
    }
    if(pipe(fd2) < 0)
    {
        perror("pipe2");
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
        close(fd1[0]);  //关闭管道1读端
        close(fd2[1]);  //关闭管道2写端
        printf("this is father process, pid=%d\n", getpid());


        //父进程向子进程发送数据
        write(fd1[1], "hello, child process\n", 22);

         //子进程读取父进程的消息到buffer1
        read(fd2[0],buffer1, 22);    
        printf("Message from child process is %s", buffer1); 

        close(fd1[1]);  //关闭管道1的写端
        close(fd2[0]);  //关闭管道2的读端
    }
    else
    {
        //子进程
        close(fd1[1]);  //关闭管道1写端
        close(fd2[0]);  //关闭管道2读端
        printf("this is child process, pid= %d\n", getpid());

        //子进程读取父进程的消息到buffer2
        read(fd1[0],buffer2, 22);     
        printf("Message from parent process is：%s", buffer2); 
        //子进程向父进程发送数据
        write(fd2[1], "hello, parent process\n", 22);

        close(fd1[0]);  //关闭管道1读端
        close(fd2[1]);  //关闭管道2写端
    }
    return 0;
}