#include <stdio.h>

union U{
    int a;
    float b;
};

int main(){
    int x=10;
    printf("variable x : %lu\n", sizeof x);
    printf("expression 1/2 : %lu\n", sizeof 1/2);
    printf("int type : %lu\n", sizeof(int));
    printf("int type : %lu\n", sizeof(short int));
    printf("expression 1.0/2.0 : %f\n", sizeof 1.0/2.0);
    printf("float: %lu\n", sizeof(float));

    union U u1;
    u1.a=4;
    u1.b=5.6;

    printf("union a: %d (un paciugo perche' ho assegnato b e a e b non possono coesistere)\n", u1.a);
    printf("union b: %f\n", u1.b);

    return 0;
}