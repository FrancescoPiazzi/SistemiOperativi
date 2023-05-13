#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
    int f = fork();
    if(f==0){
        printf("figlio\n");
    }
    else{
        printf("padre\n");
    }
    return 0;
}