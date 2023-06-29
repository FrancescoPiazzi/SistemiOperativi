#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h> 
#include <sys/msg.h>
#include <errno.h>
#include <unistd.h>


#define MAX_STR_SIZE 512
#define N_FOR_FTOK 1


struct messagestruct{
    long mtype;
    char mtext[MAX_STR_SIZE];
}message_s, message_r;


int qExists(key_t queueKey){
    // provo a creare la coda, fallendo se esisteva già
    return msgget(queueKey , 0777 | IPC_CREAT | IPC_EXCL);
}


int createQueue(char file[MAX_STR_SIZE]){
    int queueId;
    // se il file non esiste lo creo
    if(access(file, F_OK) != 0){
        fclose(fopen(file, "w"));
    }
    key_t queueKey = ftok(file, N_FOR_FTOK);
    queueId = qExists(queueKey);
    // se fallisco vuol dire che esisteva già, ottengo il suo id
    if(queueId == -1) {
        queueId = msgget(queueKey , 0777);
    }
    return queueId;
}


int main(int argc, char **argv){
    int id = createQueue("/tmp/CAMBIAMI");
    char messaggio[MAX_STR_SIZE];

    strcpy(messaggio, argc==2 ? argv[1] : "MESSAGGIO_DEFAULT");

    message_s.mtype = 1;
    strcpy(message_s.mtext, messaggio);
    msgsnd(id, &message_s, sizeof(message_s.mtext), 0);
}