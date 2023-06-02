#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    for (int i=0; i<3; i++){
        sleep(2);
        printf("Written in buffer %d", rand()%100);
        fflush(stdout);
    }
}