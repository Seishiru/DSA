#include <stdio.h>
#define MAX 12

typedef struct {
    int tree[MAX];
    int lastNdx;
}POT;

POT init();
void display(POT A);
void insertNonHeapified(POT *A, int elem);
void populate(POT *A);
void heapify(POT *A);
void swap(int *high, int *low);
void deleteMin(POT *A);
void minheap(POT *A, int *min, int *sub);


int main() {
    POT A;
    A = init(); 

    populate(&A);
    heapify(&A);
    display(A); 
    for(int x = 0; x < 10; x++)
    deleteMin(&A);
    display(A);
    
    return 0;
}

POT init() {
    return (POT){.tree = {0}, .lastNdx = -1};
}
void display(POT A) {
    printf("\nNode Index | Node Value |  [Last Index : %d]\n", A.lastNdx);
    printf("----------------------------------------\n");
    for (int i = 0; i < MAX; i++) {
        printf("%-10d | %-10d |\n", i, A.tree[i]);
    }
    printf("----------------------------------------\n");
}
void insertNonHeapified(POT *A, int elem) {
    if(A->lastNdx < MAX) {
        A->tree[++A->lastNdx] = elem;
    }
}
void populate(POT *A) {
    const int elements[] = {30, 40, 20, 10, 50, 25, 60, 45, 15, 35};

    for (int i = 0; i < sizeof(elements) / sizeof(elements[0]); i++) {
        insertNonHeapified(A, elements[i]);
    }
}
void heapify(POT *A) {
    int parent, sub, min;
    for(parent = (A->lastNdx)/2; parent >= 0; parent--) {
        for(sub = parent, min = sub*2+1; min <= A->lastNdx;) {
            min = (min+1 > A->lastNdx)? min : (A->tree[min] < A->tree[min+1])? min: min+1;
            minheap(A, &min, &sub);
        }
    }
}  
void swap(int *high, int *low) {
    int temp = *high;
    *high = *low;
    *low = temp;
}
void deleteMin(POT *A) {
    if(A->lastNdx >= 0) {
        swap(&A->tree[A->lastNdx--], &A->tree[0]);
        int sub, min;
        for(sub = 0, min = sub*2+1; min <= A->lastNdx;) {
            min = (A->tree[min] < A->tree[min+1])? min : min+1; 
            minheap(A, &min, &sub);
        }
    }
}
void minheap(POT *A, int *min, int *sub) {
    *min = (A->tree[*sub] > A->tree[*min])? swap(&A->tree[*sub], &A->tree[*min]), *sub = *min, *min = *sub*2+1: A->lastNdx + 1;
}