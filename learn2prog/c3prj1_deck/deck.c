#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"
#include "cards.h"


void print_hand(deck_t * hand){
  size_t n_cards = hand->n_cards; 
  for(int i = 0; i < n_cards; i++){
    print_card( *(hand->cards[i]) );
    printf(" ");
  }
}


int deck_contains(deck_t * d, card_t c) {
  size_t n_cards = d->n_cards; 
  for(int i = 0; i<n_cards; i++){
    if( (d->cards[i]->value == c.value) && (d->cards[i]->suit == c.suit) ){
      return 1;
    }
  } 
  return 0;
}


void shuffle(deck_t * d){
  size_t n_cards = d->n_cards;
  for (int i = 0; i<n_cards; i++){
    size_t j = i + rand() / (RAND_MAX / (n_cards - i) + 1);
    card_t* t = d->cards[j];
    d->cards[j] = d->cards[i];
    d->cards[i] = t;
  } 
}


void assert_full_deck(deck_t * d) {
  size_t n_cards = d->n_cards;

  for(size_t i = 0; i<n_cards; i++ ){
    card_t c = card_from_num(i);
    assert_card_valid(c);
    if(deck_contains(d, c) == 0){
      printf("No existe la tarjeta ");
      print_card(c);
      exit(EXIT_FAILURE); 
    }

  }
}



void add_card_to(deck_t * deck, card_t c){
  deck->cards = realloc(deck->cards, (deck->n_cards + 1) * sizeof(*deck->cards));
  assert(deck->cards!=NULL);
  deck->n_cards++;

  deck->cards[deck->n_cards -1] = malloc(sizeof(**deck->cards));
  // - 1 because the array is 0 indexed but 
  // ncards start at 1
  //*(deck->cards[deck->n_cards - 1]) = c;
  deck->cards[deck->n_cards-1]->value=c.value;
  deck->cards[deck->n_cards-1]->suit=c.suit;

}


card_t * add_empty_card(deck_t * deck){
  card_t c;
  c.value = 0;
  c.suit = NUM_SUITS;
  add_card_to(deck, c);

  return deck->cards[deck->n_cards - 1];
}


deck_t * make_deck_exclude(deck_t * excluded_cards){
  deck_t * d = malloc(sizeof(*d));
  if(d==NULL){
    fprintf(stderr, "Could not create deck in make_deck_exclude\n");
    free(d);
  }
  d->cards=NULL;
  d->n_cards=0;
  for(size_t i=0; i<52; i++){
    card_t c = card_from_num(i);
    if(!deck_contains(excluded_cards, c)){
      add_card_to(d, c);
    }
  }

  return d;
}


deck_t * build_remaining_deck(deck_t ** hands, size_t n_hands){
  deck_t * d = malloc(sizeof(*d));
  d->cards = NULL;
  d->n_cards=0;

  for(size_t i=0; i<n_hands; i++){
    for(size_t j=0; j<hands[i]->n_cards; j++){
      card_t * c = hands[i]->cards[j];
      add_card_to(d, *c);
    }
  }
  deck_t * ans = make_deck_exclude(d);
  free_deck(d);

  return ans;

}



void free_deck(deck_t * deck){
  for(size_t i=0; i<deck->n_cards; i++){
    free(deck->cards[i]);
  }
  free(deck->cards);
  free(deck);
}

