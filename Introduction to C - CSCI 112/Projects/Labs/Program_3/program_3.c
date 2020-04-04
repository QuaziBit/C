/*
 * Olexandr Matveyev
 * Program 3, CSCI 112
 * 4/19/2017
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
void free_memory(student_t *, int);
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
    //Array of students' records
    student_t *student_records;
    //dynamically allocate memory for the array of students
    student_records = (student_t*) calloc(students, sizeof(student_t));
    //Check if students and grades were entered
    if(students != 0 && grades != 0)
    {
        //Create students' records
        int i = 0;
        while(i < students)
        {
            //Get input from file or from console and store new record in the array
            student_records[i] = input(grades);
            i++;
        }

        //Print records
        print(students, grades, student_records);

        //Free memory
        free_memory(student_records, students);
    }
    //==================================================//

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
    //dynamically allocate memory for the array of grades
    grades_tmp = (float*) calloc(grades, sizeof(float));
    for(i = 0; i < grades; ++i)
    {
        //Get grades and add grades into the array
        scanf("%f", (grades_tmp + i));
    }
    for(i = 0; i < grades; ++i)
    {
        //Calculate gpa
        gpa += grades_tmp[i];
    }
    gpa = gpa / grades;
    //Add grades and gpa to the student structure
    student.grades = grades_tmp;
    student.gpa = gpa;

    //return student record
    return student;
}

void free_memory(student_t *records, int s)
{
    int i = 0;
    for(i = 0; i < s; i++)
    {
        //set grades pointer equal to NULL
        records[i].grades = NULL;
    }
    //set records equal to NULL
    records = NULL;
}

void print(int s, int g, student_t *records)
{
    //Print records
    int i = 0;
    for(i = 0; i < s; i++)
    {
        printf("ID: %d, Name: %s %s, GPA: %.2f\n", records[i].sid, records[i].last_name, records[i].first_name, records[i].gpa);
        printf("Grades: ");
        int j = 0;
        for(j = 0; j < g; ++j)
        {
            //print grades
            printf("%.1f ", records[i].grades[j]);
        }
        printf("\n");
    }
}
