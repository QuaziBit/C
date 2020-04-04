/*
 * Olexandr Matveyev
 * Lab 9, CSCI 112
 * 4/11/2017
 */

//Including derectivs
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct Elements {
    int atomic_number;
    char name[250];
    char chemical_symbol[250];
    char class[250];
    double atomic_weight;
    int n_electrons[7];
} element_t;


#define SIZE 250
#define MAX_ELEMENTS 20
#define ITEM_DATA 6

int total_elements = 0;
int min_a_n = 1000, max_a_n = -1000;

//Prototype of the functions
element_t scan_element();
void print_element(element_t elements[MAX_ELEMENTS]);

//Implementation 
 int
 main(int argc, char *argv[])
 {
    element_t elements[MAX_ELEMENTS];

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
        if(n <= 0 || n > MAX_ELEMENTS)
        {
            printf("ERROR: You must provide an integer greater than 0 and less than or equal to 20.\n");
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
                total_elements = n;

                //Get input
                int i = 0;
                while(n > 0)
                {
                    elements[i] = scan_element();
                    i++;
                    n--;
                }

                //Print
                print_element(elements);

                // int j = 0;
                // for(j = 0; j < counter; j++)
                // {
                //     print_element(elements[j]);
                // }
            }
        }
    }
    return(0);
 }

 element_t scan_element()
 {
    element_t tmp;

    //str is used to store entered string line
    char str[SIZE];

    //tmp_str is used to store single word or number sequence
    char tmp_str[SIZE];

    int j = 0;

    //isNum is used to indicate whether word is number or word
    int isNum = 0;

    //Number of chars in the line
    int len = 0;

    int element_counter = 0;

    int sub_counter = 0;

    double tmp_num = 0;

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
                        if(element_counter == 0)
                        {
                            tmp.atomic_number = (int)tmp_num;

                            //Get smallest and largest atomic number
                            if(((int)tmp_num) < min_a_n)
                            {
                                min_a_n = (int)tmp_num;
                            }
                            if(((int)tmp_num) > max_a_n)
                            {
                                max_a_n = (int)tmp_num;
                            }
                        }
                        if(element_counter == 1)
                        {
                            strcpy(tmp.name, tmp_str);
                        }
                        if(element_counter == 2)
                        {
                            strcpy(tmp.chemical_symbol, tmp_str);
                        }
                        if(element_counter == 3)
                        {
                            strcpy(tmp.class, tmp_str);
                        }
                        if(element_counter == 4)
                        {
                            tmp.atomic_weight = tmp_num;
                        }
                        if(element_counter > 4)
                        {
                            tmp.n_electrons[sub_counter] = tmp_num;
                            sub_counter++;
                        }
                    //============================================//
                    tmp_num = 0;
                    element_counter++;
                }
            }

        }
    }

    return tmp;
 }

 void print_element(element_t elements[MAX_ELEMENTS])
 {

    //print total number of elements
    printf("%d total elements.\n", total_elements);

    //Print element with the smallest and the largest atomic number
    int c = 0;
    for(c = 0; c < total_elements; c++)
    {
        if(elements[c].atomic_number == min_a_n)
        {
            printf("%s had the smallest atomic number.\n", elements[c].name);
        }
        if(elements[c].atomic_number == max_a_n)
        {
            printf("%s had the largest atomic number.\n", elements[c].name);
        }
    }

    int i = 0;
    for(i = 0; i < total_elements; i++)
    {
        printf("---------------\n");
        printf("| %d\t%.4f\n", elements[i].atomic_number, elements[i].atomic_weight);
        printf("| %s\t%s\n", elements[i].chemical_symbol, elements[i].name);
        int j = 0;
        printf("| ");
        for(j = 0; j < 7; j++)
        {
            if(elements[i].n_electrons[j] != 0)
            {
                printf("%d ", elements[i].n_electrons[j]);
            }
        }
        printf("\n---------------\n");
    }
 }