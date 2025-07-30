#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "students.dat"

typedef struct {
    int roll;
    char name[50];
    float marks;
} Student;

void addStudent() {
    FILE *fp = fopen(FILENAME, "ab");
    Student s;
    printf("Enter Roll: ");
    scanf("%d", &s.roll);
    printf("Enter Name: ");
    scanf(" %[^\n]s", s.name);
    printf("Enter Marks: ");
    scanf("%f", &s.marks);
    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);
    printf("Student added!\n");
}

void displayAll() {
    FILE *fp = fopen(FILENAME, "rb");
    Student s;
    printf("\nRoll\tName\t\tMarks\n");
    printf("-----------------------------\n");
    while(fread(&s, sizeof(s), 1, fp) == 1) {
        printf("%d\t%-15s%.2f\n", s.roll, s.name, s.marks);
    }
    fclose(fp);
}

void searchStudent() {
    FILE *fp = fopen(FILENAME, "rb");
    Student s;
    int target, found = 0;
    printf("Enter roll no. to search: ");
    scanf("%d", &target);
    while(fread(&s, sizeof(s), 1, fp) == 1) {
        if(s.roll == target) {
            printf("Found: %d %s %.2f\n", s.roll, s.name, s.marks);
            found = 1;
            break;
        }
    }
    if (!found) printf("Not found!\n");
    fclose(fp);
}

void deleteStudent() {
    FILE *fp = fopen(FILENAME, "rb");
    FILE *temp = fopen("temp.dat", "wb");
    Student s;
    int target, found = 0;
    printf("Enter roll no. to delete: ");
    scanf("%d", &target);
    while(fread(&s, sizeof(s), 1, fp) == 1) {
        if(s.roll != target) {
            fwrite(&s, sizeof(s), 1, temp);
        } else {
            found = 1;
        }
    }
    fclose(fp);
    fclose(temp);
    remove(FILENAME);
    rename("temp.dat", FILENAME);
    if (found)
        printf("Deleted!\n");
    else
        printf("Record not found.\n");
}

int main() {
    int choice;
    do {
        printf("\n--- Student Record Management ---\n");
        printf("1. Add Student\n2. Display All\n3. Search\n4. Delete\n0. Exit\nChoice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1: addStudent(); break;
            case 2: displayAll(); break;
            case 3: searchStudent(); break;
            case 4: deleteStudent(); break;
            case 0: printf("Exiting.\n"); break;
            default: printf("Invalid!\n");
        }
    } while(choice != 0);
    return 0;
}
