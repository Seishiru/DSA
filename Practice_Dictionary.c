#include <stdio.h>
#include <string.h>

#define LIMIT_NAMING 20
#define MAX 20

typedef struct {
    char fn[LIMIT_NAMING];
    char ln[LIMIT_NAMING];
    char mi;
} details;

typedef struct {
    details name;
    char course[5];
    int year;
    unsigned long idNumber; //8 digits
} student;

typedef student Dictionary[MAX];
typedef enum { TRUE, FALSE } Boolean;
typedef int where;

//Initiaize - Initialize the list and set all to empty;
void init(Dictionary);
//Hash - Gets the idNumber last value
int hash(unsigned long idNumber);
//Display - Display the student record from the dictionary
void displayList(Dictionary);
//Insertion - Add a new student record to the dictionary.
void insertStudent(Dictionary list, student newStudent);
//Deletion - Remove a student record from the dictionary by their ID number.
void deleteStudent(Dictionary list, unsigned long idNumber);
//Search - Find and retrieve a student's record by their ID number.
student* searchStudent(Dictionary list, unsigned long idNumber);
//Update - Update the details of a student's record by their ID number.
void updateStudent(Dictionary list, unsigned long idNumber);
//Count - Count the number of students in the dictionary.
int countStudents(Dictionary list);
//Load - Load student records from a file into the dictionary.
void loadStudents(Dictionary list, const char* filename);
//Save - Save student records from the dictionary to a file.
void saveStudents(Dictionary list, const char* filename);

int main() {
    Dictionary list;
    init(list);
    student ns1;
    strcpy(ns1.course, "BSCS");
    ns1.idNumber = 22105000;
    strcpy(ns1.name.fn, "Cecil Raphael");
    strcpy(ns1.name.ln, "Quibranza");
    ns1.name.mi = 'S';
    ns1.year = 2;
    insertStudent(list, ns1);

    student ns2;
    strcpy(ns2.course, "BSIS");
    ns2.idNumber = 22105002;
    strcpy(ns2.name.fn, "Alice");
    strcpy(ns2.name.ln, "Smith");
    ns2.name.mi = 'B';
    ns2.year = 3;
    insertStudent(list, ns2);

    student ns3;
    strcpy(ns3.course, "BSCS");
    ns3.idNumber = 19104539;
    strcpy(ns3.name.fn, "John Arji");
    strcpy(ns3.name.ln, "Well");
    ns3.name.mi = '\0';
    ns3.year = 2;
    insertStudent(list, ns3);

    student ns4;
    strcpy(ns4.course, "BSEG");
    ns4.idNumber = 19305023;
    strcpy(ns4.name.fn, "Sasha Irith");
    strcpy(ns4.name.ln, "Viola");
    ns4.name.mi = 'A';
    ns4.year = 2;
    insertStudent(list, ns4);

    student ns5;
    strcpy(ns5.course, "BSCS");
    ns5.idNumber = 19019329;
    strcpy(ns5.name.fn, "Aether John");
    strcpy(ns5.name.ln, "Aeon");
    ns5.name.mi = 'C';
    ns5.year = 2;
    insertStudent(list, ns5);

    student ns;
    strcpy(ns.course, "BSIT");
    ns.idNumber = 18009529;
    strcpy(ns.name.fn, "Vodka Smith");
    strcpy(ns.name.ln, "Vladimor");
    ns.name.mi = 'S';
    ns.year = 2;
    
    deleteStudent(list, 22105000);
    deleteStudent(list, 22105001);
    

    insertStudent(list, ns1);
    

    unsigned long searchId = 22105000;
    student* foundStudent = searchStudent(list, searchId);

    if (foundStudent != NULL) {
        printf("Student found:\n");
        printf("First Name: %s\n", foundStudent->name.fn);
    } else {
        printf("Student with ID %lu not found.\n", searchId);
    }

    FILE *file;

    const char* filename = "data.txt"; // Replace with your desired filename
    saveStudents(list, filename); // Save the data to the file
    loadStudents(list, filename); // Load the data from the file

    
    // Display the list
    displayList(list);
    printf("count: %d\n", countStudents(list));
    return 0;
}


