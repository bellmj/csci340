Joe Lester
Matt Bell

mainmemoryaccesstime: This function determines the average access time of the main memory. This is accomplished by allocating an array that is 		known to be larger than the cache (i.e. 16 MB) and populating it with integer values. Then this array is looped through 10000 times and 	each time the cache is flushed and then the access of one of the elements is accessed and timed. The average is accumulated and before it 		is returned the average is computed.

averageCacheAccessTime: As above this function determines the average access time of the cache. This is accomplished by allocating an array that 		is known to be larger than the cache (i.e. 16 MB) and populated with integer values. It is then looped through 10000 times where the 		first access ensures that the cache is populated, then the timed access is one ahead of the first access. Before the accumualted access 	times are returned they are averaged.

findCacheSize: 



findCacheBlockSize: We take an array larger than the cache (i.e. 16 MB) and populate it with integer values. We then loop through the some value 	of the array to determine a pattern of longer time calls at specific intervals. we assume these intervals to be 64 bytes apart or 16 ints 	apart. Since an int is 4 bytes then the pattern of longer calls should represent the line size of the cache itself. 
