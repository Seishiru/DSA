#include <stdio.h>
#include <stdlib.h>
#define MAX 5

// Array-based storage (not used in the current queue implementation)
typedef struct array {
    char elem[MAX];
    int count;
} storage;

// Node structure for linked list
typedef struct node {
    char elem;
    struct node *next;
} Node, *List;

// Queue structure using linked list
typedef struct queue {
    List front;
    List rear;
} Queue;

// Initialization function for the queue
List initialization(Queue *Q) {
    Q->front = Q->rear = NULL;
    return (List) NULL;
}

/* Insert an element at the rear (end) of the queue */
void enqueue(Queue *Q, char elem) {
    List temp = (List)malloc(sizeof(Node));
    if (temp != NULL) {
        temp->elem = elem;
        temp->next = NULL;
        if(Q->rear == NULL) {
            Q->front = temp;
        } else {
            Q->rear->next = temp;
        }
        Q->rear = temp;
    }
}

/* Remove an element from the front (beginning) of the queue */
char dequeue(Queue *Q) {
    List temp;
    temp = Q->front;
    char letter = Q->front->elem;
    Q->front = Q->front->next;
    free(temp);
    return letter;

}

/* Peek the front element of the queue */
char peek(Queue Q) {
    return (char) Q.front->elem;
}

/* Check if the queue is empty */
char isEmpty(Queue *Q) {
  
}

/* Display the elements of the queue */
void display(Queue Q) {
    if (Q.front == NULL) {
        printf("\ndata is empty\n");
    } else {
        for (;Q.front != NULL;  Q.front = Q.front->next) {
            printf("%c", Q.front->elem);
            if(Q.front->next != NULL) {
                printf(" -> ");
            }
        }
        printf("\n");
    }
}

/* Populate the queue with some elements */
void populate(Queue *Q) {
    char elements[] = {
        'Z', 'G', 'O', 'N',
        'K'
    };
    for (int i = 0; i < sizeof(elements) / sizeof(elements[0]); i++) {
        enqueue(Q, elements[i]);
    }
}

void arr_enqueue(storage *Q) {
    
}

int main() {
    // Queue Q;
    // initialization(&Q);
    // populate(&Q);
    // display(Q);
    // printf("Dequeue element: %c\n", dequeue(&Q));
    // display(Q);
    // printf("Peek front element: %c\n", peek(Q));
    // display(Q);


    return 0;
}
