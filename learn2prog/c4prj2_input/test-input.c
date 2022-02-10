#include <stdlib.h>
#include <stdio.h>
#include "future.h"
#include "cards.h"
#include "input.h"
#include "deck.h"




int main(int argc, char ** argv){
  
  if(argc!=2){
    fprintf(stderr, "Usage: program file\n");  
    exit(EXIT_FAILURE);	
  } 


  FILE * f = fopen(argv[1], "r");
  if(f==NULL){
    perror("Could not open file in test-input\n");
    return EXIT_FAILURE;
  }
  
  future_cards_t * fc = malloc(sizeof(*fc)); 
  fc->n_decks = 0;
  //fc->decks = calloc(fc->n_decks+1, (fc->n_decks + 1) * sizeof(*fc->decks));
  fc->decks = NULL;

  size_t * n_hands = malloc(sizeof(size_t));
  deck_t ** hands = read_input(f, n_hands, fc);

  printf("The hands of the file:\n");
  for(size_t i=0; i<*n_hands; i++){
    print_hand(hands[i]);
    printf("\n");
  }
  
  printf("Remaining hands %zu\n", *n_hands);
  deck_t * d = build_remaining_deck(hands, *n_hands);
  printf("Remaining deck:\n");
  print_hand(d);
  printf("\n");
  shuffle(d);

  future_cards_from_deck(d, fc);
  printf("Filled in cards:\n");
  for(size_t i=0; i<*n_hands; i++){
    print_hand(hands[i]);
    printf("\n");
  }

  free_deck(d);


  for(size_t i=0; i<*n_hands; i++){
    free_deck(hands[i]);
  }
  free(hands);
  free(n_hands);


  //for(size_t i=0; fc->n_decks; i++){
  //  for(size_t j=0; fc->decks[i].n_cards; j++){
  //    free(fc->decks[i].cards[j]);
  //  }
  //  free(fc->decks[i].cards);
  //  free_deck(&fc->decks[i]);
  //}

  //for(size_t i=0;fc->n_decks;i++){
  //  free(&fc->decks[i]);
  //}


  //for(size_t i=0;fc->n_decks;i++){
    //free(fc->decks[i].cards);
  //}
  free(fc);






  if(fclose(f)!=0){
    perror("Could not close the file\n");
    exit(EXIT_FAILURE);
  }

  return EXIT_SUCCESS;
}
