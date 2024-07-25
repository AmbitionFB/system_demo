#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int fd;
    char *addr; //映射区的起始地址
    off_t size;  // 文件大小

    if(argc != 2)   //判断文件名是否输入
    {
        fprintf(stderr, "用法：%s<文件名>\n", argv[0]);  
        exit(1);                                         //异常退出
    }

    fd = open(argv[1], O_RDONLY);
    if(fd == -1)
    {
        perror("打开文件");    //打印错误信息
        exit(1);               //异常退出
    }

    //获取文件大小
    size = lseek(fd, 0, SEEK_END); //将文件指针定位到文件末尾
    if(size ==(off_t) -1)  //这里的off_t 是用来指明-1 的类型
    {
        perror("获取文件大小");
        exit(1);
    }

    //映射文件到内存中
    addr = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
    if(addr == MAP_FAILED)
    {
        perror("映射文件");
        exit(1);
    }

    printf("%.*s\n", (int)size, addr); //输出映射到内存中的文件内容
    if(munmap(addr, size) == -1)
    {
        perror("解除映射");   //打印错误信息
        exit(1);
    }

    close(fd);
    return 0;
}