// ############################################# //
// # Author: Olexandr Matveyev                 # //
// # University: Montana State University      # //
// # Class: Operating Systems - CSCI 460 001   # //
// # Project: Assignment 2                     # //
// # About: Simulation of CPU scheduling       # //
// # proccesses, such as FCFO, SJF, and SRT.   # //
// ############################################# //

#include <stdio.h>          // printf()
#include <stdlib.h>         // exit()
#include <sys/time.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_rng.h>


// Simulation info
struct Simulation
{
    double fcfo_att;
    double d_over_fcfo_att;

    double sjf_att;
    double d_over_sjf_att;

    double srt_att;
    double d_over_srt_att;

    double d;
};

// Process
struct Process
{
    int pi;         // process ID
    int active;     // true/false
    int Ai;         // Arival Time
    int Ti;         // Execution Time
    int Ri;         // Remaining time
    int TTi;        // Turn Around Time
};


// init
// ---------------------------------------------------------------------------------------- //
int main (int argc, char *argv[]);
int randomNumber(int, int);

// Ai = Arrival Time
int *uniformDistribution (int, int);

// Ti = Service Time or Processor burst Time or Execution Time
int *gaussianDistribution (int, double, double);

// init some structures 
struct Simulation init(int n, int k, double d, double d_percentage);
// ---------------------------------------------------------------------------------------- //

// scheduler algorithms
// ---------------------------------------------------------------------------------------- //
struct Process *copyProcesses(struct Process processes[], int n);

struct Simulation simulation(struct Process processes[], int n, int d);

double simulationFCFO(struct Process processes[], int n, int d);

double simulationSJF(struct Process processes[], int n, int d);

double simulationSRT(struct Process processes[], int n, int d);

// just nice print
void nicePrint(struct Process processes[], double att, int n, int d);

// Average Turn Around Time
double ATT(struct Process processes[], int n); 
// ---------------------------------------------------------------------------------------- //


// Generating numbers
// ---------------------------------------------------------------------------------------- //
// Each Ai is an integer chosen randomly from a uniform distribution 
// between 0 and some value k, where k is a simulation parameter.
// generating Arrival Time
int *uniformDistribution (int n, int k)
{
    // allocate memory for array with the size of n
    int *tmp = malloc (sizeof (int) * n);

    // Seed generation based on time
    struct timeval t_val;
    gettimeofday(&t_val, 0);
    unsigned long seed = t_val.tv_sec + t_val.tv_usec;

    const gsl_rng_type * T;
    gsl_rng * r;

    double a = 0.0;
    double b = (double) k;
    
    // create a generator chosen by the
    // environment variable GSL_RNG_TYPE 

    gsl_rng_env_setup();
    T = gsl_rng_default;
    r = gsl_rng_alloc (T);
    gsl_rng_set(r, seed);

    // print n random variates chosen from
    // the poisson distribution with mean
    // parameter mu

    for (int i = 0; i < n; i++)
    {
        unsigned int x = gsl_ran_flat (r, a, b);
        tmp[i] = x;
    }
    
    gsl_rng_free (r);

    // first process arrival time in most cases have to be 0
    //tmp[0] = 0;

    return tmp;
}

// Each Ti is an integer chosen randomly from a normal (Gaussian) distribution 
// with an average d and a standard deviation v, where d and v are simulation parameters.
// generating Service Time
int *gaussianDistribution (int n, double d, double sigma)
{
    // allocate memory for array with the size of n
    int *tmp = malloc (sizeof (int) * n);

    // Seed generation based on time
    struct timeval t_val;
    gettimeofday(&t_val, 0);
    unsigned long seed = t_val.tv_sec + t_val.tv_usec;

    const gsl_rng_type * T;
    gsl_rng * r;

    gsl_rng_env_setup();
    T = gsl_rng_default;
    r = gsl_rng_alloc (T);
    gsl_rng_set(r, seed);

    // Print n random variates chosen from the gaussian distribution
    // with mean zero and standard deviation sigma.
     
    gsl_rng_set(r, seed);
    for (int i = 0; i < n; i++) 
    {
        double x = gsl_ran_gaussian_tail(r, d, sigma);
        tmp[i] = (( int) x );
    }

    gsl_rng_free (r);

    return tmp;
}
// ---------------------------------------------------------------------------------------- //

// ---------------------------------------------------------------------------------------- //
// find the average turnaround time
double ATT(struct Process processes[], int n)
{
    double att = 0.0;

    for (int i = 0; i < n; i++)
    {
        att = att + processes[i].TTi;
    }

    att = att / (double) n;

    return att;
}
// ---------------------------------------------------------------------------------------- //

