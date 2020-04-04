// ############################################# //
// # Author: Olexandr Matveyev                 # //
// # University: Montana State University      # //
// # Class: Operating Systems - CSCI 460 001   # //
// # Project: Assignment 1                     # //
// ############################################# //

#include <stdio.h>     // printf()
#include <stdlib.h>    // exit()
#include <pthread.h>   // thread
#include <unistd.h>    // system time
#include <time.h>	   // random generator

// Global constants variables
// ------------------------------------------------------------------------------------------------ //
// Cars movement directions
#define TO_BRIDGER 0
#define TO_BOZEMAN 1

// maximum number of cars, that can wait on one or another side of the bridge, before they can move
#define MAXCARS 3

// maximum number of cars that can be simulated {maximum number of threads}
#define MAX_SIM_CARS 1000
// ------------------------------------------------------------------------------------------------ //

// Extra global variables
// ------------------------------------------------------------------------------------------------ //
// global counter is used to show working progress for threads,
// and sub counter also used to show sub-progress for the threads work
unsigned int global_counter = 0;
unsigned int sub_counter = 0;

// this variable is used to switch directions
unsigned int turn = 0;

// number of cars to create {number of threads}
unsigned int num_cars_bridger = 0;
unsigned int num_cars_bozeman = 0;

// storing total number of cars
unsigned int total_num_cars = 0;

// one-way road capacity
// unsigned int max_cars = 0;
unsigned int road_capacity = 0;

// current amount of cars which is driving via bridge
unsigned int num_cars_driving_to_bridger = 0;
unsigned int num_cars_driving_to_bozeman = 0;

// these variables are used to keep track of cars that did drive away
unsigned int cars_bridger_counter = 0;
unsigned int cars_bozeman_counter = 0;

// curent cars on bridge
int cars_on_bridge[MAX_SIM_CARS];

// Number of cars driving to Bridger
int cars_to_bridger[MAX_SIM_CARS];

// Number of cars driving to Bozeman
int cars_to_bozeman[MAX_SIM_CARS];

// number of cars that must drive to Bridger, but currently waiting
int waiting_to_bridger = 0;

// number of cars that must drive to Bozeman, but currently waiting
int waiting_to_bozeman = 0;

// mutex our "global" lock
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// declaration of thread condition variables
// we have to use it to stop and start car threads
pthread_cond_t going_to_bridger = PTHREAD_COND_INITIALIZER;
pthread_cond_t going_to_bozeman = PTHREAD_COND_INITIALIZER;
// ------------------------------------------------------------------------------------------------ // 

// Functions' signature declaration
// ------------------------------------------------------------------------------------------------ //
void *thread_entry(void *);         // entry point for a thread
void OneVehicle(int);               // entry point for a car
void ArriveBridgerOneWay(int);      // print when a car arrived to bridge
void OnBridgerOneWay(int);          // print when a car is on bridge
void ExitBridgerOneWay(int);        // print when a car exits bridge
void start(void);                   // start simulation
unsigned int get_input(void);       // getting user input
void printBridgeStatus(int, int);   // print result, accepts {direction} and {car_id}, car_id is used for final print
int randomNumber(int, int);         // this function is used to generate random numbers between min and max
// ------------------------------------------------------------------------------------------------ //

void *thread_entry(void *arg)
{
    // Local variables
    // ------------------------------------------------------------------------------------------------ //
    // create integer pointer
    // cast void pointer into int pointer
    // getting thread ID which also car ID
    // currently {id} variable is not used
    int id = *((int *) arg);

    int direction = -1;
    // ------------------------------------------------------------------------------------------------ //
    
    // here we handle situation when we have to figure out which group of cars have to go first
    // ------------------------------------------------------------------------------------------------ //


    // change direction of driving every time when new thread starts
    
    // get random direcation between 0 and 1
    direction = randomNumber(0, 1);
    
    /*
    if (turn == 0)
    {
        direction = TO_BRIDGER;
        turn = 1;
    }
    else if (turn == 1)
    {
        direction = TO_BOZEMAN;
        turn = 0;
    }
    */

    // ------------------------------------------------------------------------------------------------ //

    // Working with threads
    // ------------------------------------------------------------------------------------------------ //
    // thread_err is for situation when we could not create a thread
    int thread_err;

    thread_err = pthread_mutex_lock(&mutex);
    if (thread_err == 1)
    {
        printf("Cannot lock a thread, program will be terminated.");
        exit(-1);
    }

    OneVehicle(direction);

    thread_err = pthread_mutex_unlock(&mutex);
    if (thread_err == 1)
    {
        printf("Cannot unlock a thread, program will be terminated.");
        exit(-1);
    }
    // ------------------------------------------------------------------------------------------------ //
}

