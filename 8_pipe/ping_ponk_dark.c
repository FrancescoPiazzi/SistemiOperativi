#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define READ 0
#define WRITE 1

int main()
{
    int pipe1[2], pipe2[2];
    char buf[50];
    pipe(pipe1);
    pipe(pipe2);
    int p2 = !fork();
    if (p2) {
        close(pipe1[WRITE]);
        close(pipe2[READ]);
        int r;
        while(rand()%5 > 0){
            r = read(pipe1[READ], &buf, 50); // Read from pipe
            printf("P2 received: '%s'\n", buf);
            write(pipe2[WRITE], "pong", 5); // Writes to pipe
        }
        r = read(pipe1[READ], &buf, 50); // Read from pipe
        printf("P2 received: '%s'\n", buf);
        write(pipe2[WRITE], "bad pong", 9); // Writes to pipe
        
        close(pipe1[READ]);
        close(pipe2[WRITE]);
    }
    else {
        close(pipe1[READ]);
        close(pipe2[WRITE]);

        int r;
        do{
            write(pipe1[WRITE], "ping", 5); // Writes to pipe
            r = read(pipe2[READ], &buf, 50); // Read from pipe
            printf("P1 received: '%s'\n", buf);
        }while(r == 5);

        printf("P2 lost the game, as excpected\n");
        
        close(pipe1[WRITE]);
        close(pipe2[READ]);
        while (wait(NULL) > 0);
    }

    return 0;
}