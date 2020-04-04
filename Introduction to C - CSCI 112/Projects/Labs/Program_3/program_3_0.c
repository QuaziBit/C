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

typedef struct StudentRecord {
    int sid;
    char last_name[50];
    char first_name[50];
    float *grades;
    float gpa;
} student_record_t;

#define SIZE 250
#define MAX_RECORDS 10
#define RECORD_DATA 5

//Prototype of the functions
student_record_t scan_records();

//Implementation 
 int
 main(int argc, char *argv[])
 {
    student_record_t records[MAX_RECORDS];

    //===============================//
    int n = 0;
    int counter = 0;
    long int n_tmp = 0;
    char * pEnd;
    //===============================//

    if(argc != 2 || argc > 2)
    {
        printf("ERROR: You must provide exactly one argument to this program.\n");
    }
    else
    {
        n_tmp = strtol(argv[1], NULL, 10);
        n = n_tmp;
        if(n <= 0 || n > MAX_RECORDS)
        {
            printf("ERROR: You must provide an integer greater than 0 and less than or equal to 10.\n");
        }
        else
        {
            n_tmp = strtol(argv[1], NULL, 10);
            n = n_tmp;
            counter = n;
            if(n < 0)
            {
                printf("Please provide an integer greater than or equal to 0\n");
            }
            else
            {
                //Get input
                int i = 0;
                while(n > 0)
                {
                    records[i] = scan_records();
                    i++;
                    n--;
                }
            }
        }
    }
    return(0);
 }

 student_record_t scan_records()
 {
    student_record_t tmp;

    //str is used to store entered string line
    char str[SIZE];

    //tmp_str is used to store single word or number sequence
    char tmp_str[SIZE];

    int j = 0;

    //isNum is used to indicate whether word is number or word
    int isNum = 0;

    //Number of chars in the line
    int len = 0;

    int record_counter = 0;

    int sub_counter = 0;

    double tmp_num = 0;

    double grade_sum = 0;
    double gpa = 0;

    //Get user input and split line "user input" into numbers and words
    if (fgets(str, SIZE, stdin)) 
    {
        //========================================================================//
        //Add extra space on the end of each line in order to get let word or letter
        len = strlen(str) - 1;
        str[len + 1] = ' ';
        //========================================================================//

        //Loop through entered line
        int i = 0;
        for(i = 0; i < SIZE; i++)
        {
            //if (str) at index {i} is [\0 --> end of line] then loop through all words in entered line
            if(str[i] != '\0')
            {
                //store single word in a temporary array
                tmp_str[j] = str[i];
                j++;

                if(str[i] == ' ')
                {
                    //end word with NULL character
                    tmp_str[j-1] = '\0';

                    //Loop through single word
                    int x = 0;
                    for(x = 0; x < j; x++)
                    {
                        //Check if string literal is number or letter
                        if(tmp_str[x] != ' ')
                        {
                            if(isdigit(tmp_str[x]))
                            {
                                isNum = 1;
                            }
                            else if(isalpha(tmp_str[x]))
                            {
                                isNum = 0;
                            }
                        }

                    }
                    if(isNum == 1)
                    {
                        //Convert string literal to double
                        sscanf(tmp_str, "%lf", &tmp_num);
                    }
                    else
                    {
                        //printf("Is letter: %s\n", tmp_str);
                    }
                    isNum = 0;
                    j = 0;

                    //populate an instance of an element_t structure
                    //============================================//
                    if(record_counter == 0)
                    {
                        tmp.sid = (int)tmp_num;
                        printf("ID: %d\n", (int)tmp_num);
                    }
                    if(record_counter == 1)
                    {
                        strcpy(tmp.last_name, tmp_str);
                        printf("Last Name: %s\n", tmp_str);
                    }
                    if(record_counter == 2)
                    {
                        strcpy(tmp.first_name, tmp_str);
                        printf("First Name: %s\n", tmp_str);
                    }
                    if(record_counter > 3)
                    {
                        //float *grades;
                        //tmp.n_electrons[sub_counter] = tmp_num;
                        if(tmp_num != 0)
                        {
                            printf("Index: %d --- Grade: %f\n", sub_counter, (float)tmp_num);
                            grade_sum += tmp_num;
                            sub_counter++;
                        }
                    }
                    if(record_counter == 4)
                    {
                        //tmp.gpa = (float)tmp_num;
                        //printf("GPA: %f", (float)tmp_num);
                    }
                    //============================================//
                    tmp_num = 0;
                    record_counter++;
                }
            }
        }
        if(grade_sum != 0)
        {
            gpa = grade_sum / sub_counter;
            //tmp.gpa = (float)tmp_num;
            printf("GPA: %f", (float)gpa);
        }
    }

    return tmp;
 }