int randomNumber(int lower, int upper)
{
    int num = (rand() % (upper - lower + 1)) + lower; 
    return num;
}

void OneVehicle(int direction) 
{
    // right before going thought bridger

    // if no more cars left that are driving to the Bridger change direction
    if (cars_bridger_counter >= num_cars_bridger)
    {
        num_cars_bridger = 0;

        direction = TO_BOZEMAN;
        turn = 0;
    }

    // if no more cars left that are driving to the Bozeman change direction
    if (cars_bozeman_counter >= num_cars_bozeman)
    {
        num_cars_bozeman = 0;

        direction = TO_BRIDGER;
        turn = 1;
    }
    

    // ArriveBridgerOneWay must not return until it is safe for the car to get on the one-way.
    ArriveBridgerOneWay(direction);

    // OnBridgerOneWay should, as a side-effect, print the state of the one-way and waiting cars, in some nice format
    // now the car is on the one-way section!
    OnBridgerOneWay(direction);

    ExitBridgerOneWay(direction);

    // now the car is off

    // global counter helps to track what thread is running
    global_counter = global_counter + 1;
}

void ArriveBridgerOneWay(int direction)
{
    if (direction == TO_BRIDGER)
    {
        // chaking if there are still some cars left that are going to Bridger
        if (cars_bridger_counter < num_cars_bridger)
        {
            // incrementing number of cars which are waiting before driving via one-way road
            waiting_to_bridger = waiting_to_bridger + 1;

            // while there are some cars that are driving to Bozeman via one-way road
            // or current number of cars which are driving to Bridger more than road capacity,
            // then we have to stop cars that are driving to Bridger
            while (num_cars_driving_to_bozeman > 0 || num_cars_driving_to_bridger >= road_capacity)
            {
                // sleep thread
                pthread_cond_wait(&going_to_bridger, &mutex);
            }

            // if current number of cars that are driving to Bozeman less than the road capacity 
            // and no cars driving to Bridger via one-way road, then we can signal to cars that are going to
            // Bozeman, they can drive,
            // else Bridger's cars must go
            if (num_cars_driving_to_bozeman < road_capacity && num_cars_driving_to_bridger == 0)
            {
                // if number of cars that are waiting their turn to go to Bozeman, than give them right to go
                if (waiting_to_bozeman > 0)
                {
                    // relese thread
                    pthread_cond_signal(&going_to_bozeman);
                }
            }
            else if (num_cars_driving_to_bozeman == 0 && num_cars_driving_to_bridger < road_capacity)
            {
                // relese thread
                pthread_cond_signal(&going_to_bridger);
            }
        }
        else
        {
            // to avoid dadblock
            // pthread_cond_signal(&going_to_bridger);
            // pthread_cond_signal(&going_to_bozeman);
        }
    }
    
    if (direction == TO_BOZEMAN)
    {
        // chaking if there are still some cars left that are going to Bozeman
        if (cars_bozeman_counter < num_cars_bozeman)
        {
            // incrementing number of cars which are waiting before driving via one-way road
            waiting_to_bozeman = waiting_to_bozeman + 1;

            // while there are some cars that are driving to Bridger via one-way road
            // or current number of cars which are driving to Bozeman more than road capacity,
            // then we have to stop cars that are driving to Bozeman
            while (num_cars_driving_to_bridger > 0 || num_cars_driving_to_bozeman >= road_capacity)
            {
                pthread_cond_wait(&going_to_bozeman, &mutex);
            }

            // if current number of cars that are driving to Bridger less than the road capacity 
            // and no cars driving to Bozeman via one-way road, then we can signal to cars that are going to
            // Bridger, they can drive,
            // else Bozeman's cars must go
            if (num_cars_driving_to_bridger < road_capacity && num_cars_driving_to_bozeman == 0)
            {
                // if number of cars that are waiting their turn to go to Bridger, than give them right to go
                if (waiting_to_bridger > 0)
                {
                    // relese thread
                    pthread_cond_signal(&going_to_bridger);
                }
            }
            else if (num_cars_driving_to_bridger == 0 && num_cars_driving_to_bozeman < road_capacity)
            {
                // relese thread
                pthread_cond_signal(&going_to_bozeman);
            }
        }
        else
        {
            // to avoid dadblock
            // pthread_cond_signal(&going_to_bozeman);
            // pthread_cond_signal(&going_to_bridger);
        }
    }

    // print resul
    printBridgeStatus(direction, -1);
}

