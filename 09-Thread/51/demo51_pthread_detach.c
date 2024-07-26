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
    pthread_t thread_id;
    int result;

    result = pthread_create(&thread_id, NULL, thread_function, NULL);
    if(result != 0)
    {
        perror("thread creation failed");
        exit(EXIT_FAILURE);
    }

    //分离子线程
    if(pthread_detach(thread_id) != 0)
    {
        perror("thread detach failed");
        exit(EXIT_FAILURE);
    }

    printf("主线程正在退出\n");
    pthread_exit(NULL);
    return 0;
}