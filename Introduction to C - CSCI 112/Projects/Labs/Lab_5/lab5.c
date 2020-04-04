/*
 * Olexandr Matveyev
 * Lab 5, CSCI 112
 * 2/26/2017
 */

//Including derectivs
#include <stdio.h>

//Declaration of the global variables
#define SIZE 12
int barcode[SIZE];

//Declaration of the functions
void get_input(void);
void isBarcodeValid(void);
void result(int, int, int, int, int);

//The definition of the functions
 int
 main(void)
 {
    //Get array of digits
    printf("\nEnter a bar code to check. Separate digits with a space > \n");
    get_input();

     return(0);
 }

//Get user input
void get_input(void)
{
    int i = 0;

    while(i < SIZE)
    {
        scanf("%d", &barcode[i]);
        i++;
    }

    isBarcodeValid();
}

void isBarcodeValid(void)
{
    int i = 0;

    int odd_sum = 0;
    int even_sum = 0;
    int total_sum = 0;
    int last_digit = 0;
    int isValid = 0;
    int check_digit = 0;

    for(i = 0; i < SIZE; i++)
    {
        if(i % 2 == 0)
        {
            odd_sum += barcode[i];
        }
        else
        {
            if(i != (SIZE-1) ) 
            {
                even_sum += barcode[i];
            }
        }

        /*
        if(i % 2 == 0)
        {
            if(i != (SIZE-1) ) 
            {
                even_sum += barcode[i];
                printf("[%d] --- EVEN: %d\n", i, barcode[i]);
            }
        }
        else
        {
            odd_sum += barcode[i];
            printf("[%d] --- ODD: %d\n", i, barcode[i]);
        }
        */
    }

    odd_sum *= 3;
    total_sum = even_sum + odd_sum;

    last_digit = total_sum % 10;

    if(last_digit == 0)
    {
        check_digit = 0;
    }
    else
    {
        check_digit = 10 - last_digit;
    }

    if(check_digit == barcode[SIZE - 1])
    {
        isValid = 1;
    }
    else
    {
        isValid = 0;
    }

    result(isValid, odd_sum, even_sum, total_sum, check_digit);
}

//Display result
void result(int isValid, int odd_sum, int even_sum, int total_sum, int check_digit)
{
    int j = 0;

    printf("\n");
    printf("You entered the code: ");
    for(j = 0; j < SIZE; j++)
    {
        printf("%d ", barcode[j]);
    }
    printf("\n");

    printf("STEP 1: Sum of odds times 3 is %d\n", odd_sum);
    printf("STEP 2: Sum of the even digits is %d\n", even_sum);
    printf("STEP 3: Total sum is %d\n", total_sum);
    printf("STEP 4: Calculated check digit is %d\n", check_digit);

    if(isValid == 1)
    {
        printf("STEP 5: Check digit and last digit match\nBarcode is VALID.\n");
    }
    else
    {
        printf("Check digit and last digit do not match\nBarcode is INVALID.\n");
    }
}