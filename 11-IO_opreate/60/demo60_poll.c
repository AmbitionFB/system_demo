#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <poll.h>

int main(int argc, char *argv[])
{
	char buf[100];
	int fd, ret, flag;
	struct pollfd fds[2]; // 定义用于监视读事件的文件描述符集�?

	// 打开鼠标输入设备
	fd = open("/dev/input/event2", O_RDONLY | O_NONBLOCK);
	if (fd == -1) 
	{
		perror("open");
		exit(EXIT_FAILURE);
	}

	// 将标准输入设置为非阻塞模�?
	flag = fcntl(STDIN_FILENO, F_GETFL);
	if (flag == -1) 
	{
		perror("fcntl F_GETFL");
		exit(EXIT_FAILURE);
	}
	flag |= O_NONBLOCK;
	if (fcntl(STDIN_FILENO, F_SETFL, flag) == -1) 
	{
		perror("fcntl F_SETFL");
		exit(EXIT_FAILURE);
	}

	//初始化结构体数组
	fds[0].fd = STDIN_FILENO;  // 添加标准输入文件描述符到数组�?
	fds[0].events = POLLIN;	//监视读事�?
	fds[1].fd = fd;				// 添加鼠标输入文件描述符到数组�?
	fds[1].events = POLLIN;     // 监视读事�?

	while (1) 
	{
		

		// 使用poll()等待事件
		ret = poll(fds, 2, -1);
		if (ret == -1) 
		{
			if (errno == EINTR) continue;
			perror("poll");
			exit(EXIT_FAILURE);
		} else if (ret == 0) 
		{
			printf("select 超时.\n");
			continue;
		}

		// 处理事件
		if (fds[0].events &POLLIN) 
		{
			memset(buf, 0, sizeof(buf));
			ret = read(STDIN_FILENO, buf, sizeof(buf));
			if (ret > 0) 
			{
				printf("键盘：成功读取了 <%d> 字节的数据\n", ret);
			}
		}
		if (fds[1].events &POLLIN) 
		{
			memset(buf, 0, sizeof(buf));
			ret = read(fd, buf, sizeof(buf));
			if (ret > 0) 
			{
				printf("鼠标：成功读取了 <%d> 字节的数据\n", ret);
			}
		}
	}
	close(fd);
	return 0;
}
