#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MSG_TYPE 1 //定义消息类型为1

struct msgbuf{
    long mtype; //消息类型，必须为long类型，必须大于0
    char mtext[1024];
};
int main()
{
    key_t key;
    int msgid;
    struct msgbuf msg;
    //创建一个IPC key, 需要和发送端保持一致
    key = ftok(".",'a');

    //打开消息队列，以读写模式打开，需要和发送端保持一致
    msgid = msgget(key, 0666);
    if(msgid == -1)
    {
        perror("msgget error");
        exit(EXIT_FAILURE);
    }
    //接收消息
    if(msgrcv(msgid, &msg,sizeof(msg.mtext), MSG_TYPE, 0) == -1)
    {
        perror("msgrcv error");
        exit(EXIT_FAILURE);
    }
    printf("Received message: %s\n", msg.mtext); //打印接收到的消息

    //删除消息队列
    if(msgctl(msgid, IPC_RMID, NULL)== -1)
    {
        perror("msgctl error");
        exit(EXIT_FAILURE);
    }
    return 0;
}