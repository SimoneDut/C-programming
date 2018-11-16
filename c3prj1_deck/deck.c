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