// Copy processes
struct Process *copyProcesses(struct Process processes[], int n)
{
    struct Process *tmp = malloc(sizeof(struct Process) * n);

    for (int i = 0; i < n; i++)
    {
        tmp[i] = processes[i];
    }

    return tmp;
}

// Simulation
// ---------------------------------------------------------------------------------------- //
// FCFS: First-Come-First-Served is a non-preemptive
double simulationFCFO(struct Process processes[], int n, int d)
{
    printf("FCFO:\n");

    // Ti: Execution Time
    // Ai: Arival Time
    // Ri: Remaning Time

    int condition = 1, j = 0, t = 0;

    // loop via all processes
    for (int i = 0; i < n; i++)
    {
        // if any i-th process has Ri = 0 we should compute Ri value
        // basically it means that i-tj process is still in queue
        if (processes[i].Ri == 0)
        {
            // infinit while loop
            // loop vai all process while all of the process will not be executed
            while (condition)
            {
                // if: i-th process is active compute Ri and TTi values and remove it from queue
                // else: we have to increment 't' which is time variable
                if (processes[i].active == 1)
                {
                    // compute Ri and TTi values based on the Assignment description
                    processes[i].Ri = processes[i].Ti - t;

                    processes[i].TTi = t - processes[i].Ai;
                    //processes[i].TTi = processes[i].Ti + processes[i].Ri;

                    // set i-th process inactive
                    processes[i].active = 0;

                    // stop infinit while loop
                    condition = 0;

                    // update time variable 't'
                    // t = 0;
                    break;
                }
                else if (processes[i].active == 0)
                {
                    // if process is not active we have to increment 't'

                    // if 't' >= Ai it means this process can can take CPU time to be processed
                    if (t >= processes[i].Ai)
                    {
                        // indicate that this process is active
                        processes[i].active = 1;
                    }

                    // increment 't'
                    t = t + 1;
                }
                
                // 'j' is used to loop over all process infinit number of times, 
                // but if we make one process active, then we have to reset 'j' variable,
                // so next time we can start looping over process that left in a queue
                if (j >= n)
                {
                    j = 0;
                }

                // increment 'j'
                j = j + 1;
            }
            
        }

        // we have to reset 'j' and 'condition'
        j = 0;
        condition = 1;
    }

    // get average turnaround time
    double att = ATT(processes, n);

    // just nice print
    nicePrint(processes, att, n, d);

    return att;
}

// SJF: Shortest-Job-First is non-preemptive algorithm. 
double simulationSJF(struct Process processes[], int n, int d)
{
    printf("SJF:\n");

    // Sort processes in ascending order
    // ----------------------------------------------------------------------------------- //
    int index = 0;

    // Ti: Execution Time
    // Ai: Arival Time
    // Ri: Remaning Time

    // We have to sort all processes by Ti,
    // so we can use selection sort in order to sort processes in ascending order
    for(int i = 0; i < n; i++)
    {
        index = i;
        for(int j = (i+1) ; j < n; j++)
        {
            if(processes[j].Ti < processes[index].Ti)
            {
                index = j;
            }
        }
 
        // swap 
        struct Process tmp = processes[i];
        processes[i] = processes[index];
        processes[index] = tmp;
    }
    // ----------------------------------------------------------------------------------- //

    // Do calculations
    // ----------------------------------------------------------------------------------- //
    int condition = 1, j = 0, t = 0;

    // loop via all processes
    for (int i = 0; i < n; i++)
    {
        // if any i-th process has Ri = 0 we should compute Ri value
        // basically it means that i-tj process is still in queue
        if (processes[i].Ri == 0)
        {
            // infinit while loop
            // loop vai all process while all of the process will not be executed
            while (condition)
            {
                // if: i-th process is active compute Ri and TTi values and remove it from queue
                // else: we have to increment 't' which is time variable
                if (processes[i].active == 1)
                {
                    // compute Ri and TTi values based on the Assignment description
                    processes[i].Ri = processes[i].Ti - t;
                    
                    processes[i].TTi = t - processes[i].Ai;

                    // set i-th process inactive
                    processes[i].active = 0;

                    // stop infinit while loop
                    condition = 0;

                    // update time variable 't'
                    // t = 0;
                    break;
                }
                else if (processes[i].active == 0)
                {
                    // if process is not active we have to increment 't'

                    // if 't' >= Ai it means this process can can take CPU time to be processed
                    if (t >= processes[i].Ai)
                    {
                        // indicate that this process is active
                        processes[i].active = 1;
                    }

                    // increment 't'
                    t = t + 1;
                }
                
                // 'j' is used to loop over all process infinit number of times, 
                // but if we make one process active, then we have to reset 'j' variable,
                // so next time we can start looping over process that left in a queue
                if (j >= n)
                {
                    j = 0;
                }

                // increment 'j'
                j = j + 1;
            }
            
        }

        // we have to reset 'j' and 'condition'
        j = 0;
        condition = 1;
    }

    // get average turnaround time
    double att = ATT(processes, n);

    // just nice print
    nicePrint(processes, att, n, d);
    // ----------------------------------------------------------------------------------- //

    return att;
}

