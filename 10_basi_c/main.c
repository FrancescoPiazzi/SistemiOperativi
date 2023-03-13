#include <stdio.h>

int main(){
    int x=10;
    printf("variable x : %lu\n", sizeof x);
    printf("expression 1/2 : %lu\n", sizeof 1/2);
    printf("int type : %lu\n", sizeof(int));
    printf("int type : %lu\n", sizeof(short int));
    printf("expression 1.0/2.0 : %f\n", sizeof 1.0/2.0);
    printf("float: %lu\n", sizeof(float));
}