void OnBridgerOneWay(int direction)
{
    if (direction == TO_BRIDGER)
    {
        // over here we testing if curent number of cars that are driving to Bridger 
        // is < then allowed cars to drive thought bridge
        if (cars_bridger_counter < num_cars_bridger)
        {
            // add a car that waiting go to bridger into cars_on_bridge[] and remove that car from cars_to_bridger[]
            int i = cars_bridger_counter;
            if (cars_to_bridger[i] != 0)
            {
                // add car to bridge
                cars_on_bridge[i] = cars_to_bridger[i];

                // remove car from list of cars that are driving to Bridger
                cars_to_bridger[i] = 0;

                // one car less which is waiting before driving to Bridger
                waiting_to_bridger = waiting_to_bridger - 1;

                // curent number of cars driving to Bridger
                num_cars_driving_to_bridger = num_cars_driving_to_bridger + 1;
            }
        }
    }

    if (direction == TO_BOZEMAN)
    {
        // over here we testing if curent number of cars that are driving to Bozeman
        // is <= then allowed cars to drive thought bridge
        if (cars_bozeman_counter < num_cars_bozeman)
        {
            // add a car that waiting go to bridger into cars_on_bridge[] and remove that car from cars_to_bridger[]
            int i = cars_bozeman_counter;
            if (cars_to_bozeman[i] != 0)
            {
                // add car to bridge
                cars_on_bridge[i] = cars_to_bozeman[i];

                // remove car from list of cars that are driving to Bozeman
                cars_to_bozeman[i] = 0;

                // one car less which is waiting before driving to Bozeman
                waiting_to_bozeman = waiting_to_bozeman - 1;

                // curent number of cars driving to Bozeman
                num_cars_driving_to_bozeman = num_cars_driving_to_bozeman + 1;
            }
        }
    }
    
    // print result
    printBridgeStatus(direction, -1);
}

void ExitBridgerOneWay(int direction)
{
    // store car id that left one-way road
    int car_left = -1;

    if (direction == TO_BRIDGER)
    {
        // if cars_bridger_counter is < num_cars_bridger then it means there are still cars which are driving to Bridger
        if (cars_bridger_counter < num_cars_bridger)
        {
            // pthread_cond_wait(&going_to_bridger, &mutex);

            // decrement number of cars which are currently driving
            num_cars_driving_to_bridger = num_cars_driving_to_bridger - 1;

            // keep car id which is living one-way road
            car_left = cars_on_bridge[cars_bridger_counter];

            // remove car from bridge 
            cars_on_bridge[cars_bridger_counter] = 0;

            // increment number of cars that are left
            cars_bridger_counter = cars_bridger_counter + 1; 
        }
    }
    
    if (direction == TO_BOZEMAN)
    {
        // if cars_bozeman_counter is < num_cars_bozeman then it means there are still cars which are driving to Bozeman
        if (cars_bozeman_counter < num_cars_bozeman)
        {
            // pthread_cond_wait(&going_to_bozeman, &mutex);

            // decrement number of cars which are currently driving
            num_cars_driving_to_bozeman = num_cars_driving_to_bozeman - 1;
            
            // keep car id which is living one-way road
            car_left = cars_on_bridge[cars_bozeman_counter];

            // remove car from bridge 
            cars_on_bridge[cars_bozeman_counter] = 0;

            // increment number of cars that are left
            cars_bozeman_counter = cars_bozeman_counter + 1;
        }
    }
    
    // print result
    printBridgeStatus(direction, car_left);
}

