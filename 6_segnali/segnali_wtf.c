#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>


// sblocca il segnale SIGUSR2
void alarm_handler(int s){
    printf("sveglia\n");
    printf("sblocco lo user signal 2\n");

    sigset_t st;
    sigemptyset(&st);
    sigaddset(&st, SIGUSR2);
    sigprocmask(SIG_UNBLOCK, &st, NULL);
}


void user_signal_handler(int s){
    printf("ricevuto un segnale\n");
}


int main(){
    signal(SIGUSR1, user_signal_handler);
    signal(SIGUSR2, user_signal_handler);
    signal(SIGALRM, alarm_handler);

    printf("pid: %d\n", getpid());
    printf("blocco lo user signal 2, si sbloccherà tra poco\n");
    
    sigset_t st;
    sigemptyset(&st);
    sigaddset(&st, SIGUSR2);
    sigprocmask(SIG_BLOCK, &st, NULL);

    // con questa riga scommentata, se mando uno o più segnali mentre il filtro li blocca, 
    // quando il filtro si disattiva ne ricevo 1, ma poi non ne ricevo più
    alarm(10);
    // con questa invece funziona normalmente
    // alarm_handler(23);

    while(1){
        // UwU
    }
}