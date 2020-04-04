/*
 * Olexandr Matveyev
 * Programm 1, CSCI 112
 * 2/14/2017
 */

//Including derectivs
#include <stdio.h>
#include <math.h>
#include <float.h>

//Declaration of the functions
int is_valid(int);
int get_input(void);
void print_pattern(int);

//The definition of functions
 int
 main(void)
 {
     //Declaration of the variables
     //===========================================================//
     int isValid = 0;
     int num = 0;
     //===========================================================//
     
     //===========================================================//
     while(isValid == 0)
     {
         printf("Enter an odd number less than or equal to 9 and greater than 0 > ");
         num = get_input();
         isValid = is_valid(num);
     }
     //===========================================================//

     print_pattern(num);
     
     return(0);
 }

//Check if entered number is valid
int is_valid(int num)
{
    //Declaration of the variables
    //===========================================================//
    int isValid = 0;
    //===========================================================//

    //===========================================================//
    if(num < 1)
    {
        printf("You have entered a number less than 1. Please try again.\n");
        isValid = 0;
    }
    else if(num > 9)
    {
        printf("You have entered a number greater than 9. Please try again.\n");
        isValid = 0;
    }
    else
    {
        if(num % 2 == 0)
        {
            printf("You have entered an even number. Please try again.\n");
            isValid = 0;
        }
        else
        {
            printf("You have entered an odd number.\n");
            isValid = 1;
        }
    }
    //===========================================================//

    return isValid;
}

//Get user input
int get_input(void)
{
    //Declaration of the variables
    //===========================================================//
    int tmp = 0;
    //===========================================================//

    //===========================================================//
    scanf("%d", &tmp);
    //===========================================================//

    return tmp;
}

//Display result
void print_pattern(int num)
{
    //Declaration of the variables
    //===========================================================//
    int tmp = num;

    int i = 0, j = 0;
    //===========================================================//

    //Printing top and bottom part
    //===========================================================//
    for(i = 1; i <= num; i++)
    {
        //Printing top part
        //===========================================================//
        if(i % 2 != 0)
        {
            int x = 1;
            printf("%*s", (num - i), " ");
            while(x <= i)
            {
                printf("%d ", x);
                x++;
            }
            printf("\n");
        }
        //===========================================================//

        //Printing bottom part
        //===========================================================//
        if(i == num)
        {
            for(j = (num - 2); j >= 1; j--)
            {
                if(j % 2 != 0)
                {
                    int y = 1;
                    printf("%*s", (j - num), " ");
                    while(y <= j)
                    {
                        //printf("You entered %*s", num, " ");
                        printf("%d ", y);
                        y++;
                    }
                    printf("\n");
                }
            }
        }
        //===========================================================//
    }
    //===========================================================//
}