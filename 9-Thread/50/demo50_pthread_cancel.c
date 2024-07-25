#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
void *thread_function(void *arg)
{
    int i;
    printf("子线程开始运行\n");
    for(i=1; i <= 5; i++)
    {
        printf("子线程打印： %d\n", i);
        sleep(1);
    }
    printf("子线程结束\n");
    return NULL;
}

int main()
{
    pthread_t thread;
    int ret;

    ret = pthread_create(&thread, NULL, thread_function, NULL);
    if(ret != 0)
    {
        perror("thread creation failed");
        exit(EXIT_FAILURE);
    }

    //等待2s
    sleep(2);


    //取消子线程
    if(pthread_cancel(thread) != 0)
    {
        perror("thread cancellation failed");
        exit(EXIT_FAILURE);
    }
    // if(pthread_join(thread, NULL) != 0)
    // {
    //     printf("等待子线程结束失败");
    //     exit(EXIT_FAILURE);
    // }
    // printf("主线程结束\n");

    return 0;
}