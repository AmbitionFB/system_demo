#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    char str[100];
    int flags;

    // 获取 stdin 的文件描述符
    int fd = fileno(stdin);
    // 获取当前标志
    flags = fcntl(fd, F_GETFL);

    //设置文件描述符为非阻塞模式
    
    fcntl(fd, F_SETFL, flags|O_NONBLOCK);
    printf("Enter string: ");
    scanf("%s", str);
    printf("Your entered: %s\n", str);
    return 0;
}