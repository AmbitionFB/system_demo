#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    struct stat file_stat;
    int ret;

    ret = stat("./test", &file_stat);

    if(-1 == ret)  //判断是否执行成功
    { 
        perror("stat error");
        return -1;
    }

    //若执行成功，输出文件大小和inode号
    printf("file sizs: %ld bytes\r\n inode number:%ld\r\n", file_stat.st_size,file_stat.st_ino );
    return 0;
}