#include <stdio.h>
#include <pthread.h>

void *printf_message(void *str)
{
    printf("%s\n", (char *) str);
    return NULL;
}

int main()
{
    pthread_t thread_id; //  线程ID
    char *message = "你好，线程";
    int result;

    //创建新线程并传入参数
    result = pthread_create(&thread_id, NULL, printf_message, (void*) message);

    if(result != 0)
    {
        printf("错误，创建新线程失败。\n");
        return -1;
    }

    printf("主线程结束。\n");
    return 0;
}