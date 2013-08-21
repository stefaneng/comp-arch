#include <stdio.h>
#include <stdlib.h>

/* declare global var's */
int mem_size, cache_size, block_size;
/* define structure of dynamic cache and initialize var */
typedef struct _cache {
  int tag;
  int *block;
} cache;

/* define dynamic array for main memory */
cache *my_cache;
int *main_mem;

/**********************************************************************/
void enter_params()
{
  /* declare local var's */
  mem_size = cache_size = block_size = -1;
  /* Prompt for main memory size, cache size, block size */
  printf("Enter main memory size (words): ");
  scanf("%d", &mem_size);
  printf("Enter cache size (words): ");
  scanf("%d", &cache_size);
  printf("Enter block size (words/block): ");
  scanf("%d", &block_size);
  /* allocate and initialize main memory--value at index i = size of main memory-i*/
  main_mem = (int *) malloc(mem_size * sizeof(int));
  int i;
  for(i = 0; i < mem_size; i++) {
    *(main_mem + i) = mem_size-i;
  }

  /* allocate memory for cache based on number of lines in cache*/
  my_cache = (struct _cache *) malloc((cache_size/block_size) * sizeof(struct _cache));
  
  return;
}


/**********************************************************************/
void access_cache()
{
  /* declare local var's */
  int rw, write_num, mm_add, c_add, miss, hit, word, tag;
  hit = 0;
  /* Prompt for read/write signal */
  printf("Select read (0) or write (1): ");
  scanf("%d", &rw);

  /* Prompt for main memory address to read/write */
  if(rw) {
    printf("Enter main memory address to write to: ");
    scanf("%d", &mm_add);
    printf("Enter value to write: ");
    scanf("%d", &write_num);
  }
  else {
    printf("Enter main memory address to read from: ");
    scanf("%d", &mm_add);
  }
  /* Translate main mem addr to cache addr fields*/
  c_add = (mm_add/block_size)%(cache_size/block_size);
  tag = mm_add/cache_size;
  if(my_cache[c_add].tag) {
    /* MISS--NON-MATCHING TAG */
    if(my_cache[c_add].tag != tag) {
      miss = 1;
    }
    /* Otherwise no miss */
    else { 
      miss = 0;
    }
  }
  else {
    /* MISS--BLOCK NOT ALLOCATED
     * Allocate cache block based on block size */
    miss = 1;
    cache new_cache = {c_add, (int *) malloc(sizeof(int)*block_size)};
    my_cache[c_add] = new_cache;
  }

  /* Print message of Read/Write miss */
  if(miss && rw) printf("Write Miss!\n");
  else if(miss && !rw) printf("Read Miss!\n");
  else if(!miss && rw) printf("Write hit!\n");
  else printf("Read Hit!\n");

  /* Overwrite tag */
  my_cache[c_add].tag = tag;

  /* Transfer equivalent block of main memory to cache--one word at a time */
  int i;
  for(i = 0; i < block_size-1; i++) {  
    if(c_add*cache_size+1 == mm_add) hit = i;
    (my_cache[c_add].block)[i] = main_mem[mm_add+i];
  }
  /* HIT--reference cache word, transfer data to/from cache and print message*/
  if(rw) {
    main_mem[mm_add] = write_num;
    (my_cache[c_add].block)[hit] = write_num;
  }
  /* Print message of word, block, tag, data value */
  printf("Word %d of block %d with tag %d contains value %d\n",
  	 mm_add%block_size, c_add, my_cache[c_add].tag,
	 (my_cache[c_add].block)[hit]);
  return;
}


/**********************************************************************/
int main()
{
/* declare local var's */

/* until program exits, print menu, select choice via switch statement and call appropriate function*/
 int loop = 1;
 int input = -1;
  /* Run the loop until the user chooses quit */
  while(loop) {
    printf("Main memory to Cache memory mapping:\n");
    printf("------------------------------------\n");
    printf("1) Enter parameters\n");
    printf("2) Access cache for reading/writing and transfer data\n");
    printf("3) Quit\n\n");
    printf("Enter selection: ");
    scanf("%d", &input);
    switch(input) {
    case 1:
      enter_params();
      break;
    case 2:
      access_cache();
      break;
    case 3:
      loop = 0;
      break;
    default:
      printf("Invalid selection.");
    }
    printf("\n\n");
  }

  return 0;
}