// SRT: Shortest-Remaining-Time-First is preemptive algorithm
// It is preemptive version of the SJF.
double simulationSRT(struct Process processes[], int n, int d)
{
    printf("SRT:\n");

    // Sort processes in ascending order
    // ----------------------------------------------------------------------------------- //
    int index = 0;

    // Ti: Execution Time
    // Ai: Arival Time
    // Ri: Remaning Time

    // We have to sort all processes by Ai,
    // so we can use selection sort in order to sort processes in ascending order
    for(int i = 0; i < n; i++)
    {
        index = i;
        for(int j = (i+1) ; j < n; j++)
        {
            if(processes[j].Ai < processes[index].Ai)
            {
                index = j;
            }
        }
 
        // swap 
        struct Process tmp = processes[i];
        processes[i] = processes[index];
        processes[index] = tmp;
    }
    // ----------------------------------------------------------------------------------- //

    // Do calculations
    // ----------------------------------------------------------------------------------- //
    int condition = 1, j = 0, t = 0;

    // loop via all processes
    for (int i = 0; i < n; i++)
    {
        // if any i-th process has Ri = 0 we should compute Ri value
        // basically it means that i-tj process is still in queue
        if (processes[i].Ri == 0)
        {
            // infinit while loop
            // loop vai all process while all of the process will not be executed
            while (condition)
            {
                // if: i-th process is active compute Ri and TTi values and remove it from queue
                // else: we have to increment 't' which is time variable
                if (processes[i].active == 1)
                {
                    // compute Ri and TTi values based on the Assignment description
                    processes[i].Ri = processes[i].Ti - t;
                    
                    processes[i].TTi = t - processes[i].Ai;

                    // set i-th process inactive
                    processes[i].active = 0;

                    // stop infinit while loop
                    condition = 0;

                    // update time variable 't'
                    // t = 0;
                    break;
                }
                else if (processes[i].active == 0)
                {
                    // if process is not active we have to increment 't'

                    // if 't' >= Ai it means this process can can take CPU time to be processed
                    if (t >= processes[i].Ai)
                    {
                        // indicate that this process is active
                        processes[i].active = 1;
                    }

                    // increment 't'
                    t = t + 1;
                }
                
                // 'j' is used to loop over all process infinit number of times, 
                // but if we make one process active, then we have to reset 'j' variable,
                // so next time we can start looping over process that left in a queue
                if (j >= n)
                {
                    j = 0;
                }

                // increment 'j'
                j = j + 1;
            }
            
        }

        // we have to reset 'j' and 'condition'
        j = 0;
        condition = 1;
    }

    // get average turnaround time
    double att = ATT(processes, n);

    // just nice print
    nicePrint(processes, att, n, d);
    // ----------------------------------------------------------------------------------- //

    return att;
}

// Start proccesses simulation
struct Simulation simulation(struct Process processes[], int n, int d)
{
    
    struct Process *tmp1 = copyProcesses(processes, n);
    struct Process *tmp2 = copyProcesses(processes, n);
    struct Process *tmp3 = copyProcesses(processes, n);
    
    // printf("Generated numbers for FCFO - SJF - SRT:\n");
    // nicePrint(processes, -1, n, d);

    double FCFO = simulationFCFO(tmp1, n, d);
    double SJF = simulationSJF(tmp2, n, d);
    double SRT = simulationSRT(tmp3, n, d);

    struct Simulation simulation;
    simulation.fcfo_att = FCFO;
    simulation.d_over_fcfo_att = d / FCFO;
    simulation.sjf_att = SJF;
    simulation.d_over_sjf_att = d / SJF;
    simulation.srt_att = SRT;
    simulation.d_over_srt_att = d / SRT;
    simulation.d = d;

