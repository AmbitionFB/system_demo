#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int ret;
    ret  = access("./test1", F_OK);
    if(-1 == ret)
    {
        perror("文件不存在\n");
        return -1;
    }
    else
    {
        printf("文件存在！\n");
    }
    ret  = access("./test1", W_OK);
    if(-1 == ret)
    {
        perror("文件是否可写：否\n");
    }
    else
    {
        printf("文件是否可写：是\n");
    }

    ret  = access("./test1", R_OK);
    if(-1 == ret)
    {
        perror("文件是否可读：否\n");
    }
    else
    {
        printf("文件是否可读：是\n");
    }

    ret  = access("./test1", X_OK);
    if(-1 == ret)
    {
        perror("文件是否可执行：否\n");
    }
    else
    {
        printf("文件是否可执行：是\n");
    }
    return 0;
}