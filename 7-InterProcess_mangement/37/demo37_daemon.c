/*创建一个守护进程 daemon*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

int main()
{
    pid_t pid;
    //1 屏蔽一些控制终端操作的信号
    signal(SIGTTOU, SIG_IGN);   //后台进程企图从控制终端写   signal函数的使用， 后一个参数handler为SIG_IGN 为忽略信号
    signal(SIGTTIN, SIG_IGN);   //后台进程企图从控制终端读 
    signal(SIGTSTP, SIG_IGN);   //控制终端（tty）上按下停止键
    //2 调用fork, 父进程退出
    pid = fork();
    if(pid < 0)
    {
        printf("fork error\n");
        exit(1);
    }
    if(pid > 0)
    {
        exit(0);
    }
    //3 setsid 一个新会话
    if(setsid() == -1)
    {
        printf("setsid error\n");
        exit(1);
    }
    //4 禁止进程重新打开控制终端
    signal(SIGHUP, SIG_IGN);  //SIGHUP 挂起信号， 通常用于重新读取配置文件等操作
    pid = fork();
    if(pid < 0)
    {
        printf("fork error\n");
        exit(1);
    }
    if(pid > 0)
    {
        exit(0);
    }
    //5 关闭打开的文件描述符
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    //6 改变当前的工作目录
    chdir("/");
    //7 重设文件创建掩模
    umask(0);
    //8 处理SIGCHLD信号
    signal(SIGCHLD, SIG_IGN);  
    /*SIGCHLD  当一个子进程结束时，操作系统会向父进程发送这个信号。
    *这个信号通知父进程，它的一个子进程已经终止，无论是正常退出还是因为接收到信号而终止。
    */


    //此时守护进程创建完毕
    while(1)
    {
        sleep(1);
    }
    return 0;
}
