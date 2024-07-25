#include <stdio.h>
#include <unistd.h>
#include <unistd.h>

int main()
{
    int ret;
    ret = symlink("./test1", "./soft");
    if(ret == -1)
    {
        perror("link is error\n");
        return -1;
    }

    return 0;
}
