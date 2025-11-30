#include <stdio.h>
#include <string.h>

#define MAX 50
struct Student {
    char name[50];
    int roll;
    int marks[3];
    float percentage;
    char grade[3];
};
void calculate(struct Student *s) {
    int total = 0;
    int i;
    for (i = 0; i < 3; i++)
        total += s->marks[i];
    s->percentage = total / 3.0;

    if (s->percentage >= 90) strcpy(s->grade, "A+");
    else if (s->percentage >= 80) strcpy(s->grade, "A");
    else if (s->percentage >= 70) strcpy(s->grade, "B+");
    else if (s->percentage >= 60) strcpy(s->grade, "B");
    else if (s->percentage >= 50) strcpy(s->grade, "C");
    else strcpy(s->grade, "F");
}

void inputStudent(struct Student *s) {
    int i;
    printf("Enter name: ");
    scanf(" %[^\n]", s->name);
    printf("Enter roll number: ");
    scanf("%d", &s->roll);

    for (i = 0; i < 3; i++) {
        do {
            printf("Enter marks for subject %d (0-100): ", i+1);
            scanf("%d", &s->marks[i]);
            if (s->marks[i] < 0 || s->marks[i] > 100)
                printf("Invalid! Enter again.\n");
        } while (s->marks[i] < 0 || s->marks[i] > 100);
    }
    calculate(s);
}

void displayStudent(struct Student s) {
    printf("\nName: %s\nRoll: %d\nMarks: %d %d %d\nPercentage: %.2f\nGrade: %s\n",
           s.name, s.roll, s.marks[0], s.marks[1], s.marks[2], s.percentage, s.grade);
}
void findByGrade(struct Student students[], int n, char grade[]) {
    int i;
    printf("\nStudents with grade %s:\n", grade);
    for (i = 0; i < n; i++)
        if (strcmp(students[i].grade, grade) == 0)
            printf("%s (Roll %d) - %.2f%%\n", students[i].name, students[i].roll, students[i].percentage);
}

void searchStudent(struct Student students[], int n) {
    int choice, i;
    printf("\nSearch by: 1.Roll 2.Name : ");
    scanf("%d", &choice);

    if (choice == 1) {
        int r;
        printf("Enter roll number: ");
        scanf("%d", &r);
        for (i = 0; i < n; i++)
            if (students[i].roll == r) {
                displayStudent(students[i]);
                return;
            }
        printf("Student not found.\n");
    } else if (choice == 2) {
        char name[50];
        printf("Enter name: ");
        scanf(" %[^\n]", name);
        for (i = 0; i < n; i++)
            if (strcmp(students[i].name, name) == 0) {
                displayStudent(students[i]);
                return;
            }
        printf("Student not found.\n");
    } else {
        printf("Invalid choice.\n");
    }
}

void classAverage(struct Student students[], int n) {
    int i;
    float total = 0;
    for (i = 0; i < n; i++)
        total += students[i].percentage;
    float avg = total / n;
    printf("\nClass average: %.2f%%\n", avg);
    printf("Students above average:\n");
    for (i = 0; i < n; i++)
        if (students[i].percentage > avg)
            printf("%s - %.2f%%\n", students[i].name, students[i].percentage);
    printf("Students below average:\n");
    for (i = 0; i < n; i++)
        if (students[i].percentage < avg)
            printf("%s - %.2f%%\n", students[i].name, students[i].percentage);
}

void displayRanks(struct Student students[], int n) {
    int i, j;
    printf("\nStudent ranks:\n");
    for (i = 0; i < n; i++) {
        int rank = 1;
        for (j = 0; j < n; j++)
            if (students[j].percentage > students[i].percentage)
                rank++;
        printf("Rank %d: %s - %.2f%%\n", rank, students[i].name, students[i].percentage);
    }
}

int main() {
    struct Student students[MAX];
    int n, i;
    printf("Enter number of students: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("\n--- Student %d ---\n", i+1);
        inputStudent(&students[i]);
    }
    printf("\n--- All Students ---\n");
    for (i = 0; i < n; i++)
        displayStudent(students[i]);

    char grade[3];
    printf("\nEnter grade to search: ");
    scanf("%s", grade);
    findByGrade(students, n, grade);

    searchStudent(students, n);
    classAverage(students, n);
    displayRanks(students, n);

    return 0;
}

