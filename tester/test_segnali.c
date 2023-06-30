#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>


void my_handler(int s, siginfo_t *siginfo, void *garbage){
    printf("\nho ricevuo un segnale %d da %d\n", s, siginfo->si_pid);
}


int main(){
    printf("pid: %d\n", getpid());

    struct sigaction sigact;
    for(int i=1; i<=64; i++){
        sigact.sa_flags = SA_SIGINFO;
        sigact.sa_sigaction = my_handler;
        sigaction(i, &sigact, NULL);
    }

    while(1){
        int pid, signo;
        printf("target pid: ");
        scanf("%d", &pid);
        printf("signal to send: ");
        scanf("%d", &signo);

        if(getpgid(pid) < 0){
            printf("il processo %d non esiste\n", pid);
        } else {
            kill(pid, signo);
        }
    }

    return 0;
}