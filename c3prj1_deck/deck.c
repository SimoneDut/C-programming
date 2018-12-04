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

void add_card_to(deck_t * deck, card_t c) {
  (deck->n_cards)++;
  deck->cards = realloc(deck->cards,(deck->n_cards)*sizeof(*(deck->cards)));
  deck->cards[deck->n_cards-1] = malloc(sizeof(*(deck->cards[deck->n_cards-1])));
  *(deck->cards[deck->n_cards-1]) = c;
}
  
card_t * add_empty_card(deck_t * deck) {
  (deck->n_cards)++;
  deck->cards = realloc(deck->cards,(deck->n_cards)*sizeof(*(deck->cards)));
  deck->cards[deck->n_cards-1] = malloc(sizeof(*(deck->cards[deck->n_cards-1])));
  deck->cards[deck->n_cards-1]->value = 0;
  deck->cards[deck->n_cards-1]->suit = 0;
  return deck->cards[deck->n_cards-1];
}
  
deck_t * make_deck_exclude(deck_t * excluded_cards) {
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
  for (size_t i = 0; i < deck->n_cards; i++) {
    free(deck->cards[i]);
  }
  free(deck->cards);
  free(deck);
}
