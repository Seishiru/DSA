#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 10

typedef struct node {
    char elem;
    struct node* next;
} listype;

typedef listype* Dict[MAX]; 


void delete(Dict A, char let);
void insertSorted(Dict A, char let);
bool checkDuplicates(listype* current, char let);
void insert(Dict A, char let);
int hash(char character);
void display(Dict A);
void init(Dict A);

int main(){

    Dict A;
    init(A);
    insert(A, 'A');
    insert(A, '-');
    insert(A, '7');
    insert(A, 'A');
    insert(A, 'U');
    
    delete(A, 'K');
    delete(A, 'U');
    display(A);

    
    return 0;    
}

void init(Dict A) {
    for (int x = 0; x < MAX; x++) {
        A[x] = NULL; // Initialize each bucket to NULL
    }
}

void display(Dict A) {
    for (int x = 0; x < MAX; x++) {
        printf("Bucket %d:", x);
        listype* current = A[x]; // Start from the first element in the linked list
        while (current != NULL) {
            printf("(%c)", current->elem);
            printf(" -> ");
            if(current->next == NULL){
                printf("NULL");
            }
            current = current->next;
        }
        printf("\n");
    }
}

int hash(char character) {
    return character % MAX;
}

void insert(Dict A, char let) {
    int getHash = hash(let);
    listype* current = A[getHash];
    if (checkDuplicates(current, let) == true) {
        return;  // Duplicate found, do not insert
    }
    listype* newNode = malloc(sizeof(listype));
    if (newNode != NULL) {
        newNode->elem = let;
        newNode->next = A[getHash];
        A[getHash] = newNode;  // Add the new node to the beginning of the linked list
    }
}


bool checkDuplicates(listype* current, char let) {
    bool flag = false;
    while (current != NULL) {
        if (current->elem == let) {
            // Element already exists
            flag = true;
            break; // No need to continue searching once a duplicate is found
        }
        current = current->next;
    }
    return flag;
}

void insertSorted(Dict A, char let){
    int getHash = hash(let);
    listype* current = A[getHash];
    listype* previous = NULL;
    
    if(checkDuplicates(current, let) == true){
        return;
    }
    listype* newNode = malloc(sizeof(listype));
    if (newNode != NULL) {
        newNode->elem = let;

        while (current != NULL && let > current->elem) {
            previous = current;
            current = current->next;
        }
        // Insert 'let' between 'previous' and 'current'
        if (previous == NULL) {
            // 'let' should be the first element in the list
            newNode->next = A[getHash];
            A[getHash] = newNode;
        } else {
            newNode->next = current;
            previous->next = newNode;
        }
    }
}



void delete(Dict A, char let) {
    int getHash = hash(let);
    listype* current = A[getHash];
    listype* previous = NULL; // Initialize 'previous' to NULL
    if (current == NULL) {
        printf("Nothing to delete\n");
    } else {
        while (current != NULL && current->elem != let) {
            previous = current;
            current = current->next;
        }
        if (current != NULL) {
            if (previous == NULL) {
                // If we're deleting the first element in the list
                A[getHash] = current->next;
            } else {
                // For any other element in the list
                previous->next = current->next;
            }
            free(current);
        }
    }
}
