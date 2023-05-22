#include <sys/ipc.h> 
#include <stdio.h> 
#include <sys/msg.h>


void main(){
    key_t queue1Key = ftok("/tmp/unique", 1);
    // ottiene l'id della queue
    // il flag IPC_EXCL la fa fallire se la coda esiste già
    int queueId = msgget(queue1Key , 0777 | IPC_CREAT | IPC_EXCL);
    
}