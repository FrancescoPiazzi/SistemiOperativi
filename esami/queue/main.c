#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h> 
#include <sys/msg.h>
#include <errno.h>
#include <unistd.h>


#define MAX_STR_SIZE 32


struct messagestruct{
    long mtype;
    char mtext[MAX_STR_SIZE];
}message_s, message_r;


int createQueue(char file[MAX_STR_SIZE]){
    int queueId;
    // se il file non esiste lo creo
    if(access(file, F_OK) != 0){
        fclose(fopen(file, "w"));
    }
    key_t queueKey = ftok(file, 1);
    // provo a creare la coda, fallendo se esisteva già
    queueId = msgget(queueKey , 0777 | IPC_CREAT | IPC_EXCL);
    // se fallisco vuol dire che esisteva già, ottengo il suo id
    if(queueId == -1) {
        queueId = msgget(queueKey , 0777);
    }
    return queueId;
}


int main(int argc, char** argv){
    char nome[MAX_STR_SIZE], azione[MAX_STR_SIZE], valore[MAX_STR_SIZE], pid[MAX_STR_SIZE];

    if(argc < 4 || argc > 5){
        fprintf(stderr, "Argomenti sbagliati");
        exit(1);
    }

    strcpy(nome, argv[1]);
    strcpy(azione, argv[2]);
    if(argc == 4){
        strcpy(pid, argv[3]);
    } else {
        strcpy(valore, argv[3]);
        strcpy(pid, argv[4]);
    }

    if(strcmp(azione, "new")==0){
        int id = createQueue(nome);
        printf("%d\n", id);
    }
    else if(strcmp(azione, "put")==0){
        if(argc==4){
            fprintf(stderr, "Val richiesto per put\n");
            exit(1);
        }
        int id = createQueue(nome);
        message_s.mtype = 1;
        strcpy(message_s.mtext, valore);
        msgsnd(id, &message_s, sizeof(message_s.mtext), 0);
    }
    else if(strcmp(azione, "get")==0){
        int id = createQueue(nome);
        msgrcv(id, &message_r, sizeof(message_r.mtext), 0, IPC_NOWAIT);
        printf("%s\n", message_r.mtext);
    }
    else if(strcmp(azione, "del")==0){
        int id = createQueue(nome);
        msgctl(id, IPC_RMID, NULL);
    }
    else if(strcmp(azione, "emp")==0){
        int id = createQueue(nome);
        int esito;
        do{
            esito = msgrcv(id, &message_r, sizeof(message_r.mtext), 0, IPC_NOWAIT);
            if(esito>0)
                printf("%s\n", message_r.mtext);
        }while(esito > 0);
    }
    else if(strcmp(azione, "mov")==0){
        if(argc==4){
            fprintf(stderr, "Val richiesto per mov\n");
            exit(1);
        }
        // controllo che la coda esista
        int rcvid = msgget(ftok(nome, 1) , 0777);
        if(rcvid == -1){
            fprintf(stderr, "la coda '%s' non esiste\n", nome);
            exit(1);
        }
        int sendid = createQueue(valore);
        int esito;
        do{
            esito = msgrcv(rcvid, &message_r, sizeof(message_r.mtext), 0, IPC_NOWAIT);
            if(esito>0)
                msgsnd(sendid, &message_r, sizeof(message_r.mtext), 0);
        }while(esito > 0);
    }

    return 0;
}