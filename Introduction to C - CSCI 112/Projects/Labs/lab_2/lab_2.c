/*
 * Olexandr Matveyev
 * Lab 2, CSCI 112
 * 1/27/2017
 */

 #include <stdio.h>

double get_input(int);
double get_next(double, double);
void print_result(double);

 int
 main(void)
 {
     //===============================//
     //Variable declaration
     double num = 0;
     double x1 = 0, x2 = 0, x3 = 0, x4 = 0, x5 = 0;
     //===============================//

     //===============================//
    //Input
    //Get [X_1]input from user
    num = 1;
    x1 = get_input(num);

    //Get [X_2]input from user
    num = 2;
    x2 = get_input(num);
    //===============================//

    //===============================//
    //Calculating result
    //X_3
    x3 = get_next(x1, x2);

    //X_4
    x4 = get_next(x2, x3);

    //X_5
    x5 = get_next(x3, x4);
    //===============================//

    //===============================//
    //Printing Result 
    print_result(x5);
    //===============================//

    return(0);
 }

//Get user input
double get_input(int num)
{
    double tmp = 0;
    printf("\nEnter X_%d: ", num);
    scanf("%lf", &tmp);

    return tmp;
}

//Calculate nex X value
double get_next(double x_1, double x_2)
{

    double next = (x_1 / 2) + 3*x_2;

    return next;
}

//Display result
void print_result(double x_5)
{
    printf("\nX_5 = %.2lf\n\n", x_5);
}