/*
 * Olexandr Matveyev
 * Lab 4, CSCI 112
 * 2/21/2017
 */

//Including derectivs
#include <stdio.h>
#include <math.h>
#include <float.h>

//Declaring constants
#define PI 3.14159
#define LOOP_LIMIT 90

//Declaring enum data type
enum menu_t 
{
    Sine, 
    Cosine, 
    Tangent, 
    QUIT
};
typedef enum menu_t MENU;

//Declaration of the functions
unsigned int get_input(void);
void result(enum menu_t);

//The definition of functions
 int
 main(void)
 {
    unsigned int tmp = 0;

    while(tmp != 3)
    {
        printf("Please choose an option: (0) Sine (1) Cosine (2) Tangent (3) QUIT\n");
        printf("Enter your choice > ");
        tmp = get_input();

        switch(tmp)
        {
            case Sine:
            //printf("You entered: %d\n", tmp );
            result(Sine);
            break;
            case Cosine:
            //printf("You entered: %d\n", tmp );
            result(Cosine);
            break;
            case Tangent:
            //printf("You entered: %d\n", tmp );
            result(Tangent);
            break;
            case QUIT:
            printf("You chose QUIT. Thank you, come again!");
            break;
            default :
            printf("%d is an invalid option. Please try again.\n", tmp );
        }
    }
    return(0);
 }

//Get user input
unsigned int get_input(void)
{
    unsigned int tmp = 0;

    scanf("%u", &tmp);

    return tmp;
}

//Display result
void result(enum menu_t m)
{
    double r = 0;
    int i = 0;

    for(i = 0; i <= LOOP_LIMIT; i += 15)
    {
        r = i * (PI / 180);
        switch(m)
        {
            case Sine:
            printf("\tsin(%d) = %.4lf\n", i, sin(r));
            break;
            case Cosine:
            printf("\tcos(%d) = %.4lf\n", i, cos(r));
            break;
            case Tangent:
            if(i == 90)
            {
                printf("\ttan(%d) is UNDEFINED\n", i);
            }
            else
            {
                printf("\ttan(%d) = %.4lf\n", i, tan(r));
            }
            break;
        }
    }
}