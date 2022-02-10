#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  // Compute the counts of values that appear in a particular input file 
  counts_t * cnt = createCounts();
  FILE * f = fopen(filename, "r");
  if(f==NULL){
    perror("Could not open file\n");
    exit(EXIT_FAILURE);
  }
   
  char * key=NULL;
  size_t sz;
  while(getline(&key, &sz, f)>=0){
    char * p = strchr(key, '\n');
    *p='\0'; 
    addCount(cnt, lookupValue(kvPairs, key));
    //key=NULL;
  }
  free(key);
  if(fclose(f)!=0){
    perror("Could not close file\n");
    exit(EXIT_FAILURE);
  }
  
  return cnt;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  if(argc<3) {
    fprintf(stderr, "Invalid number of parameters\n");
    exit(EXIT_FAILURE);
  }

  kvarray_t * kv = readKVs(argv[1]); 
 
  for(size_t i=2; i<argc; i++){
    counts_t * c = countFile(argv[i], kv);  
  //count from 2 to argc (call the number you count i)

    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)

    //compute the output file name from argv[i] (call this outName)
    char * outName = computeOutputFileName(argv[i]);

    //open the file named by outName (call that f)
    FILE * f = fopen(outName, "w");
    if(f==NULL){
      perror("Could not write file outName\n");
      exit(EXIT_FAILURE);
    }

    //print the counts from c into the FILE f
    printCounts(c, f);

    //close f
    if(fclose(f)!=0){
      perror("Could not close file outName\n");
      exit(EXIT_FAILURE);
    }
 
    //free the memory for outName and c
    free(outName);
    freeCounts(c);

  }


 //free the memory for kv
  freeKVs(kv);
  return EXIT_SUCCESS;
}
