#include <stdio.h>	/* for printf */
#include <stdint.h>	/* for uint64 definition */
#include <stdlib.h>	/* for exit() definition */
#include <time.h>
#include <math.h>
#include "cache_1.h"

#define BILLION 1E9

double mainmemoryaccesstime(){
	static int array[10000][10000];
	struct timespec start, end;
	clock_gettime(CLOCK_REALTIME, &start);
	for(int i = 0; i < 10000; i++){
	
		array[i][0] += 10;
	
	}
	clock_gettime(CLOCK_REALTIME, &end);
	
	double accum = ( end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec)/10000;	 	
	
	return accum;

}


double averageCacheAccessTime(){
	
	static int array[10000][10000];
	struct timespec start, end;

	clock_gettime(CLOCK_REALTIME, &start);

	for(int i = 0; i < 10000; i++){
		for(int j = 0; j < 10000; j++){
			array[i][j] += 10;
		}
	}

	clock_gettime(CLOCK_REALTIME, &end);	

	double accum = ( end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec)/ (10000 * 10000);
	return accum;
}

int findCacheSize(double x){
	int size = 0;
	
	return size;
}

int findCacheBlockSize(){

	struct timespec start,end;
	static int array[10000];	
	int size = 0;
	

	return size;
}

int main(int argc, char** argv){
	

	double timeDifference;

	timeDifference = mainmemoryaccesstime();
	printf("Average Time For Main Memory Access: %lf\n", timeDifference);

	timeDifference = 0.0;
	for(int i = 0; i < 20; i++){
		timeDifference += averageCacheAccessTime();			
		
	}

	timeDifference = timeDifference / 20;
	printf("Time for Average Cache Access: %lf\n", timeDifference);
	
	int cacheSize = 0;
	for(int i = 1; i < 20; i++){

		double mallocSetting = pow(i,2);
		findCacheSize(mallocSetting);

	}
	printf("Total Cache Size : %d\n", cacheSize);

	int cacheBlockSize = findCacheBlockSize();
	printf("Total Cache Block Size: %d\n", cacheBlockSize);
}
