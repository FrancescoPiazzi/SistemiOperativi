#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main(){
    // S_IRUSR -> S_I Read User
    chmod("file/file.txt", S_IRUSR | S_IRGRP | S_IROTH);
    return 0;
}