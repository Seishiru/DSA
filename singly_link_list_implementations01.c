#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int elem;
    struct node *link;
}*nodePtr;

void insert(nodePtr *L, int data) {
    nodePtr temp = malloc(sizeof(struct node));
    if(temp != NULL) {
        temp->elem = data;
        temp->link = *L;
        *L = temp;
    }
}
// If you don't know what happend draw or use python tutor and replace the line 23 with this code comment below
// for(trav = L; 
//    *trav != NULL && (*trav)->elem != data; 
//     trav = &(*trav)->link) { }
void delete(nodePtr *L, int data) {
    nodePtr *trav;
    for(trav = L; *trav != NULL && (*trav)->elem != data; trav = &(*trav)->link) { }
    if(*trav != NULL) {
        nodePtr temp = *trav;
        *trav = (*trav)->link;
        free(temp);
    }
    
}

int main() {
    nodePtr L = NULL;
    insert(&L, 2);
    insert(&L, 5);
    insert(&L, 7);
    delete(&L, 5);
}
