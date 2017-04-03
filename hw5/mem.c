#include <stdio.h>    /* for printf statements when debugging */
#include <stdlib.h>   /* for malloc() and free() */
#include "mem.h"

/*
  Physical memory array. This is a static global array for all
  functions in this file.  An element in the array with a value of
  zero represents a free unit of memory.
*/
static dur_t* memory;

/*
 The size (i.e. number of units) of the physical memory array. This is
 a static global variable used by functions in this file.
 */
static int mem_size;


/*
 The last_placement_position variable contains the end position of the
 last allocated unit used by the next fit placement algorithm.
 */
static int last_placement_position;

/*
  Using the memory placement algorithm, strategy, allocate size
  units of memory that will reside in memory for duration time units.

  If successful, this function returns the number of contiguous blocks
  (a block is a contiguous "chuck" of units) of free memory probed while
  searching for a suitable block of memory according to the placement
  strategy specified.  If unsuccessful, return -1.

  If a suitable contiguous block of memory is found, the first size
  units of this block must be set to the value, duration.
 */
int mem_allocate(mem_strats_t strategy, int size, dur_t duration)
{
  int size_of_chunk = 0;
  int size_of_bestfit_chunk = 2147483647;//MAX_VALUE
  int start_of_chunk = -1;
  int blocks_probed = 0;
  int start_of_bestfit_chunk = -1;
  switch (strategy){
    case BESTFIT:
      size_of_chunk = 0;
      start_of_bestfit_chunk = -1;
      start_of_chunk = -1;
      blocks_probed = 0;
      for(int i = 0;i < mem_size;i += 1){
        if(memory[i]==0&&i != mem_size-1){
          if(size_of_chunk==0){
            start_of_chunk = i;
            blocks_probed += 1;
          }
          size_of_chunk += 1;
        }else if(i==mem_size-1 ||(i != 0 && memory[i-1]==0)){// if were at the end of a chunk
          if(size_of_bestfit_chunk > size_of_chunk && size_of_chunk >= size){//if the chunk we found is smaller than the last best fit
            size_of_bestfit_chunk = size_of_chunk;                           //chunk found and this chunk is still big enough to fit the allocation
            start_of_bestfit_chunk = start_of_chunk;
          }
        }else{
          size_of_chunk = 0;
          start_of_chunk = -1;
        }

      }
      //have found the start_of_bestfit_chunk and the size_of_bestfit_chunk at this point
      //printf("%d\t0x%02x\n",size_of_bestfit_chunk,start_of_bestfit_chunk );
      for(int i = start_of_bestfit_chunk; i < start_of_bestfit_chunk + size; i = i + 1){
        memory[i] = duration;
      }
      return blocks_probed;
      break;
    case FIRSTFIT:
      size_of_chunk = 0;
      start_of_chunk = -1;
      blocks_probed = 0;
      for(int i = 0; i < mem_size; i = i + 1){
        if(memory[i]==0){
          if(size_of_chunk==0){
            //found a start of a block
            blocks_probed += 1;//
            start_of_chunk = i;
          }
          size_of_chunk += 1;
          if(size_of_chunk>=size){//if the chunk we found is large enough to allocate what the user is requesting
            //printf("%d\t%d\n",size_of_chunk,size );
            break;
          }
        }else{//if we out of a chunk
          size_of_chunk = 0;
          start_of_chunk = -1;
        }
      }
      //allocate chunk
      for(int i = start_of_chunk; i < start_of_chunk + size; i = i + 1){
        memory[i] = duration;
      }
      //if there is no space in memory for the allocation return -1;
      return (start_of_chunk == -1 ? start_of_chunk : blocks_probed);

      break;
    case NEXTFIT://can do a reset for the next counter to check and see if were in a continuous chunk of memory
      //TODO finish immplementing this algorithm
      //printf("%d\n",size );
      blocks_probed = 0;
      //printf("%s0x%02x\n","last placement position: ", last_placement_position );
      if(last_placement_position != 0 && memory[last_placement_position] == 0 && memory[last_placement_position-1] == 0){//if were in the middle of a bigger chunk.
        while(last_placement_position != 0 && memory[last_placement_position]==0){//while were not at the start of a chunk
          last_placement_position -= 1;//walk the last_placement_position pointer backwards
        }
        //printf("Placement position move to:0x%02x\n", last_placement_position );
      }
      for(int i = last_placement_position; i < mem_size;i += 1){
        if(memory[i] == 0){//if we're at the start of a block
            blocks_probed += 1;
            size_of_chunk = 1;
            start_of_chunk = i;
            i = i + 1;
            while(memory[i] == 0 && i < mem_size){
                size_of_chunk += 1;
                if(size_of_chunk >= size){//if we can allocate here
                  //printf("%s\n", "we can allocate here");
                  last_placement_position = start_of_chunk;
                    for(int index = start_of_chunk; index < start_of_chunk + size; index = index + 1){//allocate starting at start_of_chunk
                        memory[index] = duration;
                    }
                    return blocks_probed;
                }
                i = i + 1;
            }
            i -= 1;//have to decrement i since the for loop will increment i to be greater than size by the final iteration

        }
        //if we get to the end and we haven't repeated; repeat
        if(i == mem_size - 1){//if were at the end and haven't found an allcation spot
          //printf("%s\n","started at top" );
            for(int i = 0; i < last_placement_position; i += 1){
            if(memory[i]==0){
              blocks_probed += 1;
              size_of_chunk = 1;
              start_of_chunk = i;
              i = i + 1;
              while(memory[i] == 0 && i < mem_size){
                size_of_chunk += 1;
                if(size_of_chunk >= size){//if we can allocate here
                  last_placement_position = start_of_chunk;
                  for(int index = start_of_chunk; index < start_of_chunk + size; index = index + 1){
                    last_placement_position = start_of_chunk;
                    memory[index] = duration;
                  }
                  return blocks_probed;
                }
                i += 1;
              }
            }


            }
            //if we can't fit the block in the second part or the first part then return -1
            return -1;
        }
      }

  }
  return 0;
}

