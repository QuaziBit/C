/*
 * Olexandr Matveyev
 * Lab 7, CSCI 112
 * 3/28/2017
 */

//Including derectivs
#include <stdio.h>

//Prototype of the functions
char *my_strncpy(char *,  char *, int);
char *my_strncat(char *,  char *, int);

//Implementation 
//============================================================//
char *my_strncpy(char *dest,  char *source, int n)
{
    int i = 0;
    for(i = 0; i < n; i++)
    {
        dest[i] = source[i];
    }
    dest[n] = '\0';
    return dest;
}

char *my_strncat(char *dest,  char *source, int n)
{
    int i;
    int j = 0;
    for(i = n; i <= n*2; i++)
    {
        dest[i] = source[j];
        j++;
    }
    return dest;
}
//============================================================//

 int
 main(void)
 {
     char testSrc[] = "Hello";
     char testDest[40] = "world";
     int n = 5;

     my_strncat(testDest, testSrc, n);
     printf("CAT: %s \n", testDest);
     
     my_strncpy(testDest, testSrc, n);
     printf("CPY: %s \n", testDest);

     printf("%s \n", testDest);

     return(0);
 }