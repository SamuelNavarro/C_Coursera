#include "eval.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


int card_ptr_comp(const void * vp1, const void * vp2) {
  const card_t * const * cp1 = vp1;
  const card_t * const * cp2 = vp2;
  int val = (*cp2)->value - (*cp1)->value;
  if(val == 0){
    char s1 = suit_letter(**cp1);
    char s2 = suit_letter(**cp2);
    return strcmp(&s1, &s2);
  }
  return val;
}


suit_t flush_suit(deck_t * hand) {
  size_t n_cards = hand->n_cards;
  int flush_val = 5;
  int s=0;
  int h=0;
  int c=0;
  int d=0;
  for(size_t i=0; i<n_cards; i++){
    card_t card = *(hand->cards[i]);
    switch(suit_letter(card)){
      case 's': s++; break;
      case 'c': c++; break;
      case 'h': h++; break;
      case 'd': d++; break;
      default: 
        printf("Error en swithc suit_letter\n");
        exit(EXIT_FAILURE); 
        break;
    }
  }
  if( s>=flush_val ){
    return SPADES;
  } else if (c>=flush_val){
    return CLUBS;
  } else if (h>=flush_val){
    return HEARTS;
  } else if (d>=flush_val){
    return DIAMONDS;
  } else {
  return NUM_SUITS;
  }
}


unsigned get_largest_element(unsigned * arr, size_t n) {
  int max_idx=0;
  for(size_t i=1; i<n; i++){
    if(arr[i] > arr[max_idx]){
      max_idx=i;
    }
  }
  return arr[max_idx];
}


size_t get_match_index(unsigned * match_counts, size_t n,unsigned n_of_akind){
  int idx=-1;
  
  for(size_t i=0; i<n; i++){
    if(match_counts[i] == n_of_akind){
      if(idx == -1){ 
        idx = i;
      }
    }
  }
  if(idx == -1){
    printf("n_of_akind is not in match_counts");
    exit(EXIT_FAILURE);
  }
  return idx;
}

ssize_t  find_secondary_pair(deck_t * hand,
			     unsigned * match_counts,
			     size_t match_idx) {
  size_t n_cards = hand->n_cards;
  int idx=-1;
  for(size_t i=0; i<n_cards; i++){
    if(match_counts[i] > 1 && hand->cards[i]->value != hand->cards[match_idx]->value && idx == -1){
      idx = i;
    }
  }
  return idx;
}


int is_n_length_straight_at(deck_t* hand, size_t index, suit_t fs, int n){
  int n_cards = hand->n_cards;
  int counter = 0;
  int counter_a = 0;
  // los siguientes son los que busco
  int curr_value = hand->cards[index]->value;
  int curr_a_value = 5;

  for(size_t i=index; i<n_cards; i++){
    if(fs != NUM_SUITS && hand->cards[index]->suit == fs){
      if( hand->cards[i]->value == curr_a_value && hand->cards[i]->suit == fs && n == 4){
        curr_a_value--;
        counter_a++;
        if(counter_a == n){
          return -1;
        }
      } else if ( hand->cards[i]->value == curr_value && hand->cards[i]->suit == fs){
        curr_value --;
        counter++;
        if(counter == n){
          return 1;
        }
      }
    } else if(fs == NUM_SUITS ){
      if( hand->cards[i]->value == curr_a_value && n == 4 ){
        curr_a_value--;
        counter_a++;
        if(counter_a == n){
          return -1;
        }
      } else if ( hand->cards[i]->value == curr_value  ){
        curr_value --;
        counter++;
        if(counter == n){
          return 1;
        }
      }
    }
  }

  return 0;
}


int is_ace_low_straight_at(deck_t* hand, size_t index, suit_t fs){
  if(hand->cards[index]->value == VALUE_ACE && is_n_length_straight_at(hand, index, fs, 4)==-1){
    return 1;
  }
  return 0;
}



