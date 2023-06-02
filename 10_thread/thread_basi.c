// Nota: questo programma va compilato passando il flag -pthread a gcc!

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>


void *my_fun(void *param) {
    printf("This is a thread that received %d\n", *(int *)param);
    return (void *)3;
}


int main(void) {
    pthread_t t_id;
    int arg = 10;
    // We need to cast the augment to a void *. We are passing the address of the variable
    pthread_create(&t_id, NULL, my_fun, (void *)&arg);
    printf("Executed thread with id %ld\n", t_id);
    sleep(3);
}