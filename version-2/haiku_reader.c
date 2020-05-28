#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>

#define MAX_HAIKU_SIZE 100
#define JAPANESE_TYPE 2
#define WESTERN_TYPE 3

struct msgQueue{
    int type;
    char haiku[MAX_HAIKU_SIZE];
};


int main(int argc, char const *argv[])
{
    key_t msgKey;
    int msgID;
    int jp_count = 0, wt_count = 0;

    msgKey = ftok("./smth_key", 65);
    msgID = msgget(msgKey, 0666 | IPC_CREAT);

    while(1){
        struct msgQueue msg;
        char msg_type[9];
        msgrcv(msgID, &msg, sizeof(msg), 0, 0);
        if(msg.type == JAPANESE_TYPE){
            jp_count++;
            strncpy(msg_type, "Japanese", 9);
        }
        else if(msg.type == WESTERN_TYPE){
            wt_count++;
            strncpy(msg_type, "Western", 9);
        }
        printf("%s type haiku: %s\n", msg_type, msg.haiku);
        if(jp_count >= 3 && wt_count >= 3)
            break;
    }

    

    return 0;
}
