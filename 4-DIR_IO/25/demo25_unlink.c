#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
    int ret;
    ret = unlink("./test"); // 使用 unlink 函数删除指定的文件
    if (ret == -1)
{
    perror("unlink error");
    return -1;
} 
    return 0;
}