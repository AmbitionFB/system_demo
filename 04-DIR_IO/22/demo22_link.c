#include <stdio.h>
#include <unistd.h>
#include <unistd.h>

int main()
{
    int ret;
    ret = link("./test1", "./hard");
    if(ret == -1)
    {
        perror("link is error\n");
        return -1;
    }

    return 0;
}
