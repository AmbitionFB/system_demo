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

    //创建一个IPCkey
    key = ftok(".", 'a');

    //创建或打开一个消息队列
    msgid = msgget(key, IPC_CREAT|0666);
    if(msgid == -1)
    {
        perror("msgget error");
        exit(EXIT_FAILURE);
    }

    //构造消息
    msg.mtype = MSG_TYPE;
    strcpy(msg.mtext, "hello, this is a message from message sender");

    //发送消息
    if(msgsnd(msgid, &msg, sizeof(msg.mtext),0) == -1)
    {
        perror("msgsnd error");
        exit(EXIT_FAILURE);
    }

    printf("message sent\n");
    return 0;
}