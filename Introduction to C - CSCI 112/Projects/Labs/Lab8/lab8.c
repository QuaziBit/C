/*
 * Olexandr Matveyev
 * Lab 8, CSCI 112
 * 4/04/2017
 */

//Including derectivs
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define SIZE 80

//Prototype of the functions
void reverse(char *);

//Implementation 
 int
 main(int argc, char *argv[])
 {
    //[argc] The number of command-line arguments.

    //argv This is the list of string arguments provided on the command line.
    //The command-line arguments are separated using whitespace. argv[0] always contains the name of the program.

    int n = 0;
    long int n_tmp = 0;
    char * pEnd;

    if(argc != 2 || argc > 2)
    {
        printf("Please provide an integer greater than or equal to 0\n");
    }
    else
    {
        n_tmp = strtol(argv[1], NULL, 10);
        n = n_tmp;
        if(n < 0)
        {
            printf("Please provide an integer greater than or equal to 0\n");
        }
        else
        {
            //Get input
            char str[SIZE];
            if (fgets(str, SIZE, stdin)) 
            {
                //printf("%s\n", str);
                reverse(str);
            }

        }
    }
     return(0);
 }

 void reverse(char *str)
 {
    /*
    Example: hello word
    start loop from the end of the array, if char is space invert word;
    to invert word loop starts from N+a till word_len is not zero; N+a = i+1.
    */

    char word[SIZE];

    //Number of chars in the line
    int idx = strlen(str) - 1;

    //The length of one word in the line
    int word_len = 0;

    int x = 0;

    int i = 0;
    //start loop via array from the end of array
    for(i = idx; i >= 0; i--)
    {
        if(str[i] != ' ')
        {
            //if char is not space then count word_len
            word_len++;
        }
        else if(str[i] == ' ')
        {
            //x is first letter in the word, i+1 means start looping via word from first word letter
            x = (i+1);
            while(word_len >= 0)
            {
                //if char is alphanumeric print char
                if(isalnum(str[x]))
                {
                    printf("%c",str[x]);
                }
                x++;
                word_len--;
            }
            word_len = 0;
            printf(" ");
        }
    }

    //print last word in the array
    x = (i+1);
    while(word_len >= 0)
    {
        if(isalnum(str[x]))
        {
            printf("%c",str[x]);
        }
        x++;
        word_len--;
    }
    printf("\n");
 }