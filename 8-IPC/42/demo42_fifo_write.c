#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{
    //创建命名管道
    mkfifo("my_fifo", 0644);

    //打开命名管道
    int fd = open("my_fifo",O_WRONLY);

    if(fd == -1)
    {
        perror("open");
        exit(1);
    }

    //要写入的数据
    char *msg = "hellp, named pipe!";
    //向命名管道写入数据
    write(fd, msg, strlen(msg)+1);
    printf("pid is %d", getpid());
    //关闭文件描述
    close(fd);
    return 0;
}