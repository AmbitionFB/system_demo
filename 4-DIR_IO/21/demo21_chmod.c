#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

void check_rwx(int ret_access); 

int main(int argc, char *argv[])
{
    int ret_access;  
    int ret_chmod;
    ret_access  = access("./test1", F_OK);
    if(-1 == ret_access)
    {
        perror("文件不存在\n");
        return -1;
    }
    else
    {
        printf("文件存在！\n");
    }
    ret_access  = access("./test1", W_OK);
    check_rwx(ret_access);

    ret_chmod = chmod("./test1", 0777);
    if(ret_chmod == -1)
    {
        perror("chmod is error\n");
        return -2;
    }

    ret_access  = access("./test1", W_OK);  //修改权限后，再次检查
    check_rwx(ret_access);

    return 0;
}

void check_rwx(int ret_access)
{
    if(-1 == ret_access)
    {
        perror("文件是否可写：否\n");
    }
    else
    {
        printf("文件是否可写：是\n");
    }

    ret_access  = access("./test1", R_OK);
    if(-1 == ret_access)
    {
        perror("文件是否可读：否\n");
    }
    else
    {
        printf("文件是否可读：是\n");
    }

    ret_access  = access("./test1", X_OK);
    if(-1 == ret_access)
    {
        perror("文件是否可执行：否\n");
    }
    else
    {
        printf("文件是否可执行：是\n");
    }
}