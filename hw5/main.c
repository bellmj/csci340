#include <stdio.h>    /* for printf */
#include <stdlib.h>   /* for string to integer conversion, random numbers */
#include "mem.h"
/*
  Output: Decimal
    average external fragmentation(Number of fragmenst that are less than the min request size); nuber of probes; number of allocation failures; For each algorithm output is nine diffrent lines
  Ex.
    numruns:100
    timeforsimulation:1000
    sizeofmemory:3000

    Need to make make file
      make file captures dependencies

    hw5: main.o men.o
      gcc main.o men.o -o hw5
    main.o : main.c mem.h
      gcc -c main.c -Wall
    mem.o : mem.c mem.h
      gcc -c -Wall mem.c

    -c : complile but don't link



    BEfore each run clear out memory slots into zero
    random numbers for size and durration are generated in main and passed into mem_allocate

    for(x=BESTFIT;x<=NEXTFIT;x++){
    }

  }


*/
/*
  The main program will accept four paramemters on the command line.
  The first parameter is the memory size.  The second parameter is the
  duration of the each simulation run.  The third parameter is the
  number of times to repeat each experiment (ie. number of runs). The
  fourth parameter is a random number seed. Here is an example command
  line:

  ./hw5 1000 3000 100 1235

  This means that your program should initialize physical memory to
  1,000 units, perform 100 runs with each run taking 3000 units of
  time, and the random number generator should be seeded (one time)
  with the value 1235.
*/
// generate random int in range [min, max]
int myrand_r( long min, long max)
{
  return (max - min + 1 ) * ((double)rand()/RAND_MAX) + min;
}
int main(int argc, char** argv)
{
  int sizeofmemory = atoi(argv[1]);
  int durationOfSim = atoi(argv[2]);
  int timesRepeat = atoi(argv[3]);
  int seed = atoi(argv[4]);
  srand(seed);
  mem_init(sizeofmemory);
  for(int i = 0; i < 1; i = i + 1){//only repeat once
    int bestfit_allocation_faults = 0;
    int bestfit_number_of_probes = 0;
    double bestfit_fragmentation = 0.0;
    int firstfit_allocation_faults = 0;
    int firstfit_number_of_probes = 0;
    double firstfit_fragmentation = 0.0;
    int nextfit_allocation_faults = 0;
    int nextfit_number_of_probes = 0;
    double nextfit_fragmentation = 0.0; 
    for(dur_t x=BESTFIT;x<=NEXTFIT;x += 1){//only testing best fit.
      int allocation_faults = 0;
      int totalNumberOfProbes = 0;
      int numberOfProbes = 0;
      double average_external_fragmentation = 0.0;
      for(int simdur = durationOfSim; simdur > 0; simdur -= 1){
//printf("%d\n",simdur );
        numberOfProbes = mem_allocate(x,myrand_r(7,57),myrand_r(13,27));
        if(numberOfProbes == -1){//if there was a allocation fault
          allocation_faults += 1;
          printf("%s\n", "\tALLOCATION FAULT");
        }else{
          totalNumberOfProbes += numberOfProbes;
        }
        average_external_fragmentation += mem_fragment_count(MIN_REQUEST_SIZE);
        mem_single_time_unit_transpired();
      }
        average_external_fragmentation = average_external_fragmentation/durationOfSim;
      printf("%s%d%s%f\n","The average external Fragmentation for ", x ," is ", average_external_fragmentation);
      printf("%s%d%s\n","there were ", allocation_faults, " allocation_faults" );
      printf("%s%d%s\n","There were ",totalNumberOfProbes ," probes" );

    }
  }


  // printf("%d\n",sizeofmemory );
  // printf("%d\n",durationOfSim);
  // printf("%d\n",timesRepeat );
  // printf("%d\n",seed );
  //mem_init(sizeofmemory);
  //Testing code to make sure the functions in mem.c worked before I started with the testing
    // mem_print();
    // for(int i = 0; i < 50; i += 1){
    //   mem_allocate(BESTFIT,myrand_r(1,20),myrand_r(1,29));
    // }
    // mem_print();
    // for(int i = 0; i < 5; i += 1){
    //   mem_single_time_unit_transpired();
    // }
    // mem_print();
    // printf("number of probes:%d\n",mem_allocate(NEXTFIT,16,66));
    // mem_print();
    // for(int i = 0; i < 65; i = i + 1){
    //   mem_single_time_unit_transpired();
    // }
    // mem_print();
    // printf("number of probes:%d\n",mem_allocate(NEXTFIT,16,66));
    // mem_print();
    // for(int i = 0; i < 85; i += 1){
    //   printf("\t%d\n",(mem_allocate(NEXTFIT,myrand_r(1,20),myrand_r(1,29))));
    // }
    // mem_print();
    // for(int i = 0; i < 20; i = i + 1){
    //   mem_single_time_unit_transpired();
    // }
    // mem_print();
    // printf("\t%d\n",mem_allocate(NEXTFIT,16,66));
    // mem_print();

  return 0;
}
