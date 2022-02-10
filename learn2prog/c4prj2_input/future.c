#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"
#include "future.h"


void add_future_card(future_cards_t * fc, size_t index, card_t * ptr){
  if(fc==NULL){
    fc = realloc(fc, sizeof(*fc));
    assert(fc!=NULL);
    fc->decks=NULL;
    fc->n_decks=0;
  }

  if(index>=fc->n_decks){
    fc->n_decks = index + 1;
    // index en lugar de fc->n_decks 
    // porque si tenemos ?12
    // fc->decks = realloc(fc->decks, (fc->n_decks) * sizeof(*fc->decks));
    fc->decks = realloc(fc->decks, (index + 1) * sizeof(*fc->decks));

    // TODO
    for(size_t i=fc->n_decks - 1; i<index+1; i++){
      fc->decks[i].cards = NULL; 
      fc->decks[i].n_cards=0;
    }

    //fc->decks[index].cards = NULL;
    //fc->decks[index].n_cards = 1;


    fc->decks[index].n_cards++;
    fc->decks[index].cards = realloc(fc->decks[index].cards,
                                     fc->decks[index].n_cards * sizeof(*fc->decks[index].cards));
    fc->decks[index].cards[fc->decks[index].n_cards - 1] = ptr;

  }else{
    // fc->n_decks se queda igual
    // don't need to realloc fc->decks
    // ;(hahahha por supuesto que tengo que realloc
    fc->decks[index].n_cards++;
    fc->decks[index].cards = realloc(fc->decks[index].cards,
                                     (fc->decks[index].n_cards) * sizeof(*fc->decks[index].cards));
    
    fc->decks[index].cards[fc->decks[index].n_cards - 1] = ptr;
  }

}



void future_cards_from_deck(deck_t * deck, future_cards_t * fc){
  if(deck==NULL || fc == NULL){
    fprintf(stderr, "Deck or fc in future_cards_from_Deck is not allocated\n");
    exit(EXIT_FAILURE);
  }
  
  if(deck->n_cards<fc->n_decks){
    fprintf(stderr, "Invalid number of cards in future_cards_from_deck\n"); 
    exit(EXIT_FAILURE);
  }  
  


    for(size_t j=0; j<fc->n_decks; j++){
      if(fc->decks[j].n_cards>0){
        for(size_t k=0; k<fc->decks[j].n_cards; k++){
          fc->decks[j].cards[k]->value = deck->cards[j]->value;
          fc->decks[j].cards[k]->suit = deck->cards[j]->suit;
        }
      }
    } 


}



