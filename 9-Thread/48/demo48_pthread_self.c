#include <stdio.h>
#include <pthread.h>

pthread_t thread_id,main_thread_id;

void *thread_func(void *arg)
{
    thread_id = pthread_self();
    printf("子进程的ID是 %lu\n", thread_id);
    return NULL;
}

int main()
{
    
    if((pthread_create(&thread_id, NULL, thread_func, NULL) !=0))
    {
        printf("创建线程失败\n");
        return -1;
    }
    
    main_thread_id = pthread_self();
    printf("主线程的ID是%lu\n", main_thread_id);

    pthread_join(thread_id, NULL);
    printf("主线程结束\n");

    return 0;
}