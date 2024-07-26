#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[] )
{
    int count; //定义计数器
    printf("this pid is %d\n", getpid());
    while(1)
    {
        sleep(1);
        printf("the count is %d\n", count);
        count++;
    }
    return 0;
}