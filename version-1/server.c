#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

char *sig_type[65];

void signal_handler(int sig){
    printf("This is %s type haiku\n", sig_type[sig]);
}

int main(int argc, char const *argv[])
{
    sig_type[SIGINT] = "Japanese";
    sig_type[SIGQUIT] = "Western";
    FILE *pidFile = fopen("server.pid", "w");
    pid_t pid = getpid();
    fprintf(pidFile, "%d", (int)pid);
    fclose(pidFile);

    signal(SIGINT, signal_handler);
    signal(SIGQUIT, signal_handler);

    while(1);

    return 0;
}