#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>


void my_handler(int signal){
    printf("\nho ricevuo un segnale: %d\n", signal);
}


int main(){
    printf("pid: %d\n", getpid());

    for(int i=1; i<=64; i++)
        signal(i, my_handler);

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