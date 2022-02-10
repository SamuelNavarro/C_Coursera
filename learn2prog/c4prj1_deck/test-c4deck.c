#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"
#include "cards.h"


deck_t * create_full_deck(int num_cards){
  deck_t * d = malloc(sizeof(*d));
  for(size_t i=0; i<num_cards; i++){
    card_t c = card_from_num(i);
    add_card_to(d, c); 
  }
  return d;
}

int main(void){
   
  //deck_t * d = create_full_deck(5);
  //print_hand(d);


  card_t c1 = card_from_letters('4', 'd');
  card_t c2 = card_from_letters('5', 's');
  deck_t * excluded = malloc(sizeof(*excluded));
  excluded->n_cards = 2;
  excluded->cards = malloc(excluded->n_cards * sizeof(*excluded->cards));
  //excluded->cards = NULL;
  for(size_t i=0; i<excluded->n_cards; i++){
    excluded->cards[i] = calloc(1, sizeof(**excluded->cards));
    //excluded->cards[i] = malloc(sizeof(**excluded->cards));
  }

  add_card_to(excluded, c1);
  add_card_to(excluded, c2);
  
  deck_t * d = make_deck_exclude(excluded);
  
  free_deck(excluded);
  print_hand(d);
  free_deck(d);


  //deck_t * d1 = create_full_deck(3);
  //deck_t * d2 = create_full_deck(3);
  //deck_t * d3 = create_full_deck(3);
  //deck_t * d4 = create_full_deck(3);

  
  
 


  return EXIT_SUCCESS;
}


