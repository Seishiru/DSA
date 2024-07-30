#include <stdio.h>
#define MAX 15

typedef struct {
    int elem;
    int left;
    int right;
}node;

typedef struct {
    node tree[MAX];
    int avail;
}BST_CB;

typedef int SET;

void initialize(BST_CB *A);
void display(BST_CB A);
void insert(BST_CB *A, SET *a, int elem);
void inOrder(BST_CB A, SET a);
void delete(BST_CB *A, SET *a, int elem);

int main() {
    BST_CB A;
    SET a = -1;
    initialize(&A);
    display(A);
    printf("Inserting...\n");
    insert(&A, &a, 100);

    insert(&A, &a, 50);
    insert(&A, &a, 150);

    insert(&A, &a, 25);
    insert(&A, &a, 75);
    insert(&A, &a, 125);
    insert(&A, &a, 175);

    insert(&A, &a, 10);
    insert(&A, &a, 30);
    insert(&A, &a, 60);
    insert(&A, &a, 90);
    insert(&A, &a, 110);
    insert(&A, &a, 140);
    insert(&A, &a, 160);
    insert(&A, &a, 190);

    display(A);
    printf("Inorder traversal: ");
    inOrder(A, a);
    printf("\nDeleting...\n");
    delete(&A, &a, 190);    
    delete(&A, &a, 175);
    delete(&A, &a, 50);

    printf("[SET a: %d]\n", a);
    display(A);

}
void initialize(BST_CB *A) {
    int x;
    for(x = 0; x < MAX; x++) {
        A->tree[x].elem = -1;
        A->tree[x].left = -1;
        A->tree[x].right = x - 1;
    }
    A->avail = MAX-1;
}
void display(BST_CB A) {
    int x;
    printf("\n-----------------------------------------\n%-8s %-12s %-12s %-12s\n", "index", "left", "elem", "right");
    for(x = 0; x < MAX; x++) {
        printf("%-8d %-12d %-12d %-12d\n", x, A.tree[x].left, A.tree[x].elem, A.tree[x].right);
    }
    printf("Avail: %d\n-----------------------------------------\n", A.avail);
    system("pause");
}
void insert(BST_CB *A, SET *a, int elem) {
    SET *trav;
    if (A->avail == -1) {
       printf("No more space to insert %d\n", elem); 
    } else {
        for(trav = a; *trav != -1 && A->tree[*trav].elem != elem; trav =(A->tree[*trav].elem > elem)? &A->tree[*trav].left: &A->tree[*trav].right) { }
        if(*trav == -1) {
            int getSpace = A->avail;
            A->avail = A->tree[getSpace].right;
            A->tree[getSpace].elem = elem;
            A->tree[getSpace].left = -1;
            A->tree[getSpace].right = -1; 
            *trav = getSpace;
            printf("Successful insert with %d\n", elem);
        } else {
            printf("Element already exist %d\n", elem);
        }
    }    
}
void inOrder(BST_CB A, SET a) {
    if(a != -1) {
        inOrder(A, A.tree[a].left);
        printf("%d ", A.tree[a].elem);
        inOrder(A, A.tree[a].right);
    }
}
void delete(BST_CB *A, SET *a, int elem) {
    if(*a == -1) {
        printf("Set is empty\n");
    } else {
        int *trav;
        for(trav = a; *trav != -1 && A->tree[*trav].elem != elem; trav = (A->tree[*trav].elem < elem)? &A->tree[*trav].right : &A->tree[*trav].left) { }
        if(*trav != -1) {
            int node_temp = *trav;

            //case 1: no child left
            if(A->tree[*trav].left == -1) {
                printf("\n[case 1 triggered]\n");
                A->tree[*trav].elem = -1;
                A->tree[node_temp].right = A->avail;
                A->avail = node_temp;
                *trav = -1;
            //case 2: no child right
            } else if (A->tree[*trav].right == -1) {
                printf("\n[case 2 triggered]\n");
                *trav = (A->tree[*trav].left != -1)? A->tree[*trav].left: A->tree[*trav].right;
                A->tree[*trav].elem = -1;
                A->tree[node_temp].left = -1;
                A->tree[node_temp].right = A->avail;
                A->avail = node_temp;
            //case 3: 2 childs
            } else  {
                printf("\n[case 3 triggered]\n");
                int *min;
                for(min = &A->tree[*trav].right ; A->tree[*min].left != -1; min = &A->tree[*min].left) { }
                A->tree[*trav].elem = A->tree[*min].elem;
                A->tree[*min].elem = -1;
                A->tree[*min].right = A->avail;
                A->avail = *min;
                *min = -1;
            }
            printf("Element deleted successfully %d\n", elem);
        } else {
            printf("Element not found %d\n", elem);
        }
        
    }
}
