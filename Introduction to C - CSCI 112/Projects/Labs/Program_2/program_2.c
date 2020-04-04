/*
 * Olexandr Matveyev
 * Programm 2, CSCI 112
 * 3/18/2017
 */

//Including derectivs
#include <stdio.h>

#define MAX_ARRAY_SIZE 50

//Declaration of the functions

// Fill array with values from user.
int populate_array(int array[]);

// Print out the array values
void print_array(int array[], int n);

// Swap two array elements. 
void swap(int array[], int index1, int index2);

// Sorting algorithm
void quicksort(int array[], int low, int high);

// Find the partition point (pivot)
int partition(int array[], int low, int high);

int get_input(void);

//The definition of functions
 int
 main(void)
 {
     int array[MAX_ARRAY_SIZE];
     int n = -1;
     
     n = populate_array(array);

     printf("The initial array contains: \n");
     print_array(array, n);

     printf("The array is now sorted:\n");
     quicksort(array, 0, (n-1));
     print_array(array, n);

     return(0);
 }

int populate_array(int array[])
{
    //Get from user amount of values that must be entered to the array
    int n;
    while(1)
    {
        printf("Enter the value of n > ");
        n = get_input();
        if(n > 0 && n < MAX_ARRAY_SIZE)
        {
            break;
        }
        else if(n < 0)
        {
            printf("%d is less than zero. Please try again.\n\n", n);
        }
        else if(n > MAX_ARRAY_SIZE)
        {
            printf("%d exceeds the maximum array size. Please try again.\n\n", n);
        }
    }

    //Enter values to array
    printf("Enter %d integers (positive, negative, or zero) > \n", n);
    int i = 0;
    for(i = 0; i < n; i++)
    {
        int array_val = get_input();
        array[i] = array_val;
    }

    return n;
}

void print_array(int array[], int n)
{
    int i = 0;
    for(i = 0; i < n; i++)
    {
        printf("%+5d\n", array[i]);
    }
}

void swap(int array[], int index1, int index2)
{
    //Swap values of the array

    int index1_val = array[index1];
    int  index2_val = array[index2];

    array[index1] = index2_val;
    array[index2] = index1_val;

}

void quicksort(int array[], int low, int high)
{
    //Relocate min values on the beginning of the array
    //and max value on the bottom of the array

    int pivot = 0;
    if(low < high)
    {
        pivot = partition(array, low, high);
        quicksort(array, low, (pivot - 1));
        quicksort(array, (pivot + 1), high);
    }
}

int partition(int array[], int low, int high)
{
    int pivot = array[high];
    int i = low;
    int j = 0;
    for(j = low; j <= (high-1); j++)
    {
        if(array[j] <= pivot)
        {
            swap(array, i, j);
            i = i + 1;
        }
    }

    swap(array, i, high);

    return i;
}

//Get user input
int get_input()
{
    //Declaration of the variables
    int tmp = 0;

    scanf("%d", &tmp);

    return tmp;
}