/*
  Go through all of memory and decrement all positive-valued entries.
  This simulates one unit of time having transpired.  NOTE: when a
  memory cell is decremented to zero, it becomes "unallocated".
 */
int mem_single_time_unit_transpired()
{
  for(int i = 0; i < mem_size; i = i + 1){
    if(memory[i]>0)
      memory[i] -= 1;
  }
  return 0;
}

/*
  Return the number of fragments in memory.  A fragment is a
  contiguous free block of memory of size less than or equal to
  frag_size.
 */
int mem_fragment_count(int frag_size)
{
  int start_of_chunk = 0;
  int size_of_chunk = 0;
  int frag_count = 0;
  for(int i = 0; i < mem_size; i += 1){
    if(memory[i] == 0){//if were in a chunk
      if(i == 0 || memory[i-1] != 0){//if were a the start of a chunk
        start_of_chunk = 0;
      }
      size_of_chunk += 1;
    }else if( i == mem_size - 1 || (i != 0 && memory[i-1] == 0)){//else if we're at the end of  chunk
      if(size_of_chunk <= frag_size){
        frag_count += 1;
      }
      size_of_chunk = 0;
    }
  }
  return frag_size;
}

/*
  Set the value of zero to all entries of memory.
 */
void mem_clear()
{
  unsigned char zero = 0;
  for(int i = 0; i < mem_size;i = i + 1){
    memory[i] = zero;
  }
}

/*
 Allocate physical memory to size. This function should
 only be called once near the beginning of your main function.
 */
void mem_init(int size)
{
  memory = malloc(sizeof(dur_t)*size);
  mem_size = size;
  last_placement_position = 0;
}

/*
 Deallocate physical memory. This function should
 only be called once near the end of your main function.
 */
void mem_free()
{
  free(memory);
}

/*
  Print memory for testing/debugging purposes.  This is an optional
  routine to write, but highly recommended!  You will need to test and
  debug your allocation algorithms.  Calling this routine in your
  main() after every allocation (successful or not) will help in this
  endeavor.  NOTE: you should print the memory contents in contiguous
  blocks, rather than single units; otherwise, the output will be very
  long.
 */
void mem_print()
{
  printf("\n%s\n","\t\t\t\t\t\t\t\tPicture Of Memory\n" );
  printf("%s\t","" );
  for(int i = 0; i < 16; i +=1){
      printf("xxx%01x\t", i);
  }
  printf("%s\n","" );
   for(int i = 0; i <= mem_size-1; i = i + 1){
     if((i)%16 == 0){
       printf("%s\n","" );
       printf("%s\n", "");
       printf("%03xx\t",(i)/16);
     }
     if(memory[i]==0){
       printf(" %s\t","X");
     }else{
       printf(" %d\t",memory[i]);
     }
   }
   printf("%s\n","" );
}
