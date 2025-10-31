
#ifndef STUDENT_H
#define STUDENT_H

#define MAX_STUDENTS 100

typedef struct {
    int id;
    char name[50];
    char university[100];
    char housingPref[100];
    int age;
} Student;

void addStudent();
void viewStudents();
void searchStudent();
void updateStudent();
void deleteStudent();

#endif
