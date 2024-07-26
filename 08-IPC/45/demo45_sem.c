#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

//定义一个信号量的初始值
#define SEM_INIT_VAL 1

int main()
{
    int sem_id;
    struct sembuf sem_buf;

    //生成key
    key_t key = ftok(".",'a');
    if(key == -1)
    {
        perror("ftok");
        exit(1);
    }

    //创建一个信号量
    sem_id = semget(key, 1, IPC_CREAT|0666);
    if(sem_id < 0)
    {
        perror("创建信号失败");
        exit(1);
    }

    //初始化信号量
    if(semctl(sem_id, 0 , SETVAL, SEM_INIT_VAL) < 0)
    {
        perror("初始化信号量失败");
        exit(1);
    }

    //获取信号量
    sem_buf.sem_num = 0;
    sem_buf.sem_op = -1;
    sem_buf.sem_flg = SEM_UNDO;
    if(semop(sem_id, &sem_buf, 1) < 0)
    {
        perror("获取信号量失败");
        exit(1);
    }

    printf("信号量当前值为：%d\n", semctl(sem_id, 0 , GETVAL)); //打印信号量的当前值

    //释放信号量
    sem_buf.sem_num = 0;
    sem_buf.sem_op = 1;
    sem_buf.sem_flg = SEM_UNDO;

    if(semop(sem_id, &sem_buf, 1) < 0)
    {
        perror("释放信号量失败");
        exit(1);

    }
    printf("信号量当前值为：%d\n", semctl(sem_id, 0 , GETVAL)); //打印信号量的当前值

    //删除信号量
    if(semctl(sem_id, 0 , IPC_RMID, 0) < 0)
    {
        perror("删除信号量失败");
        exit(1);
    }

    printf("信号量程序成功执行\n");

    return 0;
}
