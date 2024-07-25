// /*B程序负责读取共享段的数据，并打印出来*/

// #include <stdio.h>
// #include <unistd.h>
// #include <stdlib.h>
// #include <sys/mman.h>
// #include <sys/stat.h>
// #include <fcntl.h>
// #include <string.h>
// #define SHARED_MEMORY_SIZE 1024

// int main()
// {
//     int fd = shm_open("myshm", O_RDWR, 0666);
//     if(fd == -1)
//     {
//         perror("shm_open error");
//         exit(1);
//     }

//     int * shared_memory = mmap(NULL, SHARED_MEMORY_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
//     if(shared_memory == MAP_FAILED)
//     {
//         perror("map failed");
//         exit(1);
//     }

//     close(fd);
//     sleep(1);
//     //输出共享内存中的数据
//     printf("进程B: %s\n", (char*)shared_memory);

//     //写入数据
//     sprintf((char *)shared_memory, "Good Bye!");

//     //打印全部数据
//     printf("全部数据：%s\n", (char*)shared_memory);

//     //解除映射关系
//     if(munmap(shared_memory,SHARED_MEMORY_SIZE)== -1)
//     {
//         perror("munmap error");
//         exit(1);
//     }
//     return 0;
// }


#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define SHARED_MEMORY_SIZE 1024 // 定义共享内存的大小

int main() 
{
    // 打开共享内存对象，并获取文件描述符
    int fd = shm_open("/myshm", O_RDWR, 0666);
    if (fd == -1) 
    {
        perror("shm_open"); // 打印错误信息
        exit(1); // 退出程序
    }

    // 将共享内存区映射到当前进程的地址空间
    int *shared_memory = mmap(NULL, SHARED_MEMORY_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (shared_memory == MAP_FAILED) 
    {
        perror("mmap"); // 打印错误信息
        exit(1); // 退出程序
    }

    // 关闭文件描述符
    close(fd);

    // 等待 1 秒钟
    sleep(1);

    // 输出共享内存中的数据
    printf("进程 B: %s\n", (char *)shared_memory);

    // 在共享内存中写入数据
    sprintf((char *)shared_memory, "Goodbye, World!");

    // 等待 1 秒钟
    sleep(1);

    // 输出共享内存中的数据
    printf("进程 B: %s\n", (char *)shared_memory);

    // 解除映射关系
    if (munmap(shared_memory, SHARED_MEMORY_SIZE) == -1) 
    {
        perror("munmap"); // 打印错误信息
        exit(1); // 退出程序
    }

    return 0;
}