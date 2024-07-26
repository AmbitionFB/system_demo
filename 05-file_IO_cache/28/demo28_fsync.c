/*fsync()函数用于将指定文件的内容数据和元数据写入磁盘*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
    //step1 判断命令行的参数
    if(argc != 3)
    {
        printf("Usage:%s<src file> <obj file>\n", argv[0]);
    }
    //step2 定义变量
    int fd_src;
    int fd_obj;
    char buff[32] = {0};
    ssize_t ret;   //读写操作的返回类型
    //step3 打开文件获得操作符
    fd_src = open(argv[1], O_RDWR);
    if(fd_src < 0)
    {
        perror("open file error\n");
        return -1;
    }
    fd_obj = open(argv[2], O_CREAT|O_RDWR, 0777);
    if(fd_obj < 0)
    {
        perror("obj open is error\n");
        return -2;
    }
    //step4 读写操作
    while((ret = read(fd_src, buff, 32) )!= 0)
    {
        printf("%zd\n", ret );
        printf("%s\n", buff);
        write(fd_obj, buff, ret);
      
    }
    //step5 sync同步
    fsync(fd_obj);
    //step6 关闭文件描述符
    close(fd_src);
    close(fd_obj);
    return 0;
}