void printBridgeStatus(int direction, int car_left)
{
    printf("::::::::::::::::::::::::::::::::::::::::::::::::::::: --{ %d:%d }- \n", global_counter, sub_counter );    

    if (direction == TO_BRIDGER)
    {
        printf("\t---------- ::: [ To Bridger ] ::: ----------\n");
    }
    else if (direction == TO_BOZEMAN)
    {
        printf("\t---------- ::: [ To Bozeman ] ::: ----------\n");
    }

    printf("\n\t-------------------------------------------\n");
    printf("\t::: Cars driving to Bridger:\n");
    for (int i = 0; i < MAX_SIM_CARS; i++)
    {
        if (cars_to_bridger[i] != 0)
        {
            printf("\t>>> Car: %d\n", cars_to_bridger[i]);
        }
    }

    printf("\n\t..........................................\n");
    printf("\t::: Cars waiting to Bridger: %d\n", waiting_to_bridger);
    printf("\t::: Cars waiting to Bozeman: %d\n\n", waiting_to_bozeman);

    printf("\t::: Cars driving to Bridger: %d\n", num_cars_driving_to_bridger);
    printf("\t::: Cars driving to Bozeman: %d\n", num_cars_driving_to_bozeman);

    printf("\n\t::: Cars driving on one-way road:\n");
    for (int i = 0; i < MAX_SIM_CARS; i++)
    {
        if (cars_on_bridge[i] != 0)
        {
            printf("\t>>> Car: %d\n", cars_on_bridge[i]);
        }
    }
    printf("\t..........................................\n");

    printf("\n\t::: Cars driving to Bozeman:\n");
    for (int i = 0; i < MAX_SIM_CARS; i++)
    {
        if (cars_to_bozeman[i] != 0)
        {
            printf("\t>>> Car: %d\n", cars_to_bozeman[i]);
        }
    }
    printf("\t-------------------------------------------\n\n");

    printf("\t###########################################\n");
    if (car_left > 0)
    {
        if (direction == TO_BRIDGER)
        {
            printf("\tCar [%d] lef one-way road and heading towards Bridger!\n", car_left);
        }
        else if (direction == TO_BOZEMAN)
        {
            printf("\tCar [%d] lef one-way road and heading towards Bozeman!\n", car_left);
        }
    }
    printf("\t###########################################\n");
    printf("::::::::::::::::::::::::::::::::::::::::::::::::::::\n\n");

    sub_counter = sub_counter + 1;
}

void initArrays(void)
{
    // adding cars that must drive to Bridger
    // car number starts from 1 
    int lastAdded = 0;
    for (int i = 0; i < MAX_SIM_CARS; i++)
    {
        if (i < num_cars_bridger)
        {
            // add car
            cars_to_bridger[i] = i + 1;
            lastAdded = i + 1;
        }
        else
        {
            // no car
            cars_to_bridger[i] = 0;
        }
    }

    // adding cars that must drive to Bozeman
    // car number starts from the last car added to the {num_cars_bridger}
    for (int i = 0; i < MAX_SIM_CARS; i++)
    {
        if (i < num_cars_bozeman)
        {
            // add car
            cars_to_bozeman[i] = lastAdded + 1;
            lastAdded = lastAdded + 1;
        }
        else
        {
            // no car
            cars_to_bozeman[i] = 0;
        }
    }

    // init cars on bridge, of course currently there are no cars, so all values are 0
    for (int i = 0; i < MAX_SIM_CARS; i++)
    {
        cars_on_bridge[i] = 0;
    }

    // TEST: print
    // --------------------------------------------------- //
    /*
    printf("Cars driving to Bridger:\n");
    for (int i = 0; i < MAX_SIM_CARS; i++)
    {
        if (cars_to_bridger[i] != 0)
        {
            printf("::: Car: %d\n", cars_to_bridger[i]);
        }
    }
    printf("\nCars driving to Bozeman:\n");
    for (int i = 0; i < MAX_SIM_CARS; i++)
    {
        if (cars_to_bozeman[i] != 0)
        {
            printf("::: Car: %d\n", cars_to_bozeman[i]);
        }
    }
    */
    // --------------------------------------------------- //
}

