#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"
#include "input.h"


int * initArray(int sz){
  int * array = malloc( (sz + 1) * sizeof(*array));
  for(size_t i=0; i<=sz; i++){
    array[i] = 0; 
  }
  return array;
}

void free_fc(future_cards_t * fc){
  for(size_t i=0; i<fc->n_decks; i++){
    //for(size_t j=0; j<fc->decks[i].n_cards; j++){
    //  free(fc->decks[i].cards[j]);
    //}
    free(fc->decks[i].cards);
  }  
  free(fc->decks);
  free(fc);
}

int winning_hand(deck_t ** deck, size_t * n_hands){
  int idx = 0;
  int draw_idx = -1;
  //print_hand(deck[idx]);
  //printf("\n");
  for(size_t i=1; i<*n_hands; i++){
    //print_hand(deck[idx]);
    //printf("\n");
    if(compare_hands(deck[i], deck[idx]) > 0 ){
      idx=i;  
    }else if(compare_hands(deck[i], deck[idx]) == 0 ){
      idx=i;
      draw_idx=i;
    }
  }

  if(draw_idx == idx){
    return *n_hands;
  }

  return idx;
}


int main(int argc, char ** argv) {
  //YOUR CODE GOES HERE

  if(argc < 2 || argc > 3){
    fprintf(stderr, "Usage: ./poker input.txt number_trials\n");
    exit(EXIT_FAILURE);
  }
  
  FILE * f = fopen(argv[1], "r");
  if(f == NULL){
    perror("Could not open file in test-input\n");
    return EXIT_FAILURE;
  }
  
  future_cards_t * fc = malloc(sizeof(*fc));
  fc->n_decks = 0;
  fc->decks = NULL;
  size_t * n_hands = malloc(sizeof(size_t));
  deck_t ** hands = read_input(f, n_hands, fc);
  deck_t * deck = build_remaining_deck(hands, *n_hands);

  int * count_array =  initArray(*n_hands); 


  unsigned int times = 10000;
  if(argc==3){ 
    if(atol(argv[2]) > 0){
      times = atol(argv[2]);
    }else{
      printf("The number of times should be greater than zero\n"); 
      exit(EXIT_FAILURE);
    }
  }

  for(size_t i=0; i<times; i++){
    shuffle(deck);  
    future_cards_from_deck(deck, fc);
    int wc = winning_hand(hands, n_hands);
    if(wc==*n_hands){
      count_array[*n_hands] += 1;
    }else{
      count_array[wc] += 1;
    }
  }
  

  for(size_t i=0; i<*n_hands; i++){
    //double div = (double)count_array[i] / times;
    printf("Hand %zu won %u / %u times (%.2f%%)\n", 
           i, count_array[i], times,
           100.0*count_array[i]/(double)times);
  }
  printf("And there were %u ties\n", count_array[*n_hands]);
  
  for(size_t i=0; i<*n_hands; i++){
    free_deck(hands[i]);
  }
  free_deck(deck);
  free(hands);
  free(n_hands);
  free_fc(fc);
  free(count_array);

  if(fclose(f) != 0){
    perror("Could not close file\n");
    exit(EXIT_FAILURE);
  }

  return EXIT_SUCCESS;
}
