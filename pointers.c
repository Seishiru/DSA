#include <stdio.h>

int main() {
    int **c, *b, a = 27;
    b = &a;
    c = &b;

    printf("value of a: %d\n", a);
    printf("address of a: %p\n\n", &a);

    printf("b is holding &a: %p\n", b);
    printf("b is getting the value of a: %d\n", *b);
    printf("address of b: %p\n\n", &b);

    printf("c is holding &b %p\n", c);
    printf("c is getting the value of b where b is pointing: %d\n", **c);
    printf("address of c %p\n", &c);
    
    return 0;
}