int is_straight_at(deck_t * hand, size_t index, suit_t fs) {
  if(is_ace_low_straight_at(hand, index, fs)){
    return -1;
  } else if (is_n_length_straight_at(hand, index, fs, 5)){
    return 1; 
  } 
  return 0;
}


// hand_eval_t has:
// hand_ranking_t ranking 
// 5 cards that form the ranking
hand_eval_t build_hand_from_match(deck_t * hand,
				  unsigned n,
				  hand_ranking_t what,
				  size_t idx) {
  hand_eval_t ans;
  ans.ranking = what;
  int i_cards = 0;

  for(size_t i=0; i<n; i++){
    ans.cards[i] = hand->cards[idx + i];
    i_cards++;
  }

  for(size_t i=0; i<5; i++){
    if( i_cards < 5){
      if( i < idx ){
        ans.cards[n + i] = hand->cards[i];
        i_cards++;
      }else if( i >= idx + n){
        ans.cards[i] = hand->cards[i];
        i_cards++;
      }
    } 
  }

  return ans;
}



int compare_hands(deck_t * hand1, deck_t * hand2) {
  int n_cards1 = 5;
  int n_cards2 = 5;
  assert(n_cards1 == n_cards2);
  qsort(hand1->cards, hand1->n_cards, sizeof(const card_t *), card_ptr_comp);
  qsort(hand2->cards, hand2->n_cards, sizeof(const card_t *), card_ptr_comp);
  hand_eval_t h1 = evaluate_hand(hand1);
  hand_eval_t h2 = evaluate_hand(hand2);

  if(h1.ranking != h2.ranking){
    return h2.ranking - h1.ranking; 
  }else{
    for(size_t i=0; i<n_cards1; i++){
      if(h1.cards[i]->value != h2.cards[i]->value){
        return h1.cards[i]->value - h2.cards[i]->value;
      }
    }
  }
  return 0;

}


//You will write this function in Course 4.
//For now, we leave a prototype (and provide our
//implementation in eval-c4.o) so that the
//other functions we have provided can make
//use of get_match_counts.
unsigned * get_match_counts(deck_t * hand){

  // sizeof(ans)
  unsigned int * arr = malloc(hand->n_cards * (sizeof(*arr)));
  for(size_t i=0; i<hand->n_cards;i++){
    arr[i]=0;
  }

  for(size_t i=0; i<hand->n_cards;i++){
    for(size_t j=0; j<hand->n_cards; j++){
      if(hand->cards[i]->value == hand->cards[j]->value){
        arr[j]++;
      }
    }
  }
  return arr;

} 

// We provide the below functions.  You do NOT need to modify them
// In fact, you should not modify them!


//This function copies a straight starting at index "ind" from deck "from".
//This copies "count" cards (typically 5).
//into the card array "to"
//if "fs" is NUM_SUITS, then suits are ignored.
//if "fs" is any other value, a straight flush (of that suit) is copied.
void copy_straight(card_t ** to, deck_t *from, size_t ind, suit_t fs, size_t count) {
  assert(fs == NUM_SUITS || from->cards[ind]->suit == fs);
  unsigned nextv = from->cards[ind]->value;
  size_t to_ind = 0;
  while (count > 0) {
    assert(ind < from->n_cards);
    assert(nextv >= 2);
    assert(to_ind <5);
    if (from->cards[ind]->value == nextv &&
	(fs == NUM_SUITS || from->cards[ind]->suit == fs)){
      to[to_ind] = from->cards[ind];
      to_ind++;
      count--;
      nextv--;
    }
    ind++;
  }
}


