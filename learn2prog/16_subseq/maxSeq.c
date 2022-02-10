#include <stdlib.h>
#include <stdio.h>


int compararContadores(int a, int b){
  if (a >= b){
    return a;
  }
  return b;
}


size_t maxSeq(int * array, size_t n){

  // array[] = {1, 2, 3, -1, 0, 1, 4, 1, 2, 3}
  // array[] = {4, 5, -4, -3, -2, -1, 1}
  // {-4, -3, -2, -1, 1, 4, 5}

  // Hay como el contador bueno.

  if(n == 0){
    return 0; 
  }
  if(n ==1){
    return 1;
  }


  int currCounter = 1;
  int prevCounter = 0;
  int counter = 0;
  
  for(size_t i = 1; i < n; i++){
    if(array[i] > array[i-1]){
      currCounter++;
    } else {
      prevCounter = currCounter;
      currCounter = 1;
    }
    counter = compararContadores(currCounter, counter);
    counter = compararContadores(counter, prevCounter);
  }
  // c 5
  // pC = 5
  // cC = 1
  // c 5

  return counter; 
}
