#include <stdio.h>
#include <stdlib.h>
//I've provided "min" and "max" functions in
//case they are useful to you
int min (int a, int b) {
  if (a < b) {
    return a;
  }
  return b;
}

int max (int a, int b) {
  if (a > b) {
    return a;
  }
  return b;
}

//Declare your rectangle structure here!
typedef struct template{
  int x, y, width, height;
} rectangle;


rectangle canonicalize(rectangle r) {
  //WRITE THIS FUNCTION
  if( r.width < 0 && r.height < 0){
    r.y = r.y + r.height;
    r.height = r.height * -1;
    
    r.x = r.x + r.width;
    r.width = r.width * -1;
  }
  else if(r.width < 0){
    r.x = r.x + r.width;
    r.width = r.width * -1;
  }
  else if(r.height < 0){
    r.y = r.y + r.height;
    r.height = r.height * -1;
  }
  return r;
}



rectangle intersection(rectangle r1, rectangle r2) {
  //WRITE THIS FUNCTION
  rectangle r;
  int dxr1, dyr1;
  int dxr2, dyr2;
  r1 = canonicalize(r1);
  r2 = canonicalize(r2);

  dxr1 = r1.x + r1.width;
  dyr1 = r1.y + r1.height;

  dxr2 = r2.x + r2.width;
  dyr2 = r2.y + r2.height;
 
  int dxr, dyr;
  dxr = min(dxr1, dxr2);
  dyr = min(dyr1, dyr2);

  r.x = max(r1.x, r2.x);
  r.y = max(r1.y, r2.y);
  
  int cond1 = r1.x > dxr2;
  int cond2 = dxr1 < r2.x;
  int cond3 = r1.y > dyr2;
  int cond4 = dyr1 < r2.y; 
  if ( cond1 || cond2 || cond3 || cond4){
    r.width = 0;
    r.height = 0;
} else
{
  r.width = dxr - r.x;
  r.height = dyr - r.y;
}


  return r;    
}

//You should not need to modify any code below this line
void printRectangle(rectangle r) {
  r = canonicalize(r);
  if (r.width == 0 && r.height == 0) {
    printf("<empty>\n");
  }
  else {
    printf("(%d,%d) to (%d,%d)\n", r.x, r.y, 
	                           r.x + r.width, r.y + r.height);
  }
}

int main (void) {
  rectangle r1;
  rectangle r2;
  rectangle r3;
  rectangle r4;

  r1.x = 2;
  r1.y = 3;
  r1.width = 5;
  r1.height = 6;
  printf("r1 is ");
  printRectangle(r1);

  r2.x = 4;
  r2.y = 5;
  r2.width = -5;
  r2.height = -7;
  printf("r2 is ");
  printRectangle(r2);
  
  r3.x = -2;
  r3.y = 7;
  r3.width = 7;
  r3.height = -10;
  printf("r3 is ");
  printRectangle(r3);

  r4.x = 0;
  r4.y = 7;
  r4.width = -4;
  r4.height = 2;
  printf("r4 is ");
  printRectangle(r4);

  //test everything with r1
  rectangle i = intersection(r1,r1);
  printf("intersection(r1,r1): ");
  printRectangle(i);

  i = intersection(r1,r2);
  printf("intersection(r1,r2): ");
  printRectangle(i);
  
  i = intersection(r1,r3);
  printf("intersection(r1,r3): ");
  printRectangle(i);

  i = intersection(r1,r4);
  printf("intersection(r1,r4): ");
  printRectangle(i);

  //test everything with r2
  i = intersection(r2,r1);
  printf("intersection(r2,r1): ");
  printRectangle(i);

  i = intersection(r2,r2);
  printf("intersection(r2,r2): ");
  printRectangle(i);
  
  i = intersection(r2,r3);
  printf("intersection(r2,r3): ");
  printRectangle(i);

  i = intersection(r2,r4);
  printf("intersection(r2,r4): ");
  printRectangle(i);

  //test everything with r3
  i = intersection(r3,r1);
  printf("intersection(r3,r1): ");
  printRectangle(i);

  i = intersection(r3,r2);
  printf("intersection(r3,r2): ");
  printRectangle(i);
  
  i = intersection(r3,r3);
  printf("intersection(r3,r3): ");
  printRectangle(i);

  i = intersection(r3,r4);
  printf("intersection(r3,r4): ");
  printRectangle(i);

  //test everything with r4
  i = intersection(r4,r1);
  printf("intersection(r4,r1): ");
  printRectangle(i);

  i = intersection(r4,r2);
  printf("intersection(r4,r2): ");
  printRectangle(i);
  
  i = intersection(r4,r3);
  printf("intersection(r4,r3): ");
  printRectangle(i);

  i = intersection(r4,r4);
  printf("intersection(r4,r4): ");
  printRectangle(i);


  return EXIT_SUCCESS;

}
