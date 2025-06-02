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

// Grade Calculation
char calculateGrade(float avg) {
    if (avg >= 90) return 'A';
    else if (avg >= 80) return 'B';
    else if (avg >= 70) return 'C';
    else if (avg >= 60) return 'D';
    else return 'F';
}

// Total, Average, Grade Calculate
void computeResult(struct Student *s) {
    s->total = 0;
    for (int i = 0; i < SUBJECTS; i++)
        s->total += s->marks[i];
    s->average = (float)s->total / SUBJECTS;
    s->grade = calculateGrade(s->average);
}

// Sorting by Total
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

// Display All Students
void displayAll(struct Student students[], int n) {
    printf("\nSorted Results:\n");
    printf("ID\tName\t\tTotal\tAverage\tGrade\n");
    for (int i = 0; i < n; i++) {
        printf("%s\t%s\t\t%d\t%.2f\t%c\n", students[i].id, students[i].name,
               students[i].total, students[i].average, students[i].grade);
    }
}

// Search by ID
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

// Update Marks
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

// File Writing
void saveToFile(struct Student students[], int n, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error opening file to save data.\n");
        return;
    }
    for (int i = 0; i < n; i++) {
        fprintf(fp, "%s %s ", students[i].id, students[i].name);
        for (int j = 0; j < SUBJECTS; j++)
            fprintf(fp, "%d ", students[i].marks[j]);
        fprintf(fp, "%d %.2f %c\n", students[i].total, students[i].average, students[i].grade);
    }
    fclose(fp);
}

// File Reading
int loadFromFile(struct Student students[], const char *filename) {
    FILE *fp = fopen(filename, "r");
    int n = 0;
    if (fp == NULL) {
        printf("No previous data found.\n");
        return 0;
    }
    while (fscanf(fp, "%s %s", students[n].id, students[n].name) != EOF) {
        for (int j = 0; j < SUBJECTS; j++)
            fscanf(fp, "%d", &students[n].marks[j]);
        fscanf(fp, "%d %f %c", &students[n].total, &students[n].average, &students[n].grade);
        n++;
    }
    fclose(fp);
    return n;
}

// Main Function
int main() {
    struct Student students[MAX];
    int n;
    char id[20];

    // Load existing data
    n = loadFromFile(students, "students.txt");

    int newCount;
    printf("Enter number of new students to add: ");
    scanf("%d", &newCount);

    // Input new data
    for (int i = n; i < n + newCount; i++) {
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

    n = n + newCount;
    sortStudents(students, n);
    displayAll(students, n);

    printf("\nEnter student ID to search: ");
    scanf("%s", id);
    searchStudent(students, n, id);

    printf("\nEnter student ID to update marks: ");
    scanf("%s", id);
    updateMarks(students, n, id);

    sortStudents(students, n);
    displayAll(students, n);

    // Save data to file
    saveToFile(students, n, "students.txt");

    return 0;
}
