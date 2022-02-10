#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}


//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}


void printResults(char ** data, size_t n){
  for(size_t i = 0; i<n; i++){
    printf("%s", data[i]); 
    free(data[i]);
  }
}


void helper(char * curr, char ** lines, FILE * src, size_t sz){
  size_t i = 0;
  while((getline(&curr, &sz, src) != -1)){
    lines = realloc(lines, (1+i)*sizeof(*lines)); 
    lines[i] = curr;
    curr = NULL;
    i++;
  }  
  free(curr);
  sortData(lines, i); // Maybe i + 1?
  printResults(lines, i);
  free(lines);
}


int main(int argc, char ** argv) {
  char ** lines = NULL;
  char * curr = NULL;
  size_t sz = 0;
  
  //WRITE YOUR CODE HERE!
  if(argc == 1){
    helper(curr, lines, stdin, sz);
  } else if(argc > 1){
    for(size_t i=1; i<argc; i++){
      FILE * f = fopen(argv[i], "r");
      if(f == NULL){
        perror("Failed to open file\n");
        exit(EXIT_FAILURE);
      }
      helper(curr, lines, f, sz);

      if(fclose(f) != 0){
        perror("Failed to close file\n");
        return EXIT_FAILURE;
      }

    }
  }else{
    fprintf(stderr, "Error. Ni argc == 1 ni argc>1\n");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
