#include <stdlib.h>
#include <stdio.h> 

size_t maxSeq(int * array, size_t n);

int main(void){

  int array[] = {4, 5, -4, -3, -2, -1, 1}; // unsigned vs signed
  if(maxSeq(array, 7) != 5){ 
  printf("Failed on {4, 5, -4, -3, -2, -1, 1}");
    exit(EXIT_FAILURE); 
  }

  //int array1[] = {1, 2, 3, -4, -3, -2, -1, 3, 5};
  //if(maxSeq(array1, 9) != 6){ 
  //printf("Failed on {1, 2, 3, -4, -3, -2, -1, 3, 5}");
  //  exit(EXIT_FAILURE); 
  //}


  int array2[] = {0, 1, -1, 0, 1, 0, 1, 2, 3};
  if(maxSeq(array2, 9) != 4){ 
  printf("Failed on {0, 1, -1, 0, 1, 0, 1, 2, 3}");
    exit(EXIT_FAILURE); 
  }

  int array3[] = {};
  if(maxSeq(array3, 0) != 0){ 
  printf("Failed on {}");
    exit(EXIT_FAILURE); 
  }

  int array4[] = {1};
  if(maxSeq(array4, 1) != 1){ 
  printf("Failed on {1}");
    exit(EXIT_FAILURE); 
  }

  //int array5[] = {-3, -42, -99, -100, 2, 3, 5};
  //if(maxSeq(array5, 7) != 4){ 
  //printf("Failed on {-3, -42, -99, -100, 2, 3, 5}");
  //  exit(EXIT_FAILURE); 
  //}

  // Todos crecientes pero negativos
  //int array6[] = {-8, -7, -6, -5, -4, -3};
  //if(maxSeq(array6, 6) != 6){ 
  //printf("Failed on {-8, -7, -6, -5, -4, -3}");
  //  exit(EXIT_FAILURE); 
  //}

  //// Todos crecientes pero positivosj
  //int array7[] = {0, 1, 2, 3, 4, 5};
  //if(maxSeq(array7, 6) != 6){ 
  //printf("Failed on {1, 2, 3, -1, 0, 1}");
  //  exit(EXIT_FAILURE); 
  //}

  // empatados
  int array8[] = {1, 2, 3, -1, 0, 1};
  if(maxSeq(array8, 6) != 3){ 
  printf("Failed on {1, 2, 3, -1, 0, 1}");
    exit(EXIT_FAILURE); 
  }

  // El que gana en medio 
  int array9[] = {1, 2, 3, -1, 0, 1, 2, -10};
  if(maxSeq(array9, 8) != 4){ 
  printf("Failed on {1, 2, 3, -1, 0, 1}");
    exit(EXIT_FAILURE); 
  }


  // Iguales
  int array10[] = {0, 0, 0};
  if(maxSeq(array10, 3) != 1){ 
  printf("Failed on {0, 0, 0}");
    exit(EXIT_FAILURE); 
  }


  return EXIT_SUCCESS;
}
