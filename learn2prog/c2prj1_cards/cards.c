#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "cards.h"


void assert_card_valid(card_t c) {
  assert(c.value >= 2);
  assert(c.value <= 14);
  assert(c.suit >= 0);
  assert(c.suit <= 3);
}


const char * ranking_to_string(hand_ranking_t r) {
  switch(r){
    case STRAIGHT_FLUSH: return("STRAIGHT_FLUSH"); break;
    case FOUR_OF_A_KIND: return("FOUR_OF_A_KIND"); break;
    case FULL_HOUSE: return("FULL_HOUSE"); break;
    case FLUSH: return("FLUSH"); break;
    case STRAIGHT: return("STRAIGHT"); break;
    case THREE_OF_A_KIND: return("THREE_OF_A_KIND"); break;
    case TWO_PAIR: return("TWO_PAIR"); break;
    case PAIR: return("PAIR"); break;
    default: return("NOTHING"); break;
  }
}


char value_letter(card_t c) {
  switch(c.value){
    case 2: return '2'; break; 
    case 3: return '3'; break; 
    case 4: return '4'; break; 
    case 5: return '5'; break; 
    case 6: return '6'; break; 
    case 7: return '7'; break; 
    case 8: return '8'; break; 
    case 9: return '9'; break; 
    case 10: return '0'; break; 
    case VALUE_JACK: return 'J'; break; 
    case VALUE_QUEEN: return 'Q'; break; 
    case VALUE_KING: return 'K'; break; 
    case VALUE_ACE: return 'A'; break; 
    default: return '?';
  }
}


char suit_letter(card_t c) {
  switch(c.suit){
    case SPADES: return 's'; break;
    case HEARTS: return 'h'; break;
    case DIAMONDS: return 'd'; break;
    case CLUBS: return 'c'; break;
    //case 's': return SPADES; break;
    //case 'h': return HEARTS; break;
    //case 'd': return DIAMONDS; break;
    //case 'c': return CLUBS; break;
    default: return '?'; 
  }
}

void print_card(card_t c) {
  card_t out;
  out.value = value_letter(c);
  out.suit = suit_letter(c);
  printf("%c%c",  out.value, out.suit);
}


card_t card_from_letters(char value_let, char suit_let) {
  card_t c;

  switch(value_let){
    case '2': c.value = 2; break; 
    case '3': c.value = 3; break; 
    case '4': c.value = 4; break; 
    case '5': c.value = 5; break; 
    case '6': c.value = 6; break; 
    case '7': c.value = 7; break; 
    case '8': c.value = 8; break; 
    case '9': c.value = 9; break; 
    case '0': c.value = 10; break; 
    case 'J': c.value = VALUE_JACK; break; 
    case 'Q': c.value = VALUE_QUEEN; break; 
    case 'K': c.value = VALUE_KING; break; 
    case 'A': c.value = VALUE_ACE; break; 
    default: c.value = '?';
   }

  switch(suit_let){
    case 's': c.suit = SPADES; break;
    case 'h': c.suit = HEARTS; break;
    case 'd': c.suit = DIAMONDS; break;
    case 'c': c.suit = CLUBS; break;
    default: c.suit =  '?';
  }

  assert_card_valid(c);
  return c;
}


card_t card_from_num(unsigned c) {
  card_t temp;
  assert(c >= 0 && c < 52);
  if(c / 13 < 1){
    temp.suit = 0;
  } else if (c / 13 >= 1 && c / 13 < 2){
    temp.suit = 1;
  } else if (c / 13 >= 2 && c / 13 < 3){
    temp.suit = 2;
  } else { 
    temp.suit = 3;
  }
  temp.value = c % 13 + 2;
;
    
  return temp;
}
