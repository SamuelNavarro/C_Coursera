#include <stdio.h>
#include <stdlib.h>


unsigned power(unsigned x, unsigned y);

void run_check(unsigned x, unsigned y, unsigned expected){

  unsigned res = power(x, y);
  if ( res != expected ){
    printf("Sin Match! Valores: %u Esperado: %u. \n", res, expected);
    exit(EXIT_FAILURE);
  }
  printf("Match!! Res: %u Esperado: %u. \n", res, expected);
};



int main(void){
  run_check(2, 2, 4);
  run_check(0, 0, 1);
  run_check(0, 1, 0);
  run_check(1, 0, 1);
  short a = 3;
  run_check(a, 10, 59049);
  run_check(10, a, 1000);
  run_check(3, 3, 27); 
  run_check(5, 10, 9765625);
  run_check(4, 2, 16);
}
