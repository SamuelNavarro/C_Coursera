#include <stdlib.h>


unsigned power_helper(unsigned x, unsigned y,  int ans){
  if(y==0){
    return ans;
  }

  return power_helper(x, y-1, ans * x );
}


unsigned power(unsigned x, unsigned y){
  if( x == 0 && y == 0){
   return 1;
  }
  return power_helper(x, y, 1);
}
