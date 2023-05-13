#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

void my_handler(int signal){
    printf("\nho ricevuo un segnale: %d\n", signal);
    if(signal==SIGINT){
        printf("hehe volevi terminarmi\n");
    }
}

void my_handler2(int s){
    static int received=0;
    if(received<10){
        printf("segnali user ricevuti fino ad ora: %d\n", ++received);
    }
    else{
        printf("hai rotto il cazzo\n");
        signal(SIGUSR1, SIG_IGN);
        signal(SIGUSR2, SIG_IGN);
    }
}

void alarm_handler(int s){
    printf("sveglia\n");
    printf("sblocco lo user signal 2");
    sigprocmask(SIG_UNBLOCK);
}


int main(){
    signal(SIGINT, my_handler);
    signal(SIGTSTP, my_handler);

    signal(SIGUSR1, my_handler2);
    signal(SIGUSR2, my_handler2);

    signal(SIGALRM, alarm_handler);


    printf("sono immune a ctrl+C e a ctrl+Z, ma puoi uccidermi con il comando kill %d\n", getpid());

    while(1){
        // alarm non può essere messa in coda (più sveglie settate assieme)
        // se lo fai viene cancellata quella che c'era
        // reimpostata quella nuova e ritornati i secondi che mancavano
        // alla chiamata di quella appena eliminata
        // non usare alarm() e sleep() assieme perchè usano lo stesso segnale
        // quindi fanno casino
        alarm(3);

        sigprocmask(SIG_BLOCK);

        while(1){
            // UwU
        }
    }

    return 0;
}