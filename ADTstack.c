#include <stdio.h>
#include <stdlib.h>
#define MAX 5

// Array-based storage (not used in the current stack implementation)
typedef struct array {
    char elem[MAX];
    int index;
} storage;

// Node structure for linked list
typedef struct linklist {
    char elem;
    struct linklist *next;
} Node, *List;

/* Push an element onto the stack */
void push(List *L, char elem) {
    List temp = (List) malloc (sizeof(Node));
    if(temp != NULL) {
        temp->elem = elem;
        temp->next = *L;
        *L = temp;
    }

}
/* Pop an element from the stack */
char pop(List *L) {
    List temp = *L;
    char ret = '0';
    if(*L != NULL) {
        ret = temp->elem;
        *L = temp->next;
        free(temp);
    }
    return ret;
}
/* Top the top element of the stack */
char top(List L) {
    return (L != NULL) ? L->elem: '\0';
}
/* Display the elements of the stack */
void display(List L) {
    printf("\nStack: ");
    for(;L != NULL;) {
        printf("%-3c",pop(&L));
    }
}

void populate(List *L) {
    char elements[] = {'Z', 'G', 'O', 'N', 'K'};
    for (int i = 0; i < sizeof(elements) / sizeof(elements[0]); i++) {
        push(L, elements[i]);
    }
}


void arr_push(storage *stack, char elem) {
    if(stack->index < MAX) {
        stack->elem[++stack->index] = elem;
    }
}

void arr_pop(storage *stack) {
    if(stack->index != -1) {
        stack->index--;
    }
}

char arr_top(storage stack) {
    return stack.elem[stack.index];
}


storage arr_init() {
    storage ret;
    ret.index = -1;
    return ret;
}

/* Display the elements of the array-based stack */
void arr_display(storage stack) {
    printf("\nArray Stack: ");
    for(int i = 0; i <= stack.index; i++) {
        printf("%-3c", stack.elem[i]);
    }
}

int main() {
    // List stack = NULL; // Initialize the stack
    // populate(&stack);
    // display(stack);
    /*Array*/

    storage arr_stack;
    arr_stack = arr_init();

    arr_push(&arr_stack, 'D');
    arr_push(&arr_stack, 'S');
    arr_push(&arr_stack, 'A');
    arr_push(&arr_stack, 'O');
    arr_display(arr_stack);
    printf("\n%-4c", arr_top(arr_stack));
    arr_pop(&arr_stack);
    arr_display(arr_stack);
    printf("\n%-4c", arr_top(arr_stack));

    return 0;
}
/*Note: I did not do the link-list stack because I notice that there wasn't any difference between a basic link-list and a stack.
  Although I forgot what I was doing for this code but hope this helps.*/