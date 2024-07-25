#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void siganl_handler(int sigal_num)
{
    switch (sigal_num)
    {
    case SIGHUP:
        printf("收到信号：SIGHUP\n");
        break;
    case SIGINT:
        printf("收到信号：SIGINT\n");
        break;
    case SIGQUIT:
        printf("收到信号：SIGQUIT\n");
        break;
    default:
        perror("signal_handler");
        break;
    }
}

int main()
{
    int count;
    //注册信号处理函数
    signal(SIGHUP, siganl_handler);
    signal(SIGINT, siganl_handler);
    signal(SIGQUIT, siganl_handler);

    printf("this pid is %d\n",getpid());
    while(1)
    {
        sleep(1);
        printf("the count is %d\n", count);
        count++;
    }

    return 0;
}