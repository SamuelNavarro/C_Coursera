#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "future.h"


deck_t * hand_from_string(const char * str, future_cards_t * fc){

  deck_t * hand = malloc(sizeof(*hand));
  hand->n_cards = 0;
  hand->cards = malloc(sizeof(*hand->cards));
  char curr[40];
  strcpy(curr, str);
  char * tkn = strtok(curr, " ");
  
  while(tkn != NULL && tkn[0] != 10){

   if(tkn[0] == '?'){
     card_t * ptr = add_empty_card(hand);

     if(tkn[2] && tkn[2] != '\n'){
       int index = tkn[2] - 48; 
       add_future_card(fc, index + 10, ptr);
       tkn = strtok(NULL, " ");
     }else{
       int index = tkn[1] - 48;
       add_future_card(fc, index, ptr);
       tkn = strtok(NULL, " ");
     }
   }else {
     card_t c = card_from_letters(tkn[0], tkn[1]); 
     add_card_to(hand, c);
     tkn = strtok(NULL, " ");
   }

  }
  if(hand->n_cards<5){
    fprintf(stderr, "Not enough cards in hand_from_string\n");
    exit(EXIT_FAILURE);
  }

  return hand;

}



deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t * fc){
  
  deck_t ** ans = NULL;
  char * line=NULL;
  size_t i=0;
  size_t sz;
  while(getline(&line, &sz, f)>=0){
    *n_hands = i+1;
    deck_t * hand = hand_from_string(line, fc);
    ans = realloc(ans, (i+1) * sizeof(*ans));
    ans[i] = hand;
    i++;
  }
  free(line);

  return ans;

}

