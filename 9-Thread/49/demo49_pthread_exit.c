#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *thread_func(void *arg)
{
    printf("子线程开始执行\n");
    sleep(3);
    printf("子线程执行完毕\n");
    return NULL;
}

int main()
{
    pthread_t tid;
    int ret;

    ret = pthread_create(&tid, NULL, thread_func, NULL);
    if(ret != 0)
    {
        printf("创建线程失败\n");
        exit(EXIT_FAILURE);
    }

    printf("主线程即将退出\n");
    pthread_exit(NULL); //主线程退出
}