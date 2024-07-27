#include <stdio.h>
#define MAX 20

int half = MAX / 2;

typedef struct {
    char elem;
    int next_cell;
} data;

typedef struct {
    data con[MAX];
    int avail_synonym;
} Dict;

void init(Dict *D);
void display(Dict D);
int hash(char letter);
void insert(Dict *D, char letter);
int search(Dict D, char letter);
void delete(Dict *D, char letter);

int main() {
    Dict D;
    init(&D);

    insert(&D, '#');
    insert(&D, '-');
    insert(&D, '7');
    insert(&D, 'A');
    insert(&D, 'K');
    insert(&D, '_');
    display(D);
    puts("-----------------------");

    delete(&D, '7');
    delete(&D, 'K');
   
    insert(&D, '=');

    // insert(&D, ')');
    // insert(&D, '3');
    // insert(&D, 'G');
    // insert(&D, 'Q');

    puts("-----------------------");
    

    

    display(D);
    return 0;
}

void init(Dict *D) {
    D->avail_synonym = half;
    for (int x = 0; x < half; x++) {
        D->con[x].elem = '\0';  //set to empty
        D->con[x].next_cell = -1; // Initialize the next_cell field, assuming -1 means no next cell
    }
    for(int x = half; x < MAX; x++){
        D->con[x].elem = ' ';
        D->con[x].next_cell = x + 1;    // this is not required actaully
    }
    D->con[MAX - 1].next_cell = -1;
}
void display(Dict D) {
    printf("\n\tDictionary Contents:\n");
    printf("AVAIL: %d\n",D.avail_synonym);
    printf("-----------------------------------\n");
    printf("| Element |    Elem   | Next Cell |\n");
    printf("|---------|-----------|-----------|\n");
    
    for (int x = 0; x < MAX; x++) {
        printf("|  %6d |     %c     |  %6d   |\n", x, D.con[x].elem, D.con[x].next_cell);
        if (x == half-1){
            printf("-----------------------------------\n");
            printf("| Element |    Elem   | Next Cell |\n");
            printf("|---------|-----------|-----------|\n");
        }
    }
}
int hash(char letter){
   // printf("Letter = %c %d\t", letter, letter % half);
    return letter % half;
}
void insert(Dict *D, char letter) {
    if (D->avail_synonym >= MAX) {
        printf("Dictionary is full. Cannot insert more elements.\n");
        return;
    }
    int getHash = hash(letter);
    int temp = D->con[getHash].next_cell;
    if (D->con[getHash].elem == '\0' || D->con[getHash].elem == ' ') {    // if it is empty then insert at prime.
        D->con[getHash].elem = letter;
    } else if (D->con[getHash].elem != '\0') {  // if prime has an occupied slot, insert at synonym
        D->con[D->avail_synonym].elem = letter;
        D->con[getHash].next_cell = D->avail_synonym;
        D->con[D->avail_synonym].next_cell = temp;
        D->avail_synonym++;
    }
}
int search(Dict D, char letter) {
    int getHash = hash(letter);

    if (D.con[getHash].elem == letter) {
        return getHash;
    } else if (D.con[getHash].elem != letter && D.con[getHash].elem != '\0') {
        int current = D.con[getHash].next_cell;
        while (current != -1) {
            if (D.con[current].elem == letter) {
                return current;
            }
            current = D.con[current].next_cell;
        }
    }
    return -1; // Return -1 to indicate that the letter was not found.
}
void delete(Dict *D, char letter) {
    if (letter == ' ' || letter == '\0'){
        printf("Cannot delete space or null character\n");
        return;
    }
    int getHash = hash(letter);
    if (D->con[getHash].elem == letter) { // If found in the primary slot
        D->con[getHash].elem = ' ';        // Set to space as deleted
        if(D->avail_synonym <= half){
            //puts("RUN 1");
            D->avail_synonym--;
        }
        // Do not set next_cell to -1 in the primary slot
    } else if (D->con[getHash].elem != letter) {
        int current = D->con[getHash].next_cell;
        int previous = getHash; // Use 'previous' to keep track of the previous index
        while (current != -1) {
            if (D->con[current].elem == letter) {
                D->con[previous].next_cell = D->con[current].next_cell;
                D->con[current].elem = ' ';
                if(D->avail_synonym >= half){
                    //puts("RUN 2");
                    D->avail_synonym--;
                }
                break;
            }
            previous = current;
            current = D->con[current].next_cell;
        }
    }
}

