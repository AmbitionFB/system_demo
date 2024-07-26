#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{
    //创建有名管道(命名管道)
    mkfifo("my_fifo",0644);

    //打开命名管道。以只读方式打开，获取文件描述符
    int fd = open("my_fifo", O_RDONLY);

    if(fd == -1)
    {
        perror("open fifo");
        exit(1);
    }

    char buf[256];  //定义存储数据的缓冲区

    //命名管道中读取数据到buf,最多256字节，并返回实际读取到的字节数
    int n =read(fd, buf, 256);

    //输出读取到的数据
    printf("pid is %d", getpid());
    printf("Received message: %s\n", buf);

    close(fd);
    return 0;
}