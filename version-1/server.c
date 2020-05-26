// server.c version 1

// Include libraries

#include <stdio.h> 
#include <sys/ipc.h> 
#include <sys/msg.h> 
#include <string.h> 
#include <stdlib.h> 
#include <signal.h> 
#include <pthread.h>

//Declare global variables


// message struct 
struct mesg_buffer { 
	long mesg_type; 
	int mesg[100]; 
} message; 

//Print Haiku function




//Main function
int main(){


	//declare variables


 	int msgid; 
    key_t key;


 	key = ftok("/etc/passwd", 'A'); 
    if(key<0){
        printf("ftok error \n");
        exit(1);
    }
    
	msgid = msgget(key, 0666 | IPC_CREAT); 
    for(int i=0;i<100;i++){
   
        msgrcv(msgid, &message, sizeof(message), 1, 0); 
        if(message.mesg[i]==2){
                printf("%d) japaneese\n",i);
            }else if(message.mesg[i]==3){
                    printf("%d) western\n",i);
                    }else{
                        printf("%d) no %d\n",i,message.mesg[i]);
                    }

        
    }
    //remove the message queue
	msgctl(msgid, IPC_RMID, NULL); 

    //remove the semaphores




return 0;
}