#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"

void print_hand(deck_t * hand) {
  for (size_t i = 0; i < (hand -> n_cards); i++) {
    print_card(*((hand -> cards)[i]));
    printf(" ");
  }
}

int deck_contains(deck_t * d, card_t c) {
  for (size_t i = 0; i < (d -> n_cards); i++) {
    if (((*((d -> cards)[i])).suit == c.suit)&&((*((d -> cards)[i])).value == c.value)) {
      return 1;
    }
  }
  return 0;
}

void shuffle(deck_t * d) {
  if ((d -> n_cards) > 1) {
    size_t i = random() % (d -> n_cards);
    card_t * temp = (d -> cards)[i];
    (d -> cards)[i] = (d -> cards)[(d -> n_cards)-1];
    (d -> cards)[(d -> n_cards)-1] = temp;
    (d -> n_cards)--;
    shuffle(d);
    (d -> n_cards)++;
  }
}

void assert_full_deck(deck_t * d) {
  assert((d -> n_cards)==52);
  for (unsigned c = 0; c < 52; c++) {
    assert(deck_contains(d ,card_from_num(c)));
  }
}

/*
struct deck_tag {
  card_t ** cards;
  size_t n_cards;
};
typedef struct deck_tag deck_t;
*/


void add_card_to(deck_t * deck, card_t c) {
/*
Add the particular card to the given deck (which will
					   involve reallocing the array of cards in that deck).
*/
  (deck->n_cards)++;
  deck->cards = realloc(deck->cards,(deck->n_cards)*sizeof(*(deck->cards)));
  deck->cards[deck->n_cards-1] = malloc(sizeof(*(deck->cards[deck->n_cards-1])));
  *(deck->cards[deck->n_cards-1]) = c;
}
  
card_t * add_empty_card(deck_t * deck) {
/*
Add a card whose value and suit are both 0, and return a pointer  
   to it in the deck.  
   This will add an invalid card to use as a placeholder  
   for an unknown card.
*/
  (deck->n_cards)++;
  deck->cards = realloc(deck->cards,(deck->n_cards)*sizeof(*(deck->cards)));
  deck->cards[deck->n_cards-1] = malloc(sizeof(*(deck->cards[deck->n_cards-1])));
  deck->cards[deck->n_cards-1]->value = 0;
  deck->cards[deck->n_cards-1]->suit = 0;
  return deck->cards[deck->n_cards-1];
}
  
deck_t * make_deck_exclude(deck_t * excluded_cards) {
  /*
   Create a deck that is full EXCEPT for all the cards
   that appear in excluded_cards.  For example,
     if excluded_cards has Kh and Qs, you would create
   a deck with 50 cards---all of them except Kh and Qs.
   You will need to use malloc to allocate this deck.
     (You will want this for the next function).
   Don't forget you wrote card_t card_from_num(unsigned c)
   in Course 2 and int deck_contains(deck_t * d, card_t c)
   in Course 3!  They might be useful here.
*/
  deck_t * ans = malloc(sizeof(*ans));
  ans->cards = NULL;
  ans->n_cards = 0;
  for (unsigned i = 0; i < 52; i++) {
    card_t c = card_from_num(i);
    if (!deck_contains(excluded_cards,c)) {
      add_card_to(ans,c);
    }
  }
  return ans;
}

deck_t * build_remaining_deck(deck_t ** hands, size_t n_hands) {
/*
   This function takes an array of hands (remember
   that we use deck_t to represent a hand).  It then builds
   the deck of cards that remain after those cards have
   been removed from a full deck.  For example, if we have
   two hands:
      Kh Qs ?0 ?1 ?2 ?3 ?4
      As Ac ?0 ?1 ?2 ?3 ?4
   then this function should build a deck with 48
   cards (all but As Ac Kh Qs).  You can just build
   one deck with all the cards from all the hands
   (remember you just wrote add_card_to),
   and then pass it to make_deck_exclude.
*/

  deck_t * allFromHands = malloc(sizeof(*allFromHands));
  allFromHands->cards = NULL;
  allFromHands->n_cards = 0;

  for (size_t i = 0; i < n_hands; i++) {
    for (size_t j = 0; j < hands[i]->n_cards; j++) {
      card_t c = *(hands[i]->cards[j]);
      add_card_to(allFromHands,c);
    }
  }

  deck_t * ans = make_deck_exclude(allFromHands);

  free(allFromHands);

  return ans;

}

void free_deck(deck_t * deck) {
/*
   Free the memory allocated to a deck of cards.
   For example, if you do
     deck_t * d = make_excluded_deck(something);
     free_deck(d);
   it should free all the memory allocated by make_excluded_deck.
   Once you have written it, add calls to free_deck anywhere you
   need to to avoid memory leaks.
*/

  /*
struct deck_tag {
  card_t ** cards;
  size_t n_cards;
};
typedef struct deck_tag deck_t;
*/
  for (size_t i = 0; i < deck->n_cards; i++) {
    free(deck->cards[i]);
  }
  free(deck->cards);
  free(deck);
}
