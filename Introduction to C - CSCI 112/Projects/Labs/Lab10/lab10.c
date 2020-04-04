/*
 * Olexandr Matveyev
 * Lab 10, CSCI 112
 * 4/20/2017
 */

//Including derectivs
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define ELEMENT_FILENAME "element_db.csv"

typedef struct {
    int atomic_number;
    char symbol[4];
    char name[25];
    float atomic_weight;
    char state[25];
    char bonding_type[25];
    char discovered[25];
} element_t;

//Prototype of the functions
element_t * find_element( element_t * list, char * symbol );

//Implementation 
int main( int argc, char * argv[] )
{
    if ( argc < 2 )
    {
        printf("ERROR: Please provide at least one program argument.\n");
        return 0;
    }

    //List of elements
    element_t * elements = (element_t *)calloc( 118 , sizeof( element_t ) );
    
    //Read elements' information from the text file
    FILE * element_file = fopen( ELEMENT_FILENAME, "r" );
    if ( element_file != NULL )
    {
        char line[100];
        while( fgets(line, 100, element_file ) != NULL )
        {
            // remove newline character from line
            char * nl = strchr( line, '\n' );
            if ( nl )
            {
                *nl = '\0';
            }
            //printf("line = %s\n", line );
            element_t e;
            char * str = strtok( line, "," );
            int col = 0;
            while ( str != NULL )
            {
                //Populate element
                switch( col )
                {
                    case 0:
                        e.atomic_number = atoi( str );
                        break;
                    case 1:
                        strcpy( e.symbol, str );
                        break;
                    case 2:
                        strcpy( e.name, str );
                        break;
                    case 3:
                        e.atomic_weight = atof( str );
                        break;
                    case 4:
                        strcpy( e.state, str );
                        break;
                    case 5:
                        strcpy( e.bonding_type, str );
                        break;
                    case 6:
                        strcpy( e.discovered, str );
                        break;
                }
                str = strtok( NULL, "," );
                col++;
            }
            //Add new element to the list of elements
            elements[ e.atomic_number - 1 ] = e;

            
            //printf(" %s\n", elements[ e.atomic_number - 1].symbol );

            /*
            //----------------------------Print Test-----------------------------------//
            printf("atomic_number: %d\n", elements[ e.atomic_number - 1].atomic_number );
            printf("symbol: %s\n", elements[ e.atomic_number - 1].symbol );
            printf("name: %s\n", elements[ e.atomic_number - 1].name );
            printf("atomic_weight: %f\n", elements[ e.atomic_number - 1].atomic_weight );
            printf("state: %s\n", elements[ e.atomic_number - 1].state );
            printf("bonding_type: %s\n", elements[ e.atomic_number - 1].bonding_type );
            printf("discovered: %s\n", elements[ e.atomic_number - 1].discovered );
            printf("----------------------\n");
            //-----------------------------------------------------------------------//
            */
            
        }
        //Close the stream
        fclose( element_file );
    }

    // process program arguments.
    FILE * output_f = NULL;
    int i;
    for( i = 1; i < argc; i++ )
    {
        if ( i == 1 ) // check for filename
        {
            char * dot = strchr( argv[i], '.' );
            if ( dot )
            {
                // this is a filename
                output_f = fopen( argv[i], "w" );
                continue;
            }
        }

        // Look up this element
        element_t * ele = find_element( elements, argv[i] );
        if ( ele )
        {
            //printf("%d %s\n", ele->atomic_number, ele->symbol);
            //Print elements which was found
            printf("----------------------\n");
            printf("| %d\t%.4f\n", ele->atomic_number, ele->atomic_weight);
            printf("| %s\t%s\n", ele->symbol, ele->name);
            printf("| %s\n", ele->state);
            printf("| %s\n", ele->bonding_type);
            printf("| Found: %s\n", ele->discovered);
            printf("----------------------\n");

            //Write elements into the file
            fprintf(output_f, "----------------------\n");
            fprintf(output_f, "| %d\t%.4f\n", ele->atomic_number, ele->atomic_weight);
            fprintf(output_f, "| %s\t%s\n", ele->symbol, ele->name);
            fprintf(output_f, "| %s\n", ele->state);
            fprintf(output_f, "| %s\n", ele->bonding_type);
            fprintf(output_f, "| Found: %s\n", ele->discovered);
            fprintf(output_f, "----------------------\n");
        }
    }
    //Close the stream
    fclose(output_f);
    return 0;
}

element_t * find_element( element_t * list, char * symbol )
{
    int i;
    for( i = 0; i < 118; i++ )
    {
        if ( strcmp( list[i].symbol, symbol ) == 0 )
        {
            element_t * result = &list[i];
            return result;
        }
    }
    printf("WARNING: No such element: %s\n", symbol);
    return NULL;
}