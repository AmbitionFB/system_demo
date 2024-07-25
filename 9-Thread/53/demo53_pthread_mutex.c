#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define THREAD_NUM 2 //线程数量
int count = 0;

pthread_mutex_t mutex; // 定义互斥锁变量
void *thread_func(void *arg)
{
    int i;
    for(i=0; i<10000; i++)
    {
        pthread_mutex_lock(&mutex); // 加锁
        count++; // 计数器加 1
        pthread_mutex_unlock(&mutex); // 解锁
    }
    pthread_exit(NULL);
}

int main()
{
    pthread_t thread_id[THREAD_NUM];
    int result, i;
    pthread_mutex_init(&mutex, NULL); // 初始化互斥锁

    for(i=0; i<THREAD_NUM; i++)
    {
        result = pthread_create(&thread_id[i], NULL, thread_func, NULL);
        if(result != 0)
        {
            perror("pthread create falied");
            exit(EXIT_FAILURE);
        }
    }

    for(i=0; i<THREAD_NUM; i++)
    {
        result = pthread_join(thread_id[i], NULL);
        if(result != 0)
        {
            perror("pthread join falied");
            exit(EXIT_FAILURE);
        }
    }

    pthread_mutex_destroy(&mutex); // 销毁互斥锁
    printf("the final count is %d\n", count);
    pthread_exit(NULL);
}