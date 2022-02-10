#include <stdlib.h>


void rotate(char matrix[10][10]){

  char out[10][10];

  for(size_t i = 0; i < 10; i++){
    for(size_t j = 0; j < 10; j++){
    out[i][j] = matrix[9 - j][i]; 
    }
  }

  for(size_t i = 0; i < 10; i++){
    for(size_t j = 0; j < 10; j++){
      matrix[i][j] = out[i][j];
    }
  }
  

}
