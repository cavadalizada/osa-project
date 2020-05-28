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
    FILE *jp_haiku, *wt_haiku;
    char jp_file[MAX_HAIKU_SIZE], wt_file[MAX_HAIKU_SIZE];

    msgKey = ftok("./smth_key", 65);
    msgID = msgget(msgKey, 0666 | IPC_CREAT);

    if( (jp_haiku = fopen("./japanese_haiku.txt", "r")) == NULL || (wt_haiku = fopen("./western_haiku.txt", "r")) == NULL ){
        perror("Cannot open haiku files!");
        exit(EXIT_FAILURE);
    }

    int jp_file_end_flag = 0, wt_file_end_flag = 0;
    while(1){
        if(fgets(jp_file, sizeof(jp_file), jp_haiku)){
            struct msgQueue msg;
            msg.type = JAPANESE_TYPE;
            strncpy(msg.haiku, jp_file, MAX_HAIKU_SIZE);
            msgsnd(msgID, &msg, sizeof(msg), 0);
            printf("Sent message: %s\n", msg.haiku);
        }else
        {
            jp_file_end_flag = 1;
        }
        
        if(fgets(wt_file, sizeof(wt_file), wt_haiku)){
            struct msgQueue msg;
            msg.type = WESTERN_TYPE;
            strncpy(msg.haiku, wt_file, MAX_HAIKU_SIZE);
            msgsnd(msgID, &msg, sizeof(msg), 0);
            printf("Sent message: %s\n", msg.haiku);
        }else
        {
            wt_file_end_flag = 1;
        }
        if(jp_file_end_flag && wt_file_end_flag)
            break;
        
    }

    fclose(jp_haiku);
    fclose(wt_haiku);

    return 0;
}
