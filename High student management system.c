#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student
{
    int rollno;
    char name[50];
    int age;
    char course[30];
    float marks;
};

void addStudent()
{
    struct Student s;
    FILE *fp;

    fp = fopen("students.dat", "ab");

    if(fp == NULL)
    {
        printf("File cannot be opened.\n");
        return;
    }

    printf("\nEnter Roll Number: ");
    scanf("%d", &s.rollno);

    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);

    printf("Enter Age: ");
    scanf("%d", &s.age);

    printf("Enter Course: ");
    scanf(" %[^\n]", s.course);

    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);

    printf("\nStudent added successfully.\n");
}

void displayStudents()
{
    struct Student s;
    FILE *fp;

    fp = fopen("students.dat", "rb");

    if(fp == NULL)
    {
        printf("\nNo records found.\n");
        return;
    }

    printf("\n----- Student Records -----\n");

    while(fread(&s, sizeof(s), 1, fp) == 1)
    {
        printf("\nRoll Number : %d", s.rollno);
        printf("\nName        : %s", s.name);
        printf("\nAge         : %d", s.age);
        printf("\nCourse      : %s", s.course);
        printf("\nMarks       : %.2f\n", s.marks);
    }

    fclose(fp);
}

void searchStudent()
{
    struct Student s;
    FILE *fp;
    int rollno, found = 0;

    fp = fopen("students.dat", "rb");

    if(fp == NULL)
    {
        printf("\nNo records found.\n");
        return;
    }

    printf("\nEnter Roll Number to search: ");
    scanf("%d", &rollno);

    while(fread(&s, sizeof(s), 1, fp) == 1)
    {
        if(s.rollno == rollno)
        {
            printf("\nStudent Found!");
            printf("\nRoll Number : %d", s.rollno);
            printf("\nName        : %s", s.name);
            printf("\nAge         : %d", s.age);
            printf("\nCourse      : %s", s.course);
            printf("\nMarks       : %.2f\n", s.marks);

            found = 1;
            break;
        }
    }

    if(!found)
        printf("\nStudent not found.\n");

    fclose(fp);
}

void deleteStudent()
{
    struct Student s;
    FILE *fp, *temp;
    int rollno, found = 0;

    fp = fopen("students.dat", "rb");
    temp = fopen("temp.dat", "wb");

    if(fp == NULL)
    {
        printf("\nNo records found.\n");
        return;
    }

    printf("\nEnter Roll Number to delete: ");
    scanf("%d", &rollno);

    while(fread(&s, sizeof(s), 1, fp) == 1)
    {
        if(s.rollno == rollno)
        {
            found = 1;
        }
        else
        {
            fwrite(&s, sizeof(s), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if(found)
        printf("\nStudent deleted successfully.\n");
    else
        printf("\nStudent not found.\n");
}

void updateStudent()
{
    struct Student s;
    FILE *fp;
    int rollno, found = 0;

    fp = fopen("students.dat", "rb+");

    if(fp == NULL)
    {
        printf("\nNo records found.\n");
        return;
    }

    printf("\nEnter Roll Number to update: ");
    scanf("%d", &rollno);

    while(fread(&s, sizeof(s), 1, fp) == 1)
    {
        if(s.rollno == rollno)
        {
            printf("\nEnter New Name: ");
            scanf(" %[^\n]", s.name);

            printf("Enter New Age: ");
            scanf("%d", &s.age);

            printf("Enter New Course: ");
            scanf(" %[^\n]", s.course);

            printf("Enter New Marks: ");
            scanf("%f", &s.marks);

            fseek(fp, -sizeof(s), SEEK_CUR);
            fwrite(&s, sizeof(s), 1, fp);

            found = 1;
            break;
        }
    }

    fclose(fp);

    if(found)
        printf("\nStudent updated successfully.\n");
    else
        printf("\nStudent not found.\n");
}

int main()
{
    int choice;

    do
    {
        printf("\n\n===== STUDENT MANAGEMENT SYSTEM =====");
        printf("\n1. Add Student");
        printf("\n2. Delete Student");
        printf("\n3. Search Student");
        printf("\n4. Update Student");
        printf("\n5. Display All Students");
        printf("\n6. Exit");

        printf("\n\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                addStudent();
                break;

            case 2:
                deleteStudent();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                updateStudent();
                break;

            case 5:
                displayStudents();
                break;

            case 6:
                printf("\nExiting program...");
                break;

            default:
                printf("\nInvalid choice. Please try again.");
        }

    } while(choice != 6);

    return 0;
}
