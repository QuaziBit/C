# Hown to run application

### Step 0:
    type in terminal: <./Makefile> or <make> to compile application 

### Step 1:
    if make file is not working for some reason type these commands in terminal:
    :: gcc -c p_simulation.c
    :: gcc -o p_simulation p_simulation.o -lgsl -lgslcblas -lm

### Step 2:
    after compilation run application:
    :: ./p_simulation n k d d_percentage sc
    :: -> n = number of processes
    :: -> k = max arrival time
    :: -> d = average total CPU time
    :: -> d_percentage = fixed percentage of d for standard deviation v
    :: -> sc = simulation circles
   
    Here is example:
    :: ./p_simulation 10 10 10 85.0 10

### Summary of the program:
    Function 'init' will generate 'Uniform Distribution' and 'Gaussian Distribution'.
    After, three simulation functions will be executed 'simulationFCFO', 'simulationSJF', 'simulationSRT'.
    Each of these simulation functions will return a structure of current simulation.
    The simulation structure will hold all necessary variables to calculate 'd/ATT' for each
    scheduling algorithm.

    On the end, this application prints summary of simulation, basically it will
    print output in 'CSV' format, so you can copy and paste it into Microsoft Excel to build graphs.

### Simulation demo video:
YouTube video: <https://youtu.be/Lu0SlSFrZ7Q>