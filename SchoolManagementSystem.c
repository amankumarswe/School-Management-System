#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student {
    char name[50];
    int roll;
    char course[30];
    char section[2]; 
    int session;    
    float course_fee;
};
int num_students;

    

void insert(struct student *s, int n) {
    FILE *fp;
    fp = fopen("personaldetail.txt", "w");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }
    // Prompt user to input number of students to insert
    printf("Enter number of students to insert: ");
    scanf("%d", &n);

    // Adjust memory allocation based on user input
    s = (struct student *)malloc(n * sizeof(struct student));
    if (s == NULL) {
        printf("Memory allocation failed.\n");
        fclose(fp);
        return;
    }

    for (int i = 0; i < n; i++) {
        printf("Enter details for student %d:\n", i + 1);
        printf("Name: ");
        scanf("%s", s[i].name);
        printf("Roll Number: ");
        scanf("%d", &s[i].roll);
        printf("Course: ");
        scanf("%s", s[i].course);
        printf("Section: ");
        scanf(" %c", &s[i].section[0]);
        s[i].section[1] = '\0'; // Null-terminate the section string
        printf("Session: ");
        scanf("%d", &s[i].session);
        printf("Course Fee: ");
        scanf("%f", &s[i].course_fee);
        // Write to file
        fprintf(fp, "%s %d %s %c %d %.2f\n", s[i].name, s[i].roll, s[i].course, s[i].section[0], s[i].session, s[i].course_fee);
    }
    fclose(fp); // Close file after writing
}

void update(struct student *s, int n) {
    FILE *fp;
    fp = fopen("personaldetail.txt", "r+");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    int roll_to_update;
    printf("Enter Roll Number to update: ");
    scanf("%d", &roll_to_update);

    // Buffer to store each line read from file
    char buffer[200];
    int found = 0;

    // Read each line from the file
    while (fgets(buffer, sizeof(buffer), fp)) {
        int file_roll;
        sscanf(buffer, "%s %d %s %c %d %f", s->name, &file_roll, s->course, &s->section[0], &s->session, &s->course_fee);
        
        // Compare roll numbers
        if (file_roll == roll_to_update) {
            found = 1; 
            // Print current details
            printf("Current Details:\n");
            printf("Name: %s\n", s->name);
            printf("Roll Number: %d\n", file_roll);
            printf("Course: %s\n", s->course);
            printf("Section: %c\n", s->section[0]);
            printf("Session: %d\n", s->session);
            printf("Course Fee: %.2f\n", s->course_fee);
            // Prompt for updated details
            printf("\nEnter updated details:\n");
            printf("Name: ");
            scanf("%s", s->name);
            printf("Course: ");
            scanf("%s", s->course);
            printf("Section: ");
            scanf(" %c", &s->section[0]);
            printf("Session: ");
            scanf("%d", &s->session);
            printf("Course Fee: ");
            scanf("%f", &s->course_fee);
            // Move file pointer back to the beginning of the current line
            fseek(fp, -strlen(buffer), SEEK_CUR);
            
            // Write updated details to file
            fprintf(fp, "%s %d %s %c %d %.2f\n", s->name, file_roll, s->course,
            s->section[0], s->session, s->course_fee); 
            // Break out of loop since update is done
            break;
        }
    }

    if (!found) {
        printf("Student with Roll Number %d not found.\n", roll_to_update);
    }

    fclose(fp); // Close file after reading and writing
}

void delete(struct student *s, int n) {
    FILE *fp;
    fp = fopen("personaldetail.txt", "r+");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }
    int roll_to_delete;
    printf("Enter Roll Number to delete: ");
    scanf("%d", &roll_to_delete);
    // Buffer to store each line read from file
    char buffer[200];
    int found = 0;
    // Temporary file to store non-deleted records
    FILE *temp_fp = fopen("temp.txt", "w"); 
    // Read each line from the file
    while (fgets(buffer, sizeof(buffer), fp)) {
        int file_roll;
        sscanf(buffer, "%s %d %s %c %d %f", s->name, &file_roll,
        s->course, &s->section[0], &s->session, &s->course_fee);
        
        // Compare roll numbers
        if (file_roll == roll_to_delete) {
            found = 1;
            continue;
     // Skip writing this line to temp file (effectively deleting it)
        }

        // Write non-deleted records to temporary file
        fprintf(temp_fp, "%s %d %s %c %d %.2f\n", s->name, file_roll,
         s->course, s->section[0], s->session, s->course_fee);
    }

    fclose(fp); // Close original file
    fclose(temp_fp); // Close temporary file

    // Remove the original file
    remove("personaldetail.txt");
    // Rename the temporary file to original file name
    rename("temp.txt", "personaldetail.txt");
}
void display(struct student *s, int num_students) {
    FILE *fp;
    fp = fopen("personaldetail.txt", "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("Student Details:\n");
    printf("--------------------------------------------------\n");
    printf("Name\tRoll\tCourse\tSection\tSession\tFee\n");
    printf("--------------------------------------------------\n");

    // Read and display each student's details from file
    while (fscanf(fp, "%s %d %s %c %d %f", s->name, &s->roll, s->course,
     &s->section[0], &s->session, &s->course_fee) != EOF)
      {
        printf("%s\t%d\t%s\t%c\t%d\t%.2f\n", s->name, s->roll, s->course,
         s->section[0], s->session, s->course_fee);
    }
    fclose(fp); // Close file after reading
}
int main() {
    int choice;
    // Dynamically allocate memory for students
    struct student *Students = 
    (struct student *)malloc(num_students * sizeof(struct student));
    if (Students == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }
    printf("Press 1 to Insert Data\n");
    printf("Press 2 to Update existing data\n");
    printf("Press 3 to Delete existing data\n");
    printf("Press 4 to View existing data\n");
    printf("Press 5 to Exit the program \n");

    printf("Enter your choice: ");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            insert(Students, num_students);
            break;
        case 2:
            update(Students, num_students);
            break;
        case 3:
            delete(Students, num_students);
            break;
        case 4:
                display(Students, num_students);
                break;
            case 5:
                printf("Exiting program.\n");
                break;
        default:
            printf("Invalid choice!\n");
    }

    // Free dynamically allocated memory
    free(Students);

    return 0;
}

