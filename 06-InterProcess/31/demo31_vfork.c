#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
int main(int argc, char * argv[])
{
    pid_t pid;
    pid = vfork();
    if(pid == -1)
    {
        printf("vfork error\n");
        exit(1);
    }
    else if(pid == 0)
    {
        printf("child process:pi=%d\n", getpid());
        _exit(0);
    }
    else
    {
        printf("parent process pid=%d, childpid=%d\n", getpid(), pid);
    }
    return 0;
}
/*使用fork函数 ，为了避免不必要的延迟，会先执行父进程，再执行子进程
* 而vfork函数创建子进程后，会进入阻塞状态，等待子进程执行完，直到调用 exec()族函数或_exit()函数为止
* 对比demo30的结果先显示了这一差异。
*/