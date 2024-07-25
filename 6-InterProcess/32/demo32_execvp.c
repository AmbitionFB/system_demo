/*子进程的创建往往和 exec 函数一起使用
* fork和vfork函数只是创建进程，但是使用却是父进程的所有资源。
* 若想希望执行不同的程序，则需要使用exec族函数
× exec 函数会将新程序加载到子进程的地址空间中，
* 并将程序入口地址作为新的堆栈指针， 然后跳转到程序入口地址开始执行
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(int argc, char * argv[])
{
    pid_t pid;
    pid = fork();
    if(pid == -1)
    {
        printf("fork error\n");
        return 1;
    }
    else if(pid == 0)
    {
        //子进程的代码
        char *args[] = {"ls", "-l", NULL}; //要执行的命令及其参数
        execvp(args[0],args);
        printf("This line will not be executed.\n"); //execvp()函数执行失败的话，这行代码会被执行
        exit(0);
    }
    else
    {
        wait(NULL);
        printf("child process has finished.\n");
        printf("parent process pid=%d, childpid=%d\n", getpid(), pid);
    }
    return 0;
}
