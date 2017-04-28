#include <stdio.h>	/* for printf */
#include <stdint.h>	/* for uint64 definition */
#include <stdlib.h>	/* for exit() definition */
#include <time.h>
#include <math.h>
#include "cache_1.h"

#define BILLION 1E9

double mainmemoryaccesstime(){
	static int * dataArray;
	dataArray = malloc(2 * 1024 * 1024 * 8);// allocate 16 meg in memory
	for(int i = 0; i < 1024 * 1024 * 2 ; i++){
		 dataArray[i] = 1;
	}
	struct timespec start, end;

	double totalns = 0.0;
	int what;
	for(int i = 0; i < 10000; i++){
			 system("sync");
			clock_gettime(CLOCK_REALTIME, &start);
		 	what = dataArray[i];
		 	clock_gettime(CLOCK_REALTIME, &end);
		 double accum = (( end.tv_sec - start.tv_sec)*BILLION + (end.tv_nsec - start.tv_nsec));
		 totalns += accum;
	}

	return totalns/(double)10000;

}


double averageCacheAccessTime(){
	static int * dataArray;
	dataArray = malloc(2 * 1024 * 1024 * 8);// allocate 16 meg in memory
	for(int i = 0; i < 1024 * 1024 * 2 ; i++){
		 dataArray[i] = 1;
	}
	struct timespec start, end;
	printf("%s\n","top of for" );
	double totalns = 0.0;
	int what;
	for(int i = 0; i < 10000; i++){

		 what = dataArray[0];
		  clock_gettime(CLOCK_REALTIME, &start);
		 	what = dataArray[0];
		 clock_gettime(CLOCK_REALTIME, &end);
		  double accum = (( end.tv_sec -start.tv_sec)*BILLION + (end.tv_nsec - start.tv_nsec));
			 totalns += accum;
		 }

	return totalns/(double)10000;
	// static int * dataArray;
	// dataArray = malloc(2 * 1024 * 1024 * 8);// allocate 16 meg in memory
	// struct timespec start, end;
	// for(int i = 0; i < 10000; i++){
	// 	clock_gettime(CLOCK_REALTIME, &start);
	// 		dataArray[i] = 1;
	// }
	//
	// clock_gettime(CLOCK_REALTIME, &end);
	//
	// double accum = ( end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec)/ (10000 * 10000);
	// return accum;
}

int findCacheSize(double x){
	int size = 0;

	return size;
}

int findCacheBlockSize(){

	static int * dataArray;
	dataArray = malloc(2 * 1024 * 1024 * 8);// allocate 16 meg in memory
	for(int i = 0; i < 1024 * 1024 * 2 ; i++){
		 dataArray[i] = i;
	}
	struct timespec start, end;
	printf("%s\n","top of for" );
	double totalns = 0.0;
	int what;
	int value[2];
	for(int i = 0; i < 1000; i++){

		 what = dataArray[0];
			clock_gettime(CLOCK_REALTIME, &start);
			what = dataArray[i];
		 clock_gettime(CLOCK_REALTIME, &end);
			double accum = (( end.tv_sec -start.tv_sec)*BILLION + (end.tv_nsec - start.tv_nsec));
			 if(accum>149){

				if(value[2] == value[1]){								
				 	value[1]=i;

				}else if(value[2] == value[1]){
					value[2] = i;			
				}else{
					value[1] = i;				
				}
		 	}
		 }

	return value[2] - value[1];
}

int main(int argc, char** argv){


	double timeDifference;

	timeDifference = mainmemoryaccesstime();
	printf("Average Time For Main Memory Access: %lf\n", timeDifference);

	printf("Time for Average Cache Access: %lf\n",averageCacheAccessTime());
	int cacheSize = 0;
	for(int i = 1; i < 20; i++){

		double mallocSetting = pow(i,2);
		findCacheSize(mallocSetting);

	}
	printf("Total Cache Size : %d\n", cacheSize);

	int cacheBlockSize = findCacheBlockSize() * 4;
	printf("Total Cache Block Size: %d Bytes\n", cacheBlockSize);
}
