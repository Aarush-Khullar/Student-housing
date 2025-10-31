#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

Student students[MAX_STUDENTS];
int studentCount = 0;

void addStudent() {
    if (studentCount >= MAX_STUDENTS) {
        printf("Cannot add more students.\n");
        return;
    }

    Student s;
    s.id = studentCount + 1;

    printf("Enter student name: ");
    scanf(" %[^\n]", s.name);
    printf("Enter university name: ");
    scanf(" %[^\n]", s.university);
    printf("Enter housing preference: ");
    scanf(" %[^\n]", s.housingPref);
    printf("Enter age: ");
    scanf("%d", &s.age);

    students[studentCount++] = s;
    printf("Student added successfully! ID = %d\n", s.id);
}

void viewStudents() {
    if (studentCount == 0) {
        printf("No students to display.\n");
        return;
    }

    // printf("\ID\tName\t\tUniversity\t\tHousing\t\tAge\n");
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
    int id;
    printf("Enter ID to search: ");
    scanf("%d", &id);

    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            printf("Student Found:\n");
            printf("Name: %s\nUniversity: %s\nHousing: %s\nAge: %d\n",
                   students[i].name,
                   students[i].university,
                   students[i].housingPref,
                   students[i].age);
            return;
        }
    }
    printf("Student not found!\n");
}

void updateStudent() {
    int id;
    printf("Enter ID to update: ");
    scanf("%d", &id);

    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            printf("Enter new name: ");
            scanf(" %[^\n]", students[i].name);
            printf("Enter new university: ");
            scanf(" %[^\n]", students[i].university);
            printf("Enter new housing preference: ");
            scanf(" %[^\n]", students[i].housingPref);
            printf("Enter new age: ");
            scanf("%d", &students[i].age);
            printf("Student updated successfully!\n");
            return;
        }
    }
    printf("Student not found!\n");
}

void deleteStudent() {
    int id;
    printf("Enter ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            for (int j = i; j < studentCount - 1; j++) {
                students[j] = students[j + 1];
            }
            studentCount--;
            printf("Student deleted successfully!\n");
            return;
        }
    }
    printf("Student not found!\n");
}
