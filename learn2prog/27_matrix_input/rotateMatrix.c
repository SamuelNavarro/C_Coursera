#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>


#define DIM_SZ 10


void rotate(char matrix[10][10]){
  char out[10][10];
  for(size_t i=0; i<10; i++){
    for(size_t j=0; j<10; j++){
      out[i][j] = matrix[9 - j][i];
    }
  }

  for(size_t i=0; i<10; i++){
    for(size_t j=0; j<10; j++){
      matrix[i][j] = out[i][j];
    }
  }
}



int main(int argc, char ** argv){
  if(argc == 1){
   fprintf(stderr, "Usage: program file\n"); 
  }
  if(argc != 2){
    fprintf(stderr, "Usage: program file\n");
    return EXIT_FAILURE;
  }
  
  FILE * f = fopen(argv[1], "r");
  if(f == NULL){
    perror("Could not open file\n");
    exit( EXIT_FAILURE );
  }

  char line[DIM_SZ+2];
  char mtx[DIM_SZ][DIM_SZ];
  int idx=0;

  while(fgets(line, DIM_SZ+2, f) != NULL){
    if(strchr(line, '\n')-line+1 != DIM_SZ + 1){
      perror("Line is too short \n");
      exit( EXIT_FAILURE );
    }

    if(strchr(line, '\n') == NULL){
      perror("Line is too long \n");
      exit( EXIT_FAILURE );
    } 

    for(size_t j=0; j<DIM_SZ; j++){
      mtx[idx][j] = line[j];
    }

    if(idx>9){
      fprintf(stderr, "Too many lines\n");
      exit(EXIT_FAILURE);
    }
    idx++;
  } 

  rotate(mtx);

  if(idx<10){
    fprintf(stderr, "File is too short\n");
    exit(EXIT_FAILURE);
  }



  for(size_t i=0; i<10; i++){
    for(size_t j=0; j<10; j++){
      printf("%c", mtx[i][j]);
    }
    printf("\n");
  }

  if(fclose(f)!=0){
    perror("Couldn't close file\n");
    exit(EXIT_FAILURE);
  }


  return EXIT_SUCCESS;

}
