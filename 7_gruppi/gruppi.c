#include <stdio.h>
#include <unistd.h> 
#include <sys/wait.h>


int main(){
    int isChild = !fork();
    printf("PID %d PPID: %d GID %d\n", getpid(), getppid(), getpgid(0));
    if(isChild){ 
        isChild = !fork(); //new child
        if(!isChild) 
            setpgid(0,0); // Become group leader
        sleep(5);
        printf("------\n");
        fork(); //new child
        printf("PID %d PPID: %d GID %d\n", getpid(), getppid(), getpgid(0));
    }; while(wait(NULL)>0);
}