void init(Dictionary list) {
    where x = 0;
    for (; x < MAX; x++) {
        strncpy(list[x].course, "\0", sizeof(list[x].course));
        strncpy(list[x].name.fn, "\0", sizeof(list[x].name.fn));
        strncpy(list[x].name.ln, "\0", sizeof(list[x].name.ln));
        list[x].name.mi = '\0';
        list[x].idNumber = 0;
        list[x].year = 0;
    }
}
int hash(unsigned long idNumber) {
    // Use a simple modulo operation for simplicity
    return (int)(idNumber % 10);
}
void displayList(Dictionary list) {
    printf("\n\n-----------Student List-----------\n\n");
    where x = 0;
    for (; x < MAX; x++) {
        if(x > (MAX/2)-1){
            printf("%23s %d]\n", "[Student Synonym",x);
        }else{
            printf("%20s %d]\n", "[Student",x);
        }
        printf("First Name:   %20s\n", list[x].name.fn);
        printf("Last Name:    %20s\n", list[x].name.ln);
        printf("Middle Initial:%19c\n", list[x].name.mi);
        printf("Course:       %20s\n", list[x].course);
        printf("Year:         %20d\n", list[x].year);
        printf("ID Number:    %20lu\n", list[x].idNumber);
        if(strncmp(list[x].course, "\0", sizeof(list[x].course)) == 0){
            printf("This field are empty\n");
        }
        if(strncmp(list[x].course, "XXXX", sizeof(list[x].course)) == 0){
            printf("This field got deleted\n");
        }
        printf("\n\n");
    }
}
void insertStudent(Dictionary list, student newStudent) {
    int getHash = hash(newStudent.idNumber);

    if (strncmp(list[getHash].course, "\0", sizeof(list[getHash].course)) != 0) {
        // Collision occurred; find the next available slot
        where x = MAX / 2; // Start searching from the middle of the list

        for (; x < MAX; x++) {
            if (strncmp(list[x].course, "\0", sizeof(list[x].course)) == 0) {
                // Found an empty slot, insert the student here
                list[x] = newStudent;
                //printf("Inserted at index %d\n", x);
                return;
            }
        }
    } else {
        // No collision; insert the student in the original hash slot
        list[getHash] = newStudent;
    }
}
void deleteStudent(Dictionary list, unsigned long idNumber){
    int getHash = hash(idNumber);
    
    if (strncmp(list[getHash].course, "\0", sizeof(list[getHash].course)) == 0){
        //It means this field is empty and nothing to search begind with
        printf("Nothing to delete\n");
        return;
    }
    if (list[getHash].idNumber == idNumber){
        strncpy(list[getHash].course, "XXXX", sizeof(list[getHash].course));
        list[getHash].idNumber = 0;
        strncpy(list[getHash].name.fn, "XXXXXXXXX", sizeof(list[getHash].name.fn));
        strncpy(list[getHash].name.ln, "XXXXXXXXX", sizeof(list[getHash].name.ln));
        list[getHash].name.mi = 'X';
        list[getHash].year = -1;
    }else{
        where x = MAX / 2;
        for(;x < MAX; x++ ){
            if(list[x].idNumber == idNumber){
                strncpy(list[x].course, "XXXX", sizeof(list[x].course));
                list[x].idNumber = 0;
                strncpy(list[x].name.fn, "XXXXXXXXX", sizeof(list[x].name.fn));
                strncpy(list[x].name.ln, "XXXXXXXXX", sizeof(list[x].name.ln));
                list[x].name.mi = 'X';
                list[x].year = -1;

                return;
            }
        }
    }

}
student* searchStudent(Dictionary list, unsigned long idNumber) {
    int getHash = hash(idNumber);
    
    if (strncmp(list[getHash].course, "\0", sizeof(list[getHash].course)) == 0) {
        // It means this field is empty, and there's nothing to search for
        printf("Student not found\n");
        return NULL; // Return NULL to indicate that the student was not found
    }

    if (strncmp(list[getHash].course, "XXXX", sizeof(list[getHash].course)) == 0) {
        where x = MAX / 2;
        for (; x < MAX; x++) {
            //printf("x = %d\t", x);
            if (list[x].idNumber == idNumber) {
                return &list[x]; // Return a pointer to the found student
            }
        }
    }
    // If the loop completes without finding a match, the student is not in the dictionary
    printf("Student not found!!\n");
    return NULL;
}

void updateStudent(Dictionary list, unsigned long idNumber){
    int getHash = hash(idNumber);
    if (strncmp(list[getHash].course, "\0", sizeof(list[getHash].course)) == 0) {
        // It means this field is empty, and there's nothing to search for
        printf("Student not found\n");
        return;
    }
    if (strncmp(list[getHash].course, "XXXX", sizeof(list[getHash].course)) == 0) {
        where x = MAX / 2;
        for (; x < MAX; x++) {
            //printf("x = %d\t", x);
            if (list[x].idNumber == idNumber) {
                strncpy(list[x].course, "UPDA", sizeof(list[x].course));
                strncpy(list[x].name.fn, "UPDATED", sizeof(list[x].name.fn));
                strncpy(list[x].name.ln, "UPDATED", sizeof(list[x].name.ln));
                list[x].name.mi = 'U';
            }
        }
    }

}
int countStudents(Dictionary list){
    where x=0;
    int counter = 0;
    for(;x<MAX;x++){
        if(strncmp(list[x].course, "XXXX", sizeof(list[x].course) != 0 && strncmp(list[x].course, "\0", sizeof(list[x].course) != 0 ))){
            counter++;
        }
    }
    return counter;
}
void loadStudents(Dictionary list, const char* filename) {
    FILE *dataStudents;

    dataStudents = fopen(filename, "r"); // Open the file in read mode

    if (dataStudents == NULL) {
        puts("Error opening the file.");
        return;
    }

    // Read student data from the file and populate the Dictionary
    int x = 0;
    while (fread(&list[x], sizeof(student), 1, dataStudents)) {
        x++;
        if (x >= MAX) {
            printf("Maximum capacity reached. Some data may not be loaded.\n");
            break;
        }
    }

    fclose(dataStudents); // Close the file when done
}

void saveStudents(Dictionary list, const char* filename) {
    FILE* file = fopen(filename, "w"); // Open the file for writing

    if (file == NULL) {
        printf("Error opening the file '%s' for writing.\n", filename);
        return; // Handle the error as needed
    }

    where x = 0;
    for (; x < MAX; x++) {
        // Check if the slot is not empty and not marked as deleted
        if (strncmp(list[x].course, "XXXX", sizeof(list[x].course)) != 0 &&
            strncmp(list[x].course, "\0", sizeof(list[x].course)) != 0) {
            // Write the student record to the file
            fprintf(file, "%lu %s %s %c %s %d\n", list[x].idNumber, list[x].name.fn, list[x].name.ln,
                    list[x].name.mi, list[x].course, list[x].year);
        }
    }

    fclose(file); // Close the file when done
}