    return simulation;
}
// ---------------------------------------------------------------------------------------- //

// just nice print
void nicePrint(struct Process processes[], double att, int n, int d)
{
    printf("pi - Active - Ai - Ti - Ri - TTi\n");
    for (int i = 0; i < n; i++)
    {
        int a = processes[i].active;
        int ai = processes[i].Ai;
        int ti = processes[i].Ti;
        int ri = processes[i].Ri;
        int tti = processes[i].TTi;

        printf(" %d -   %d/1  -  %d - %d -  %d -  %d\n", i, a, ai, ti, ri, tti );
    }
    printf("ATT ::: %f\n", att);
    printf("d/ATT ::: %f\n", (d / att) );
    printf("\n");
}

// INIT
// ---------------------------------------------------------------------------------------- //
struct Simulation init(int n, int k, double d, double d_percentage)
{
    // standard deviation, (for simplicity, v could be just a fixed percentage of d)
    double v = d / 100.0 * d_percentage;

    // The value k/n represents the frequency of process arrivals. 
    double fpa = k / n;

    // init some data
    // ----------------------------------------------------------- //
    // Generate processes
    struct Process processes[n];

    // Generate arrival times for processes
    int *Ai = uniformDistribution(n, k);

    // first process arrival time in most cases have to be 0
    Ai[0] = 0;

    // Generate processes Execution Time, also known as a Service Time or a Processor burst Time
    // CPU Burst: It is the amount of time required by a process 
    // or can be said the amount of time required by the process to finish
    int *Ti = gaussianDistribution(n, d, v);

    // The field “active” indicates whether the process is currently competing for the CPU.
    // The value becomes 1 at the time of process arrival and 0 at the time of process termination.
    // Initially, the value is set to 1 for all processes with arrival time Ai = 0.

    // init processes
    for (int i = 0; i < n; i++)
    {
        processes[i].pi = i;

        if (Ai[i] == 0)
        {
            processes[i].active = 1;
        }
        else
        {
            processes[i].active = 0;
        }

        processes[i].Ai = Ai[i];
        processes[i].Ti = Ti[i];
        processes[i].Ri = 0;
        processes[i].TTi = 0;
    }    

    // ----------------------------------------------------------- //

    return simulation(processes, n, d);
}

int main (int argc, char *argv[])
{
    // ----------------------------------------------------------- //
    // Ai = Arrival Time
    // Ti = Service Time or Execution Time
    // Ri = Waiting Time 
    // ----------------------------------------------------------- //

    // working with arguments
    // ----------------------------------------------------------- //
    // number of processes
    int n = atoi(argv[1]);

    // Each Ai is an integer chosen randomly from a uniform distribution 
    // between 0 and some value k, where k is a simulation parameter.
    // k is max arrival time 
    int k = atoi(argv[2]);

    // Each Ti is an integer chosen randomly from a normal (Gaussian) distribution
    // with an average d and a standard deviation v, where d and v are simulation parameters.
    // an average total CPU time
    double d = atoi(argv[3]);

    // standard deviation, (for simplicity, v could be just a fixed percentage of d)
    double d_percentage = atoi(argv[4]);

    // simulation circles
    int sc = atoi(argv[5]);
    // ----------------------------------------------------------- //

    // Handle negative input
    if (sc < 0)
    {
        sc = -1 * sc;
    }

    // basic cheack of cycles number
    if (sc == 0)
    {
        printf("Simulation Circles is -{ %d }-, nothing to simulate\n", sc);
    }
    else
    {
        // Run simulation 'sc' number of times
        struct Simulation simulations[sc];
        for (int i = 0; i < sc; i++)
        {
            simulations[i] = init(n, k, d, d_percentage);
        }

        printf("\nCSV output:\n");
        printf("d,d/FCFO_ATT,d/SJF_ATT,d/SRT_ATT\n");
        for (int i = 0; i < sc; i++)
        {
            double fcfo_att = simulations[i].fcfo_att;
            double sjf_att = simulations[i].sjf_att;
            double srt_att = simulations[i].srt_att;

            double d_over_fcfo_att = simulations[i].d_over_fcfo_att;
            double d_over_sjf_att = simulations[i].d_over_sjf_att;
            double d_over_srt_att = simulations[i].d_over_srt_att;
            double d = simulations[i].d;

            printf("%.2f,%.2f,%.2f,%.2f\n", d, d_over_fcfo_att, d_over_sjf_att, d_over_srt_att);
        }

    }
}
// ---------------------------------------------------------------------------------------- //