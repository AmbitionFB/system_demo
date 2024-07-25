#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024
int main()
{
    //生成一个key
    key_t key = ftok(".",'a');
    if(key == -1)
    {
        perror("ftok");
        exit(1);
    }

    //创建共享内存段
    int shmid = shmget(key, SHM_SIZE, 0666|IPC_CREAT); //创建一个大小为1024的共享内存段
    if(shmid == -1)
    {
        perror("shmget");
        exit(1);
    }

    //连接共享内存段
    char *shmaddr = (char*) shmat(shmid, NULL, 0);
    if(shmaddr == (char*)-1)
    {
        perror("shmat");
        exit(1);
    }

    //写入共享内存
    strncpy(shmaddr, "hello, shared memory",SHM_SIZE);  //向共享内存中写入字符串

    //分离共享内存
    if(shmdt(shmaddr) == -1)
    {
        perror("shmdt");
        exit(1);
    }

    printf("数据已经写入共享内存中\n");

    return 0;
}