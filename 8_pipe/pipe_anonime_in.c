#include <stdio.h>
#include <unistd.h>
int main() {
    char msg[50];
    int n = 3;
    for (int i=0; i<3; i++) {
        int c = read(0, msg, 49);
        if (c > 0) {
            msg[c] = 0;
            printf("Read: '%s' (%d)\n", msg, c);
        }
    }
}