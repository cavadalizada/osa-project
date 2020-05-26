// client.c version 1

// Include libraries

#include <stdio.h> 
#include <unistd.h>
#include <sys/ipc.h> 
#include <sys/msg.h> 
#include <string.h> 
#include <stdlib.h> 
#include <signal.h> 
#include <time.h> 
#include <pthread.h>

//Declare global variables


// message struct 
struct mesg_buffer { 
	long mesg_type; 
	int mesg[100]; 
} message; 

//sends SIGINT
void send_sigint(int msgid,int i) 
{ 

	message.mesg_type = 1; 

    message.mesg[i]=SIGINT;

	msgsnd(msgid, &message, sizeof(message), 0); 

	printf("Sent : %d %d \n", message.mesg[i],i); 
} 

//sends SIGQUIT
void send_sigquit(int msgid,int i) 
{ 

	message.mesg_type = 1; 

    message.mesg[i]=SIGQUIT;

	msgsnd(msgid, &message, sizeof(message), 0); 

	printf("Sent : %d %d \n", message.mesg[i],i); 
} 

//Main function
int main(){

   
    int msgid; 
    key_t key;

 	key = ftok("/etc/passwd", 'A'); 
    if(key<0){
        printf("ftok error \n");
        exit(1);
    }
	msgid = msgget(key, 0666 | IPC_CREAT); 

    srand(time(0));

    for(int i=0 ;i<100; i++){
    printf("%d",i);

    if((rand()%2)==1){
        send_sigint(msgid,i);
    }else if((rand()%2)==0){
        send_sigquit(msgid,i);
    }   


    sleep(2);

}


return 0;
}