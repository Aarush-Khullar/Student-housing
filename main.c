#include <stdio.h>
#include <stdlib.h>

#define MAX_STUDENTS 100

typedef struct Student {
    int id;
    char name[50];
    char university[100];
    char housingPref[100];
    int age;
} S;

S students[MAX_STUDENTS];
int studentCount = 0;

void addStudent() {

    if (studentCount >= MAX_STUDENTS) {
        printf("Cannot add more students. Maximum limit reached.\n");
        return;
    }

    S s;
    s.id = studentCount + 1;

    printf("Enter student name: ");
    scanf(" %[^\n]", s.name);

    printf("Enter university name: ");
    scanf(" %[^\n]", s.university);

    printf("Enter housing preference (single/shared/apartment): ");
    scanf(" %[^\n]", s.housingPref);

    printf("Enter age: ");
    scanf("%d", &s.age);

    students[studentCount] = s;
    studentCount++;

    printf("\nStudent added successfully! Assigned ID: %d\n", s.id);
}

void displayStudents() {
    if (studentCount == 0) {
        printf("No students added yet.\n");
        return;
    }

    printf("\nStudent List \n");
    // printf("ID\tName\t\tUniversity\t\tHousingPref\t\tAge\n");

    for (int i = 0; i < studentCount; i++) {
        printf("%d\t%s\t\t%s\t\t%s\t\t%d\n",
               students[i].id,
               students[i].name,
               students[i].university,
               students[i].housingPref,
               students[i].age);
    }
}
void searchStudent() {
    if (studentCount == 0) {
        printf("\nNo students to search.\n");
        return;
    }

    int id, found = 0;
    printf("\nEnter student ID to search: ");
    scanf("%d", &id);

    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            printf(" Student found:\n");
            printf("ID: %d\nName: %s\nUniversity: %s\nHousing: %s\nAge: %d\n",
                   students[i].id,
                   students[i].name,
                   students[i].university,
                   students[i].housingPref,
                   students[i].age);
            found = 1;
            break;
        }
    }

    if (found == 0) {
        printf("\n Student with ID %d not found.\n", id);
    }
}

void updateStudent() {
    if (studentCount == 0) {
        printf("\nNo students to update.\n");
        return;
    }

    int id, found = 0;
    printf("\nEnter student ID to update: ");
    scanf("%d", &id);

    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            found = 1;
            printf("\nEditing details for %s (ID: %d)\n", students[i].name, students[i].id);

            printf("Enter new name: ");
            scanf(" %[^\n]", students[i].name);

            printf("Enter new university: ");
            scanf(" %[^\n]", students[i].university);

            printf("Enter new housing preference: ");
            scanf(" %[^\n]", students[i].housingPref);

            printf("Enter new age: ");
            scanf("%d", &students[i].age);

            printf(" Student record updated successfully!\n");
            break;
        }
    }

    if (found == 0) 
    {
        printf(" Student with ID %d not found.\n", id);
    }
}
void deleteStudent() {
    if (studentCount == 0) {
        printf("\nNo students to delete.\n");
        return;
    }

    int id, found = 0;
    printf("\nEnter student ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            found = 1;
            for (int j = i; j < studentCount - 1; j++) {
                students[j] = students[j + 1];
            }

            studentCount--;

            printf("Student with ID %d deleted successfully.\n", id);
            break;
        }
    }
    if (found == 0) {
        printf("Student with ID %d not found.\n", id);
    }
}

int main() {
    int ch;
    while (1) {
        printf("1. Add Student\n");
        printf("2. View Students\n");
        printf("3. Exit\n");
        printf("4. Search student\n");
        printf("5. Update student info\n");
        printf("6. Delete student data\n");
        printf("\nEnter choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1:
                addStudent();
                break;
            case 2:
                displayStudents();
                break;
            case 3:
                exit(0);
            case 4:
                searchStudent();
                break;
            case 5:
                updateStudent();
                break;
            case 6:
                deleteStudent();
                break;
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}
