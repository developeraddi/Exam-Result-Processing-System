#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define SUBJECTS 3

struct Student {
    char id[20];
    char name[50];
    int marks[SUBJECTS];
    int total;
    float average;
    char grade;
};

// Function to calculate grade
char calculateGrade(float avg) {
    if (avg >= 90) return 'A';
    else if (avg >= 80) return 'B';
    else if (avg >= 70) return 'C';
    else if (avg >= 60) return 'D';
    else return 'F';
}

// Function to calculate total, average, and grade
void computeResult(struct Student *s) {
    s->total = 0;
    for (int i = 0; i < SUBJECTS; i++)
        s->total += s->marks[i];
    s->average = (float)s->total / SUBJECTS;
    s->grade = calculateGrade(s->average);
}

// Function to sort students by total marks
void sortStudents(struct Student students[], int n) {
    struct Student temp;
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (students[j].total > students[i].total) {
                temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }
}

// Function to display all students
void displayAll(struct Student students[], int n) {
    printf("\nSorted Results:\n");
    printf("ID\tName\t\tTotal\tAverage\tGrade\n");
    for (int i = 0; i < n; i++) {
        printf("%s\t%s\t\t%d\t%.2f\t%c\n", students[i].id, students[i].name,
               students[i].total, students[i].average, students[i].grade);
    }
}

// Function to search by student ID
void searchStudent(struct Student students[], int n, char id[]) {
    int found = 0;
    for (int i = 0; i < n; i++) {
        if (strcmp(students[i].id, id) == 0) {
            printf("\nStudent Found:\n");
            printf("ID: %s\nName: %s\nTotal: %d\nAverage: %.2f\nGrade: %c\n",
                   students[i].id, students[i].name, students[i].total,
                   students[i].average, students[i].grade);
            found = 1;
            break;
        }
    }
    if (!found)
        printf("Student ID not found.\n");
}

// Function to update student marks
void updateMarks(struct Student students[], int n, char id[]) {
    int found = 0;
    for (int i = 0; i < n; i++) {
        if (strcmp(students[i].id, id) == 0) {
            printf("Enter new marks for 3 subjects:\n");
            for (int j = 0; j < SUBJECTS; j++) {
                printf("Subject %d: ", j + 1);
                scanf("%d", &students[i].marks[j]);
            }
            computeResult(&students[i]);
            printf("Marks updated successfully.\n");
            found = 1;
            break;
        }
    }
    if (!found)
        printf("Student ID not found.\n");
}

int main() {
    struct Student students[MAX];
    int n;
    char id[20];

    printf("Enter number of students: ");
    scanf("%d", &n);

    // Input data
    for (int i = 0; i < n; i++) {
        printf("\nEnter details for Student %d:\n", i + 1);
        printf("ID: ");
        scanf("%s", students[i].id);
        printf("Name: ");
        scanf("%s", students[i].name);
        for (int j = 0; j < SUBJECTS; j++) {
            printf("Marks for subject %d: ", j + 1);
            scanf("%d", &students[i].marks[j]);
        }
        computeResult(&students[i]);
    }

    // Sort and display
    sortStudents(students, n);
    displayAll(students, n);

    // Search by ID
    printf("\nEnter student ID to search: ");
    scanf("%s", id);
    searchStudent(students, n, id);

    // Update marks
    printf("\nEnter student ID to update marks: ");
    scanf("%s", id);
    updateMarks(students, n, id);

    // Display again
    sortStudents(students, n);
    displayAll(students, n);

    return 0;
}