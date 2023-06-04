// 9:45
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/ipc.h> 
#include <sys/msg.h>


FILE* logfile;


struct messagestruct{
    long mtype;
    char mtext[32];
}message_r;


void logsig(int pid, int s){
    if(!fork()){
        sleep(3);
        fprintf(logfile, "%d-%d\n", pid, s);
        fflush(logfile);
    }
}


void repeater(int s, siginfo_t *siginfo, void *garbage){
    kill(siginfo->si_pid, SIGUSR1);
    logsig(siginfo->si_pid, SIGUSR1);
}


void relay(int s, siginfo_t *siginfo, void *garbage){
    if(!fork())
        kill(siginfo->si_pid, SIGUSR2);
    logsig(siginfo->si_pid, SIGUSR2);
}


void close_handler(int s){
    fprintf(logfile, "stop\n");
    fflush(logfile);
}


int main(int argc, char** argv){
    if(argc!=2){
        printf("Argomenti sbagliati\n");
        exit(1);
    }
    printf("pid: %d\n", getpid());

    logfile = fopen(argv[1], "w");

    struct sigaction sa_rep;
    sa_rep.sa_flags = SA_SIGINFO;
    sa_rep.sa_sigaction = repeater;
    sigaction(SIGUSR1, &sa_rep, NULL);

    struct sigaction sa_rel;
    sa_rel.sa_flags = SA_SIGINFO;
    sa_rel.sa_sigaction = relay;
    sigaction(SIGUSR2, &sa_rel, NULL);

    signal(SIGINT, close_handler);

    int qid = msgget(ftok(argv[1], 1), 0777);
    printf("qid: %d\n", qid);

    while(1){
        int r = msgrcv(qid, &message_r, sizeof(message_r.mtext), 0, 0);
        // quando mi arriva un segnale, msgrcv ritorna -1, lo ignoro
        if(r > 0){
            printf("target pid: %s\n", message_r.mtext);
            kill(atoi(message_r.mtext), SIGALRM);
        }
    }

    return 0;
}