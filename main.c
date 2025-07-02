#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100

struct Student {
    int id;
    char name[50];
};

struct Student students[MAX];
int count = 0;

void loadFromFile();
void saveToFile();
void createStudent();
void readStudents();
void updateStudent();
void deleteStudent();

int main() {
    int choice;
    loadFromFile(); // Load data from file on start

    while (1) {
        printf("\n=== Student Information System ===\n");
        printf("1. Add Student\n");
        printf("2. View Students\n");
        printf("3. Update Student\n");
        printf("4. Delete Student\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar(); // consume newline

        switch (choice) {
            case 1: createStudent(); break;
            case 2: readStudents(); break;
            case 3: updateStudent(); break;
            case 4: deleteStudent(); break;
            case 5: saveToFile(); return 0;
            default: printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}

void loadFromFile() {
    FILE *file = fopen("students.txt", "r");
    if (file == NULL) return;

    count = 0;
    while (fscanf(file, "%d\n", &students[count].id) == 1) {
        fgets(students[count].name, sizeof(students[count].name), file);
        students[count].name[strcspn(students[count].name, "\n")] = 0; // Remove newline
        count++;
        if (count >= MAX) break;
    }

    fclose(file);
}

void saveToFile() {
    FILE *file = fopen("students.txt", "w");
    if (file == NULL) {
        printf("Error saving data.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%d\n%s\n", students[i].id, students[i].name);
    }

    fclose(file);
}

void createStudent() {
    if (count >= MAX) {
        printf("Student list full!\n");
        return;
    }

    printf("Enter Student ID: ");
    scanf("%d", &students[count].id);
    getchar(); // consume newline

    printf("Enter Student Name: ");
    fgets(students[count].name, sizeof(students[count].name), stdin);
    students[count].name[strcspn(students[count].name, "\n")] = 0; // Remove newline

    count++;
    saveToFile();
    printf("Student added successfully!\n");
}

void readStudents() {
    if (count == 0) {
        printf("No students to show.\n");
        return;
    }

    printf("\n--- Student List ---\n");
    for (int i = 0; i < count; i++) {
        printf("ID: %d | Name: %s\n", students[i].id, students[i].name);
    }
}

void updateStudent() {
    int id, found = 0;
    printf("Enter Student ID to update: ");
    scanf("%d", &id);
    getchar();

    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            printf("Enter new name: ");
            fgets(students[i].name, sizeof(students[i].name), stdin);
            students[i].name[strcspn(students[i].name, "\n")] = 0;

            saveToFile();
            printf("Student updated successfully!\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Student with ID %d not found.\n", id);
    }
}

void deleteStudent() {
    int id, found = 0;
    printf("Enter Student ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            for (int j = i; j < count - 1; j++) {
                students[j] = students[j + 1];
            }
            count--;
            saveToFile();
            printf("Student deleted successfully!\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Student with ID %d not found.\n", id);
    }
}

