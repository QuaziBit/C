/*
 * Olexandr Matveyev
 * Program 3, CSCI 112
 * 4/18/2017
 */

//Including derectivs
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define NAME_SIZE 25

typedef struct student {
    int sid;
    char last_name[NAME_SIZE];
    char first_name[NAME_SIZE];
    float *grades;
    float gpa;
} student_t;

//Prototype of the functions
student_t input(int);
student_t create_records(int, int, char *);
void print(int, int, student_t *);

//Implementation 
int
main(void)
{
    int students = 0, grades = 0;
     
    //==================================================//
    //Get students and grades from file or from console
    scanf("%d\n", &students);
    scanf("%d", &grades);
    printf("Number of students: %d\n", students);
    printf("Number of grades (each): %d\n", grades);
    //==================================================//
    
    //==================================================//
    student_t student_records[students];
    if(students != 0 && grades != 0)
    {
        int i = 0;
        while(i < students)
        {
            student_records[i] = input(grades);
            i++;
        }
    }
    //==================================================//


    print(students, grades, student_records);

    return 0; 
}

student_t input(int grades)
{
    student_t student;

    int sid = 0;
    char last_name[NAME_SIZE];
    char first_name[NAME_SIZE];
    float *grades_tmp;
    float gpa = 0;

    //Get input
    scanf("%d\n", &sid);
    scanf("%s\n", &last_name);
    scanf("%s\n", &first_name);

    //Populate struct
    student.sid = sid;
    strcpy(student.last_name, last_name);
    strcpy(student.first_name, first_name);

    //Get grades
    int i = 0;
    grades_tmp = (float*) calloc(grades, sizeof(float));
    for(i = 0; i < grades; ++i)
    {
        scanf("%f", (grades_tmp + i));
    }
    for(i = 0; i < grades; ++i)
    {
        gpa += grades_tmp[i];
    }

    gpa = gpa / grades;
    student.grades = grades_tmp;
    student.gpa = gpa;

    return student;
}


student_t create_records(int students, int grades, char *str)
{
    student_t tmp;


    return tmp;
}

void print(int s, int g, student_t *records)
{
    int i = 0;
    for(i = 0; i < s; i++)
    {
        printf("ID: %d, Name: %s %s, GPA: %.2f\n", records[i].sid, records[i].last_name, records[i].first_name, records[i].gpa);
        printf("Grades: ");
        int j = 0;
        for(j = 0; j < g; ++j)
        {
            printf("%.2f ", records[i].grades[j]);
        }
        printf("\n");
    }
}
