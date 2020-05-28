#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<time.h>

void send_sigQuit(pid_t serverPid){
    kill(serverPid, SIGQUIT);
}

void send_sigInt(pid_t serverPid){
    kill(serverPid, SIGINT);
}


int main(int argc, char const *argv[])
{
    FILE *pidFile;
    if( (pidFile = fopen("server.pid", "r")) == NULL ){
        perror("Cannot open pid file!");
        exit(EXIT_FAILURE);
    }
    pid_t serverPid;
    fscanf(pidFile, "%d", &serverPid);

    srand(time(0));
    for (int i = 0; i < 100; i++)
    {
        if(rand() % 2)
            send_sigQuit(serverPid);
        else
            send_sigInt(serverPid);
        sleep(1);
    }
    
    return 0;
}