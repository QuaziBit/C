/*
 * Olexandr Matveyev
 * Lab 3, CSCI 112
 * 2/6/2017
 */

//Including derectivs
#include <stdio.h>
#include <math.h>
#include <float.h>

//Declaration of the functions
int get_n(void);
double get_set(int);
double get_input(void);
void print_result(double, double, double, double, double);
void calculate_result(int, double, double, double, double);

//The definition of functions

 int
 main(void)
 {
    //Declaration of the variables
    //===========================================================//
    int N = -1;
    //===========================================================//
    
    //Get user input
    //===========================================================//

    //User have to specify the size of numbers collection
    N = get_n();

    if(N > 0)
    {
        //If N is valid user will enter collection of numbers
        get_set(N);
    }
    else if(N == 0)
    {
        //If N equals to 0, then user will not be asked for further input
        //Variables highest, lowest, average, range, and s_dev will have zero values
        print_result(0, 0, 0, 0, 0);
    }
    //===========================================================//
    
    return(0);
 }

//Get size of numbers set
int get_n(void)
{
    //Declaration of the variables
    //===========================================================//
    int N = -1;
    double tmp = 0;
    //===========================================================//

    //===========================================================//
    do{
        printf("Enter a value for N that is >= 0: ");
        N = (int)get_input();

        if(N < 0)
        {
            printf("Invalid value for N\n");
        }
        else
        {
            break;
        }
    }while(N < 0);
    //===========================================================//

    return N;
}

double get_set(int N)
{
    //Declaration of the variables
    //===========================================================//
    double tmp = 0;
    double sum = 0;
    double S = 0;
    //if input < -DBL_MAX then it is lowest
    //if input > DBL_MAX then it is highest
    double lowest = DBL_MAX, highest = -DBL_MAX;
    //===========================================================//

    //For loop
    //===========================================================//
    int i;
    for(i = 0; i < N; i++)
    {
        printf("Enter a number: ");
        tmp = get_input();

        if(tmp < lowest)
        {
            lowest = tmp;
        }
        if(tmp > highest)
        {
            highest = tmp;
        }

        sum += tmp;
        S += pow(tmp, 2);
    }
    //===========================================================//

    calculate_result(N, highest, lowest, sum, S);

}

//Get user input
double get_input(void)
{
    double tmp = 0;

    scanf("%lf", &tmp);

    return tmp;
}

//Function will calculate Average, Range, and Standard deviation
//based on user input
void calculate_result(int N, double highest, double lowest, double sum, double S)
{
    //Average
    double average = sum /N;

    //Range
    double range = highest - lowest;

    //Standard deviation
    double s_dev = sqrt( S/N - pow(average, 2) );

    //Print calculations
    print_result(highest, lowest, average, range, s_dev);
}

//Display result
void print_result(double h, double l, double a, double r, double s_dev)
{
    printf("The Highest is: %.3lf\nThe Lowest is: %.3lf\n", h, l);
    printf("The Average is: %.3lf\n", a);
    printf("The Range is: %.3lf\n", r);
    printf("The Standard deviation is: %.3lf\n ", s_dev);
}