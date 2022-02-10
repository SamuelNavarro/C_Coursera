#include "cards.h"
#include <stdio.h>

int main(void) {

//  for(unsigned i=0; i<52; i++){
//   card_t c = card_from_num(i);
//   print_card(c);
//}

  card_t c = card_from_letters('4', 's');
  print_card(c);
  printf("\n");
  return 0;
}