//This looks for a straight (or straight flush if "fs" is not NUM_SUITS)
// in "hand".  It calls the student's is_straight_at for each possible
// index to do the work of detecting the straight.
// If one is found, copy_straight is used to copy the cards into
// "ans".
int find_straight(deck_t * hand, suit_t fs, hand_eval_t * ans) {
  if (hand->n_cards < 5){
    return 0;
  }
  for(size_t i = 0; i <= hand->n_cards -5; i++) {
    int x = is_straight_at(hand, i, fs);
    if (x != 0){
      if (x < 0) { //ace low straight
	assert(hand->cards[i]->value == VALUE_ACE &&
	       (fs == NUM_SUITS || hand->cards[i]->suit == fs));
	ans->cards[4] = hand->cards[i];
	size_t cpind = i+1;
	while(hand->cards[cpind]->value != 5 ||
	      !(fs==NUM_SUITS || hand->cards[cpind]->suit ==fs)){
	  cpind++;
	  assert(cpind < hand->n_cards);
	}
	copy_straight(ans->cards, hand, cpind, fs,4) ;
      }
      else {
	copy_straight(ans->cards, hand, i, fs,5);
      }
      return 1;
    }
  }
  return 0;
}


//This function puts all the hand evaluation logic together.
//This function is longer than we generally like to make functions,
//and is thus not so great for readability :(
hand_eval_t evaluate_hand(deck_t * hand) {
  suit_t fs = flush_suit(hand);
  hand_eval_t ans;
  if (fs != NUM_SUITS) {
    if(find_straight(hand, fs, &ans)) {
      ans.ranking = STRAIGHT_FLUSH;
      return ans;
    }
  }
  unsigned * match_counts = get_match_counts(hand);
  unsigned n_of_a_kind = get_largest_element(match_counts, hand->n_cards);
  assert(n_of_a_kind <= 4);
  size_t match_idx = get_match_index(match_counts, hand->n_cards, n_of_a_kind);
  ssize_t other_pair_idx = find_secondary_pair(hand, match_counts, match_idx);
  free(match_counts);
  if (n_of_a_kind == 4) { //4 of a kind
    return build_hand_from_match(hand, 4, FOUR_OF_A_KIND, match_idx);
  }
  else if (n_of_a_kind == 3 && other_pair_idx >= 0) {     //full house
    ans = build_hand_from_match(hand, 3, FULL_HOUSE, match_idx);
    ans.cards[3] = hand->cards[other_pair_idx];
    ans.cards[4] = hand->cards[other_pair_idx+1];
    return ans;
  }
  else if(fs != NUM_SUITS) { //flush
    ans.ranking = FLUSH;
    size_t copy_idx = 0;
    for(size_t i = 0; i < hand->n_cards;i++) {
      if (hand->cards[i]->suit == fs){
	ans.cards[copy_idx] = hand->cards[i];
	copy_idx++;
	if (copy_idx >=5){
	  break;
	}
      }
    }
    return ans;
  }
  else if(find_straight(hand,NUM_SUITS, &ans)) {     //straight
    ans.ranking = STRAIGHT;
    return ans;
  }
  else if (n_of_a_kind == 3) { //3 of a kind
    return build_hand_from_match(hand, 3, THREE_OF_A_KIND, match_idx);
  }
  else if (other_pair_idx >=0) {     //two pair
    assert(n_of_a_kind ==2);
    ans = build_hand_from_match(hand, 2, TWO_PAIR, match_idx);
    ans.cards[2] = hand->cards[other_pair_idx];
    ans.cards[3] = hand->cards[other_pair_idx + 1];
    if (match_idx > 0) {
      ans.cards[4] = hand->cards[0];
    }
    else if (other_pair_idx > 2) {  //if match_idx is 0, first pair is in 01
      //if other_pair_idx > 2, then, e.g. A A K Q Q
      ans.cards[4] = hand->cards[2];
    }
    else {       //e.g., A A K K Q
      ans.cards[4] = hand->cards[4];
    }
    return ans;
  }
  else if (n_of_a_kind == 2) {
    return build_hand_from_match(hand, 2, PAIR, match_idx);
  }
  return build_hand_from_match(hand, 0, NOTHING, 0);
}
