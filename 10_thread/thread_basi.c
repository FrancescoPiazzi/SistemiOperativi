// non tutti i thread sono joinable, ma lo sono di default
// solo un processo può joinarsi con un altro thread
// per rendere un thread unjoinable rendere il thread detached
// un thread detached non può diventare joinable, ma non il contrario
// lo stato si cambia in fase di creazione con .....
// o con la funzione pthread_detach(thread)
// quando un segnale viene inviato ad un processo, non c'è modo di sapere
// quale thread lo riceverà

#include <stdio.h>
#include <threads.h>    // mi sa che non è questa quella che serve


int main(){
    pthread_t t_id;



    return 0;
}