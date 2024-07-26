/*分散聚集 IO（Scatter-Gather IO） 也是减少系统调用次数从而提高系统性能的一种方式。 
*分散聚集 IO（Scatter-Gather IO） 是一种 IO 操作方式， 它可以在一次 IO 操作中对多个缓冲区进行读取或写入，
* 而无需对每个缓冲区进行单独的 IO 操作。*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/uio.h>


#define BUF_SIZE 100

int main(int argc, char * argv[])
{
    //定义三个缓冲区
    char buf1[BUF_SIZE] = {0};
    char buf2[BUF_SIZE] = {0};
    char buf3[BUF_SIZE] = {0};

    //定义一个iovec 结构体数组
    struct iovec iov[3];

    //定义一个变量用于记录读取到的字节数
    ssize_t nread;

    //设置iovec 结构体数组中的各个成员的指针和长度
    iov[0].iov_base = buf1;
    iov[0].iov_len = 5;
    iov[1].iov_base = buf2;
    iov[1].iov_len = 8;
    iov[2].iov_base = buf3;
    iov[2].iov_len = BUF_SIZE;

    //从标准输入中读取数据并写入到iovec结构体数组中
    //readv 函数将从标准输入中读取数据， 并将数据分别存储到 iovec 结构体数组 iov 中的三个缓冲区中
    nread = readv(STDIN_FILENO, iov, 3);

    //输出读取的字节数
    printf("%ld bytes read.\n", nread);

    //分别输出三个缓冲区的内容
    printf("buf1: %s\n", buf1);
    printf("buf2: %s\n", buf2);
    printf("buf3: %s\n", buf3);
    return 0;
}