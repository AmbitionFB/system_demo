#include <stdio.h>
#include <unistd.h>
#include <unistd.h>

int main()
{
    char buf[50] = {0};
    int ret;
    ret = readlink("./soft", buf, sizeof(buf));
    if(ret == -1)
    {
        perror("readlink is error\n");
        return -1;
    }
    printf("%s\n", buf);
    return 0;
}
