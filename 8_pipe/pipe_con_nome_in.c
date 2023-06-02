#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>


int main(int argc, char *argv[]) {
    int fd;
    char *fifoName = "/tmp/fifo1";
    mkfifo(fifoName, S_IRUSR | S_IWUSR); // Create pipe if doesn’t exist

    char str1[80], *str2 = "I'm a reader";
    fd = open(fifoName, O_RDONLY); // Open FIFO for read only
    read(fd, str1, 80);            // read from FIFO and close it
    close(fd);

    printf("Writer is writing: %s\n", str1);
}