void start(void)
{
    // Add cars to {cars_to_bridger} and {cars_to_bozeman}
    initArrays();

    // first print of bridge status
    printBridgeStatus(-1, -1);

    // thread_err is for situation when we could not create a thread
    int thread_err;

    // init threads, one car one thread
    pthread_t threads[total_num_cars];

    // Generate all threads
    for (int i = 0; i < total_num_cars; i++)
    {
        thread_err = pthread_create(&threads[i], NULL, thread_entry, &i);

        // stop program if we could not crate thread
        if (thread_err == 1)
        {
            printf("Cannot create a thread, program will be terminated.");
            exit(-1);
        }

        // slowdown threads
        // min = 0, max can be any non-negative integer
        //sleep( randomNumber(0, 1) ); 
    }

    // pthread_join it ensures that the main thread will wait until the second thread finishes,
    // if we would not use pthread_join the program would immediately exit.
    for (int i = 1; i < total_num_cars; i++)
    {
        thread_err = pthread_join(threads[i], NULL);

        // stop program if we could not close a thread
        if (thread_err == 1)
        {
            printf("Cannot close a thread, program will be terminated.");
            exit(-1);
        }
    }
}

/**
 * Get user input using input from console
*/
unsigned int get_input(void)
{
    unsigned int tmp = 0;

    scanf("%u", &tmp);

    return tmp;
}

/**
 * Get data from user
*/
void getData()
{
    // get user input
    // --------------------------------------------------------------------------------------------- //
    printf("Hello user.\n");
    printf("Please enter number of cars driving to Bridger.\n");
    printf("[MUST BE POSITIVE INTEGER] number of cars: ");
    num_cars_bridger = get_input();
    printf("\n");

    printf("Please enter number of cars driving to Bozeman.\n");
    printf("[MUST BE POSITIVE INTEGER] number of cars: ");
    num_cars_bozeman = get_input();
    printf("\n");

    printf("Please enter one-way road capacity.\n");
    printf("[MUST BE POSITIVE INTEGER] one-way road capacity: ");
    road_capacity = get_input();
    printf("\n");
    // --------------------------------------------------------------------------------------------- //

    // getting total amount of cars
    total_num_cars = num_cars_bridger + num_cars_bozeman;
}

int main(int argc, char *argv[])
{
    // working with arguments
    // -------------------------------------------------- //
    num_cars_bridger = atoi(argv[1]);
    num_cars_bozeman = atoi(argv[2]);
    road_capacity = atoi(argv[3]);

    // getting total amount of cars
    total_num_cars = num_cars_bridger + num_cars_bozeman;
    // -------------------------------------------------- //

    // use this if you need use input
    // ----------------------------- //
    // getData();
    // ----------------------------- //

    // init random time
    srand(time(NULL));

    // do some checking before starting simulation;
    // we have to make sure that at least we provide minimum number of cars and road capacity;
    // we have to make sure that the number of cars is not more then number of threads that we can run;
    if (num_cars_bridger > 0 && num_cars_bozeman > 0 && road_capacity > 0 && total_num_cars < MAX_SIM_CARS)
    {
        // Start simulation
        start();

        // exit from program
        return EXIT_SUCCESS;
    }
    else
    {
        printf("\nSomthing wrong with your inputs!\n");
        printf("Program terminated\n");

        // terminate program
        exit(-1);
    }

    // clean up
    pthread_mutex_destroy(&mutex);
    pthread_exit(NULL);
}