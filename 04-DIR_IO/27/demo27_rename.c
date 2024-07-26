#include <stdio.h>
#include <unistd.h>
#include <unistd.h>

int main()
{
    int ret;
    ret = rename("./test", "./test_new");
    if(ret == -1)
    {
        perror("remove error\n");
        return -1;
    }
    printf("rename ok!\n");
    return 0;
}