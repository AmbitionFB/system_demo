/*
*1、通过键盘输入要拷贝文件的路径和文件名等信息
×2、打印我们要拷贝的目录下的所有文件名， 并拷贝我们需要的文件
*/


#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

int main(int argc, char * argv[])
{
    //step 1 定义变量    
    int fd_src;     //源文件描述符
    int fd_obj;     //
    char file_path[32] = {0};
    char file_name[32] = {0};
    char buf[32] = {0};
    DIR *dp;
    struct dirent *dir; 
    ssize_t ret;    //读取到的字节数
    //step 2 键盘输入文件路径
    printf("请输入文件路径：\n");
    scanf("%s", file_path);

    //step 3 打开目录，获取目录流指针，并读取目录
    dp = opendir(file_path);
    if(dp == NULL)
    {
        perror("opendir is error\n");
        return -1;
    }
    printf("oprndir is OK\n");
    while(1)    //循环读取目录
    {
        dir = readdir(dp);
        if(dir != NULL)
        {
            printf("filename is %s\n", dir->d_name);
        }
        else
            break;
    }
    //step 4 获得文件名
    printf("请输入文件名:\n");
    scanf("%s", file_name);
    //step 5 获得文件描述符
    fd_src = open(strcat(strcat(file_path, "/"), file_name), O_RDWR);
    if(fd_src < 0)
    {
        perror("open is error\n");
        return -2;
    }

    fd_obj = open(file_name, O_CREAT|O_RDWR,0666); // 打开或创建文件
    if(fd_obj < 0)
    {
        perror("open is error\n");
        return -3;
    }
    //step 6 读写操作
    while((ret =read(fd_src, buf,32))!= 0)
    {
        write(fd_obj, buf, ret);
    }
    //step7  关闭目录和文件
    close(fd_src);
    close(fd_obj);
    closedir(dp);
    return 0;
}
