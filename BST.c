#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int elem;
    struct node *left;
    struct node *right;
}*nodePtr;

void insert(nodePtr *A, int elem);
void deleteElem(nodePtr *A, int elem);
void displayInOrder(nodePtr A);

int main() {
    nodePtr A = NULL;

    insert(&A, 100); 
    insert(&A, 50);
    insert(&A, 150);
    insert(&A, 25);
    insert(&A, 75);
    insert(&A, 125);
    insert(&A, 175);
    insert(&A, 15);
    insert(&A, 30);
    insert(&A, 60);
    insert(&A, 90);
    insert(&A, 110);
    insert(&A, 140);
    insert(&A, 160);
    insert(&A, 190);
    displayInOrder(A);
    deleteElem(&A, 50);
    deleteElem(&A, 1000);
    printf("\n----\n");
    displayInOrder(A);
    return 0;
}

void insert(nodePtr *A, int elem) {
    if(*A != NULL && (*A)->elem >= elem) {
        insert(&(*A)->left, elem);
    } else if (*A != NULL && (*A)->elem < elem) {
        insert(&(*A)->right, elem);
    } else {
        nodePtr temp = (nodePtr) malloc(sizeof(struct node));
        if(temp != NULL) {
            temp->elem = elem;
            temp->left = temp->right = NULL;
        *A = temp;
        }
    }
}
void deleteElem(nodePtr *A, int elem) {
    /* trav will be the pointer-to-pointer-to-node and will get the address of either left or right child as it traverses, otherwise it will get the address of the pointer which is the 'A'. As soon as it finds the PPN is NULL or the elem that is looking for is true then the loops stop */
    nodePtr *trav;
    for (trav = A; *trav != NULL && (*trav)->elem != elem; trav = ((*trav)->elem < elem) ? &(*trav)->right : &(*trav)->left) { }
    /* value of node_temp will get the trav that would be the where the value of elem is located. */
    nodePtr node_temp = *trav;
    /* value of trav will get the 4 posiblibilities outcome. 1. NULL. 2. node_temp->left. 3. node_temp->right 4. *trav */
     *trav = ((node_temp == NULL || node_temp->right == NULL && node_temp->left == NULL) ? NULL : ((node_temp->right == NULL) ? node_temp->left : ((node_temp->left == NULL) ? node_temp->right : *trav)));
    /* jf the A is not originally empty and if the parent has both child*/
    if (node_temp != NULL && node_temp->right != NULL && node_temp->left != NULL) {
        nodePtr minRight;
    /* if the parent has both child then the minimum node would be the right child. otherwise the node will be the left child  only if the left child exist*/
        for (minRight = node_temp->right; minRight->left != NULL; minRight = minRight->left) { }
    /* swaping the parent with the minimym child */
        node_temp->elem = minRight->elem;
    /* Calls the function again to repeat the process, will only stop when it finally frees*/
        deleteElem(&node_temp->right, minRight->elem);
        return;
    }
    /* Free the memory allocated for the node to delete and exits the function */
    free(node_temp);
}

void displayInOrder(nodePtr A) {
  if (A != NULL) {
    displayInOrder(A->left);
    printf("%d ", A->elem); 
    displayInOrder(A->right); 
  }
}
