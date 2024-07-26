#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
int main()
{
    char buf[100];
    int fd, ret, flag;
    fd_set rdfds;         //定义用于监听事件的文件描述符集合

    //打开鼠标输入设备
    fd = open("/dev/input/event2", O_RDONLY|O_NONBLOCK);
    if(fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    //将标准输入设置为非阻塞模式
    flag = fcntl(STDIN_FILENO, F_GETFL);
    if(flag == -1)
    {
        perror("fcntl F_GETFL");
        exit(EXIT_FAILURE);
    }

    flag |= O_NONBLOCK;
    if(fcntl(STDIN_FILENO, F_SETFL, flag) == -1)
    {
        perror("fcnel F_SETFL");
        exit(EXIT_FAILURE);
    }

    while(1)
    {
        FD_ZERO(&rdfds);
        FD_SET(STDIN_FILENO, &rdfds);
        FD_SET(fd, &rdfds);

        //使用select()等待事件
        ret = select(fd+1,&rdfds,NULL, NULL, NULL);
        if(ret == -1)
        {
            if(errno == EINTR) continue;
            perror("select");
            exit(EXIT_FAILURE);
        }
        else if(ret == 0)
        {
            printf("select 超时");
            continue;
        }

        //处理事件
        if (FD_ISSET(STDIN_FILENO, &rdfds)) 
		{
			memset(buf, 0, sizeof(buf));
			ret = read(STDIN_FILENO, buf, sizeof(buf));
			if (ret > 0) 
			{
				printf("键盘：成功读取了 <%d> 字节的数据\n", ret);
			}
		}

        if(FD_ISSET(fd, &rdfds))
        {
            memset(buf, 0, sizeof(buf));
            ret = read(fd, buf, sizeof(buf));
            if(ret > 0)
            {
                printf("鼠标:成功读取了<%d>字节的数据\n", ret);
            }
        }
    }
    close(fd);
    return 0;
}

