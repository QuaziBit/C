/*
 * Olexandr Matveyev
 * Lab 6, CSCI 112
 * 3/09/2017
 */

//Including derectivs
#include <stdio.h>
#include <math.h>
#include <float.h>

// List of all function prototypes

// displays user menu, validates input
int user_menu(void);

// reads input
float get_input(void);

// Equation functions that are pass by reference
void equation1(float *);
void equation2(float *);
void equation3(float *);
void equation4(float *);

// User input functions return a value from user
float get_position_initial(void);
float get_position_final(void);
float get_velocity_initial(void);
float get_velocity_final(void);
float get_acceleration(void);
float get_time(void); 

//Print out the calculated result
void printResult(float *);

//The definition of the functions
 int
 main(void)
 {
    // Print welcome message
    printf("Welcome to the MOTION EQUATION CALCULATOR\n\n");

    // Variable for the user choice menu.
    int user_choice;
    
    do
    {
        // print menu, validate choice is between 1 and 5
        user_choice = user_menu();

        // You will pass the address of this variable to your equation functions. 
        // Variable to hold calculated result
        float result;

        // Handle menu choice selected by user
        switch( user_choice )
        {
            case 1:
                //Passing address of result variable to store final calculations under its address
                equation1(&result);
            break;
            case 2:
                equation2(&result);
            break;
            case 3:
                equation3(&result);
            break;
            case 4:
                equation4(&result);
            break;
            case 5:
                // exit program if user selected QUIT
                printf("Thank you for using the MOTION EQUATION CALCULATOR. Goodbye.\n");
                return 0;
            break;
        }

        // Print out the calculated result with four digits after the decimal place
        //printf("Your result is %.4f.\n\n", result);

        //This function will accept address of result variable and will print out value stored under its address
        printResult(&result);

        } while ( user_choice != 5 );

    return 0; // exit with no error
 }

 int user_menu()
 {
    float tmp = 0;

    while(tmp != 5)
    {
        printf("Choose a motion equation 1-4 or choose 5 to QUIT > ");
        tmp = get_input();
        // User input have to be in specific range
        if( ((int)tmp)  <= 5 && ((int)tmp) > 0)
        {
            return tmp;
        }
        else
        {
            printf("Invalid Option. Please try again.\n\n");
        }
    }
 }

//Get user input
float get_input(void)
{
    // Basic input

    float tmp = 0;

    scanf("%f", &tmp);

    return tmp;
}

//=====================================//
void equation1(float *result)
{
    //[1] initial velocity
    float v_0 = get_velocity_initial();
    float a = get_acceleration();
    float t = get_time();
    
    float vf = v_0 + a * t;
    *result = vf;
}
void equation2(float *result)
{
    //[2] acceleration
    float x_0 = get_position_initial();
    float v_0 = get_velocity_initial();
    float t = get_time();
    float a = get_acceleration();

    float xf = x_0 + v_0 * t + 0.5 * a * pow(t, 2);
    *result = xf;
}
void equation3(float *result)
{
    //[3] time
    float v_0 = get_velocity_initial();
    float a = get_acceleration();
    float xf = get_position_final();
    float x_0 = get_position_initial();

    float vf = sqrt( (v_0 * v_0) + 2 * a * (xf - x_0) );
    *result = vf;
}
void equation4(float *result)
{
    //[4] acceleration
    float x_0 = get_position_initial();
    float vf = get_velocity_final();
    float v_0 = get_velocity_initial();
    float t = get_time();

    float xf = x_0 + 0.5 * (vf+v_0) * t;
    *result = xf;
}
//=====================================//

//=====================================//
float get_position_initial()
{
    printf("Enter initial position > ");
    return get_input();
}
float get_position_final()
{
    printf("Enter final position > ");
    return get_input();
}
float get_velocity_initial()
{
    printf("Enter initial velocity > ");
    return get_input();
}
float get_velocity_final()
{
    printf("Enter final velocity > ");
    return get_input();
}
float get_acceleration()
{
    printf("Enter acceleration > ");
    return get_input();
}
float get_time()
{
    printf("Enter time > ");
    return get_input();
}
//=====================================//

//Print out the calculated result
void printResult(float *result)
{
    // Print out the calculated result with four digits after the decimal place
    printf("Your result is %.4f.\n\n", *result);
}