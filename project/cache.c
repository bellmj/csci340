#include <stdio.h>	/* for printf */
#include <stdint.h>	/* for uint64 definition */
#include <stdlib.h>	/* for exit() definition */
#include <time.h>
#define BILLION 1000000000L
int main(){
  uint64_t diff;
  struct timespec start, end;
  clock_gettime( CLOCK_THREAD_CPUTIME_ID ,&start);
  sleep(1);
  clock_gettime(CLOCK_THREAD_CPUTIME_ID,&end);
  diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
  printf("%s\n",diff );
}
main();
