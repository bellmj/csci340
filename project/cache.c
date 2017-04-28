#include <stdio.h>	/* for printf */
#include <stdint.h>	/* for uint64 definition */
#include <stdlib.h>	/* for exit() definition */
#include <time.h>

#define BILLION 1E9
int sleep();
int main(int argc, char** argv){
  uint64_t diff;
  struct timespec start,end;
  clock_gettime( CLOCK_MONOTONIC ,&start);
  sleep(1);
  clock_gettime(CLOCK_MONOTONIC,&end);
  diff =  BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
  printf("%ld\n",diff );

  int * dataArray;
  dataArray = malloc(2 * 1024 * 1024 * 8);// allocate 16 meg in memory
  uint64_t totalns = 0;
  for(int z = 0; z < 100; z += 1){
    // for(int i = 0; i < 10000; i += 1){
    //    system("sync");//clear cache
    //   clock_gettime( CLOCK_MONOTONIC ,&start);//start timer
    //   dataArray[0];//access memory
    //   clock_gettime(CLOCK_MONOTONIC,&end);//stop timer
    //   diff =  BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;//calculate time in nS
    //   totalns += diff;
    // }
    // printf("%f\n",totalns/10000.0 );

    totalns = 0;
    uint64_t lastMiss = 0;
    int numberofmisses = 0;
    uint64_t totallenofmisses = 0;
    system("sync");//clear cache
    for(int i = 0; i < 2 * 1024 * 1024 * 8; i += 1){
      // system("sync");//clear cache
      clock_gettime( CLOCK_MONOTONIC ,&start);//start timer
      dataArray[i];//access memory
      clock_gettime(CLOCK_MONOTONIC,&end);//stop timer
      diff =  BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;//calculate time in nS
      if(diff>60){//likely a cache miss
        //printf("memory access time %ld at index %d\n",diff, i );
        numberofmisses += 1;
        totallenofmisses += i - lastMiss;
        lastMiss = i;
      }
      totalns += diff;
    }
    printf("%f\n",totalns/(2.0 * 1024 * 1024 * 8) );
    printf("%f\n",totallenofmisses * 1.0 /numberofmisses );
  }


}
