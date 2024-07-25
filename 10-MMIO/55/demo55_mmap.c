/*
* 创建一个大小为1024的共享内存区域,创建了一个子进程用来通信
* 子进程中，向共享内存中写入整数123,并等待1s后输出共享内存中的数据，最后解除映射关系
* 父进程中，等待子进程写入数据，然后输出共享内存中的数据，接着在共享内存中写入整数456.等待子进程读取数据
* 最后输出共享内存中的数据并解除了映射关系
*/
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#define SHARED_MEMORY_SIZE 1024

int main()
{
    int *shared_memory;
    pid_t pid;
    shared_memory = mmap(NULL, SHARED_MEMORY_SIZE, PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS, -1, 0);   
    // 这里显示MAP_ANONYMOUS未定义是标准不同，编译时添加-std=gnu99

    if(shared_memory == MAP_FAILED)
    {
        perror("map error");
        exit(1);
    }

    pid = fork();
    if(pid == -1)
    {
        perror("fork failed\n");
        exit(42);
    }

    else if(pid == 0) //子进程
    {
        *shared_memory = 123;
        sleep(1);

        printf("子进程： %d\n", *shared_memory);

        if(munmap(shared_memory, SHARED_MEMORY_SIZE) == -1)
        {
            perror("munmap error");
            exit(1);
        }

        exit(0);   // 子进程退出
    }

    else   //父进程
    {
        //父进程等待子进程写入数据
        sleep(2);
        
        //使用wait函数等待子进程结束
        // int status;
        // wait(&status);
        // if(WIFEXITED(status))
        // {
        //     printf("child process exit with code%d\n", status);
        // }


        //输出共享内存的内容
        printf("父进程： %d\n", *shared_memory);
        // 写入数据
        *shared_memory = 456;
        //父进程等待子进程读取数据
        sleep(1);
        //输出共享内存的内容
        printf("父进程： %d\n", *shared_memory);

        if(munmap(shared_memory, SHARED_MEMORY_SIZE) == -1)
        {
            perror("munmap error");
            exit(1);
        }

        exit(0); // 父进程退出
        
    }
    return 0;
}