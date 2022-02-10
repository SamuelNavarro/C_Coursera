#include <stdio.h>
#include <stdlib.h>

int f(int ** r, int ** s) {
  int temp = ** r; // temp = 80
  int temp2 = **s; // temp2 = 12
  int * z = *r; // z apunta a donde apunta p
  *r = *s; // r apuanta  q
  *s = z;  // q apunta a p
  printf("**r = %d\n",**r); //**r = 12
  printf("**s = %d\n",**s); //**s = 80
  *z += 3; // a = 83
  **s -= 8; // a = 72
  **r -= 19; // b = -7
  return temp + temp2;
}

int main(void) {
  int a = 80;
  int b = 12;
  int * p = &a;
  int * q = &b;
  int x = f(&p, &q);
  printf("x = %d\n", x); // 92
  printf("*p = %d\n", *p); // 72
  printf("*q = %d\n", *q); // -7
  printf("a = %d\n", a);
  printf("b = %d\n", b);
  return EXIT_SUCCESS;
}
