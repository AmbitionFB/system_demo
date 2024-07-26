#include <stdio.h>
#include <unistd.h>
#include <unistd.h>

int main()
{
    int ret;
    ret = remove("./test");
    if(ret == -1)
    {
        perror("remove error\n");
        return -1;
    }
    printf("remove ok!\n");
    return 0;
}