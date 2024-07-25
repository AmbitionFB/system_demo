/*A程序负责写入数据到共享内存段*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define SHARED_MEMORY_SIZE 1024
int main()
{
    // 创建或打开共享内存对象，获取一个文件描述符
    int fd = shm_open("myshem", O_CREAT|O_RDWR, 0666);
    if(fd == -1)
    {
        perror("shm_open error");
        exit(1);
    }

    //调整共享内存区的大小
    if(ftruncate(fd,SHARED_MEMORY_SIZE)== -1)
    {
        perror("ftruncate");
        exit(1);
    }

    //将共享内存区域映射到当前进程的地址空间
    int *shared_memory = mmap(NULL, SHARED_MEMORY_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    if(shared_memory == MAP_FAILED)
    {
        perror("mmap");
        exit(1);
    }
    close(fd);

    sprintf((char *)shared_memory, "hello world!");

    sleep(1);

    printf("进程A: %s\n", (char *)shared_memory);

    //解除映射关系
    if(munmap(shared_memory,SHARED_MEMORY_SIZE)== -1)
    {
        perror("munmap error");
        exit(1);
    }
    return 0;
}