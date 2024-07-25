#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define VH_SIZE 0XC

typedef char string[0XF];
typedef int list;
typedef struct {
    string elem;
    int next;
}node;

typedef struct {
    node space[VH_SIZE];
    int avail;
}VisualHeap;

typedef struct node {
    string elem;
    struct node *link;
}*nodePtr;

void insert(nodePtr *L, string data);
nodePtr populateLL();
void displayLL(nodePtr LL);
void initvs(VisualHeap *vs);
void displayCB(VisualHeap vs, list G);
int allocSpace(VisualHeap *vs);
void CBinsertSorted(VisualHeap *vs, list *G, string data);
void populateCB(VisualHeap *vs, list *G,nodePtr *LL);

int main() {
    nodePtr LL = NULL;
    VisualHeap vs;
    list G = -1;
    
    LL = populateLL();

    // [1 Call initvs and displayCB]
    initvs(&vs);
    displayCB(vs, G);
    // [3 Call the populateCB and displayCB]
    populateCB(&vs, &G, &LL);
    displayCB(vs, G);

}



void insert(nodePtr *L, string data) {
    nodePtr temp = malloc(sizeof(struct node));
    if(temp != NULL) {
        strcpy(temp->elem, data);
        temp->link = *L;
        *L = temp;
    }
}
nodePtr populateLL() {
    nodePtr retLL = NULL;
    const int COUNT = 15;
    string datas[] = {
                       "Starlingia", "Crystalite", "Aventorion", "Halcyonize", "Lucentoria", 
                       "Radiantium", "Glimmerine", "Celestonic", "Brilliance", "Luminarion", 
                       "Spectravia", "Verdancia", "Seraphicor", "Mythoriana", "Etherealix", 
                     };
    int x;
    for(x = 0; x < COUNT; x++) {
        insert(&retLL, datas[x]);
    }
    return retLL;
}
void displayLL(nodePtr LL) {
    printf("[List of names]\n");
    for(;LL != NULL; LL = LL->link) printf("%s\n", LL->elem);
}
void initvs(VisualHeap *vs) {
    // [2] Provide the code below
    int x;
    for(x = 0; x < VH_SIZE; x++) {
        vs->space[x].next = x - 1;
        strcpy(vs->space[x].elem, "  ");
    }
    vs->avail = x-1;
}
void displayCB(VisualHeap vs, list G) {
    int x;
    printf("%15s | %15s | %15s\n", "INDEX", "ELEM", "NEXT");
    for(x=0; x<VH_SIZE; x++){
        printf("%15d | %15s | %15d\n", x, vs.space[x].elem, vs.space[x].next);
    }
    printf("Available: %d Index\n", vs.avail);
    printf("List: %d\n",G);
}
int allocSpace(VisualHeap *vs) {
    // [6] Provide the code below
    int avail = vs->avail;
    if(avail != -1){
        vs->avail = vs->space[avail].next;
    }
    return avail;
}
void CBinsertSorted(VisualHeap *vs, list *G, string data) {
    // [5] Provide the code below
    if (vs->avail != -1) {
		int *x;
		for(x = G; *x != -1 && strcmp(vs->space[*x].elem, data) < 0; x = &vs->space[*x].next) { }
        int getSpace = allocSpace(vs);
        if(getSpace != -1) {
            strcpy(vs->space[getSpace].elem, data);
            vs->space[getSpace].next = *x;
            *x = getSpace;
		}
	} else {
		printf("No available space. Person with name: %s cannot be inserted.\n", data);
	}
}
void populateCB(VisualHeap *vs, list *G,nodePtr *LL) {
    nodePtr trav;
    for(trav = *LL; trav != NULL; trav = trav->link) {
        // [4 Provide the code below]
        nodePtr temp = trav;
        CBinsertSorted(vs, G, temp->elem);
        free(temp);
    }
}