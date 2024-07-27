#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h> // Include for calloc
#include <string.h> // Include for string functions

#define MAX 8

typedef char SET[MAX];

void insertElem(SET, char);
void deleteElem(SET, char);
bool isMember(SET, char);
SET *setUnion(SET, SET);
SET *setIntersection(SET, SET);
SET *setDifference(SET, SET);
void display(SET);

int main(void) {
    SET A = {0}, B = {0}, *C;
    insertElem(A, 4);
    insertElem(A, 1);
    insertElem(A, 7);
    insertElem(A, 3);

    insertElem(B, 4);
    insertElem(B, 6);
    insertElem(B, 5);
    insertElem(B, 3);

    display(A);
    display(B);

    C = setUnion(A, B);
    display(*C);

    // Clean up dynamically allocated memory
    free(C);

    return 0;
}

void insertElem(SET A, char ndx) {
    if (ndx < MAX) {
        A[(int)ndx] = 1;
    }
}

void deleteElem(SET B, char ndx) {
    if (ndx < MAX) {
        B[(int)ndx] = 0;
    }
}

bool isMember(SET C, char ndx){ 
    return C[(int)ndx] == 1; 
}

SET *setUnion(SET A, SET B) {
    SET *C = (SET *)calloc(sizeof(SET),1);
    if(*C != NULL){
        int x;
        for (x = 0; x < MAX; x++) {
            (*C)[x] = A[x] | B[x];
        }
    }
    
    return C;
}

SET *setIntersection(SET A, SET B) {
    SET *C = (SET *)calloc(sizeof(SET),1);
    int x;
    for (x = 0; x < MAX; x++) {
        (*C)[x] = A[x] & B[x];
    }
    return C;
}

SET *setDifference(SET A, SET B) {
    SET *C = (SET *)calloc(sizeof(SET),1);
    int x;
    for (x = 0; x < MAX; x++) {
        (*C)[x] = A[x] & ~B[x];
    }
    return C;
}

void display(SET A) {
    int x;
    for (x = 0; x < MAX; x++) {
        if (A[x] == 1) {
            printf("%d\t", x);
        }
    }
    printf("\n");
}