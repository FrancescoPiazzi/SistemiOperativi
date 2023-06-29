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
    char azione = (argc == 2 ? argv[1][0] : 'g');
    int id = createQueue("/tmp/CAMBIAMI");

    if(azione=='g'){
        msgrcv(id, &message_r, sizeof(message_r.mtext), 0, 0);
        printf("%s\n", message_r.mtext);
    }
    else if(azione=='e'){
        int esito;
        do{
            esito = msgrcv(id, &message_r, sizeof(message_r.mtext), 0, IPC_NOWAIT);
            if(esito>0)
                printf("%s\n", message_r.mtext);
        }while(esito > 0);
    }

    return 0;
}