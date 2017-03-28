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

  ./hw7 1000 3000 100 1235

  This means that your program should initialize physical memory to
  1,000 units, perform 100 runs with each run taking 3000 units of
  time, and the random number generator should be seeded (one time)
  with the value 1235.
*/

int main(int argc, char** argv)
{
  int sizeofmemory = atoi(argv[1]);
  int durationOfSim = atoi(argv[2]);
  int timesRepeat = atoi(argv[3]);
  int seed = atoi(argv[4]);
  // printf("%d\n",sizeofmemory );
  // printf("%d\n",durationOfSim);
  // printf("%d\n",timesRepeat );
  // printf("%d\n",seed );
  mem_init(sizeofmemory);
  mem_print();
  mem_free();
  return 0;
}
