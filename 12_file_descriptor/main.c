#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
    // 0, 1 e 2 normalmente sono, rispettivamente stdin, stdout, e stderr
    // il kernel tiene due tabelle: quella dei file attivi e quella dei file aperti
    char buf[128];
    int file = open("input.txt", O_RDONLY, NULL);
    read(file, buf, 128);
    printf("contenuto del file:\n%s", buf);

    lseek(file, -5, SEEK_END);
    char buf2[128];
    read(file, buf2, 128);
    printf("contenuto dopo aver spostato il puntatore:\n%s", buf);

    // close(file);

    return 0;
}