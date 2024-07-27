#include <stdio.h>
#include <stdbool.h>
#define MAX 10

typedef struct Queue{
    char elem[MAX];
    int front;
    int rear;
}Queue;

void init(Queue *CA) {
    CA->front = 0;
    CA->rear = MAX - 1;
}

bool isEmpty(Queue CA) {
    return ((CA.rear + 1) % MAX == CA.front)? true: false; 
}

bool isFull(Queue CA) {
    return ((CA.rear + 2) % MAX == CA.front)? true: false;
}

void queue(Queue *CA, char elem) {
    if(!isFull(*CA)) {
        CA->elem[(CA->rear = (CA->rear + 1) % MAX)] = elem;
    } else {
        printf("\nQueue is full");
    }
}

void display(Queue CA) {
    printf("\nfront: %d\nrear: %d\n\n", CA.front, CA.rear);
    if (isEmpty(CA) != true) {
        for (int x = CA.front; x != (CA.rear + 1) % MAX; x = (x + 1) % MAX) {
            printf("%-3c", CA.elem[x]);
        }
        printf("\n");
        for (int x = CA.front; x != (CA.rear + 1) % MAX; x = (x + 1) % MAX) {
            printf("%-3d", x);
        }
    } else  {
        printf("[Queue is empty.]\n");
    }
}

void dequeue(Queue *CA) {
    if(isEmpty(*CA) != true) {
        CA->front = (CA->front + 1) % MAX;
    }
}

int main() {
    Queue CA;
    init(&CA);
    display(CA);
    queue(&CA, 'A');
    queue(&CA, 'B');
    queue(&CA, 'C');
    queue(&CA, 'D');
    queue(&CA, 'E');

    queue(&CA, 'F');
    queue(&CA, 'G');
    queue(&CA, 'H');
    queue(&CA, 'I');
    dequeue(&CA);
    dequeue(&CA);
    dequeue(&CA);
    dequeue(&CA);
    dequeue(&CA);
    dequeue(&CA);
    dequeue(&CA);
    dequeue(&CA);
    dequeue(&CA);
    dequeue(&CA);
    queue(&CA, 'J');
    queue(&CA, 'K');
    // queue(&CA, 'L');
    display(CA);


    return 0;
}