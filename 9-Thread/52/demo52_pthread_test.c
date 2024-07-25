#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define THREAD_NUM 2 //线程数量
int count = 0;

void *thread_func(void *arg)
{
    int i;
    for(i=0; i<10000; i++)
    {
        count++;
    }
    pthread_exit(NULL);
}

int main()
{
    pthread_t thread_id[THREAD_NUM];
    int result, i;
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

    printf("the final count is %d\n", count);
    pthread_exit(NULL);
}