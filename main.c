#include <stdio.h>
#include <stdlib.h>
#include "student.h"

int main() {
    int choice;
    while (1) {
        printf("\n--- Student Management System ---\n");
        printf("1. Add Student\n");
        printf("2. View Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: 
                addStudent(); 
                break;
            case 2: 
                viewStudents(); 
                break;
            case 3: 
                searchStudent(); 
                break;
            case 4: 
                updateStudent(); 
                break;
            case 5: 
                deleteStudent(); 
                break;
            case 6: 
                exit(0);
            default: 
                printf("Invalid choice!\n");
        }
    }
    return 0;
}
