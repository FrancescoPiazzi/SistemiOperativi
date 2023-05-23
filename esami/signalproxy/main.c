#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>


FILE *log_file;


struct messagestruct{
    long mtype;
    int target_pid;
}message;


void logsignal(int pid, int signal){
    int isChild = !fork();      // non sevirebbe se chiamato da relay
    if(isChild){
        sleep(3);
        fprintf(log_file, "%d-%d\n", pid, signal);
        fflush(log_file);
    }
}


void repeater(int s, siginfo_t *siginfo, void *garbage){
    kill(siginfo->si_pid, s);
    logsignal(siginfo->si_pid, s);
}


void relay(int s, siginfo_t *siginfo, void *garbage){
    int isChild = !fork();
    if(isChild){
        kill(siginfo->si_pid, s);
        logsignal(siginfo->si_pid, s);
    }
}


void terminate(int s){
    fprintf(log_file, "stop\n");
    fflush(log_file);
    exit(0);
}


int main(int argc, char **argv){
    if(argc!=2){
        printf("argomenti sbagliati\n");
        exit(1);
    }

    printf("pid: %d\n", getpid());
    log_file = fopen(argv[1], "w");

    struct sigaction sa_rep;
    sa_rep.sa_flags = SA_SIGINFO;
    sa_rep.sa_sigaction = repeater;
    sigaction(SIGUSR1, &sa_rep, NULL);

    struct sigaction sa_rel;
    sa_rel.sa_flags = SA_SIGINFO;
    sa_rel.sa_sigaction = relay;
    sigaction(SIGUSR2, &sa_rel, NULL);

    signal(SIGINT, terminate);

    key_t qkey = ftok(argv[1], 1);
    int qid = msgget(qkey, 0777 | IPC_CREAT);

    while(1){
        msgrcv(qid, &message, sizeof(message.target_pid), 0, 0);
        kill(message.target_pid, SIGALRM);
    }

    return 0;
}