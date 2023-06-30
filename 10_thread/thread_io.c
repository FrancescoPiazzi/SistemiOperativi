// Nota: questo programma va compilato passando il flag -pthread a gcc!

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>


struct ipair_t{
    int n1, n2;
};
typedef struct ipair_t ipair;


void *my_fun(void *param) {
    kill((*(ipair *)param).n2, (*(ipair *)param).n1);
}


int main(void) {
    pthread_t t_id;
    ipair n;
    n.n1 = 10;
    n.n2 = 31843;
    pthread_create(&t_id, NULL, my_fun, (void *)&n);
    printf("Executed thread with id %ld\n", t_id);
    sleep(3);
}