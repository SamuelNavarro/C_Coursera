#include <stdio.h>
#include <stdlib.h>


int main(void) {
  int anArray[] = {5,16,33,99};
  int * p = anArray;
  printf("*p = %d\n", *p); // *p is 5
  p++;
  printf("Now *p = %d\n", *p); // *p is 16
  int * q = &anArray[3]; // *q is 99;
  int ** x = &q;
  **x = 12; // cambia 99 por 12
  *x = p;  
  **x = 42;  // pero p estaba aputando en 16. tons 16 se cambia por 42
  q[1] = 9;  // Undefined??
  for (int i =0; i < 4; i++){
    printf("anArray[%d] = %d\n",i, anArray[i]);
  } // {5, 42, 33, 12
  return EXIT_SUCCESS;
}
