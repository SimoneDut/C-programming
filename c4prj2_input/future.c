#include "future.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void add_future_card(future_cards_t * fc, size_t index, card_t * ptr) {
  if ((index+1) > fc->n_decks) {
    fc->decks = realloc(fc->decks,(index+1)*sizeof(*(fc->decks)));
    for (size_t i = fc->n_decks; i < (index+1); i++) {
      fc->decks[i].cards = NULL;
      fc->decks[i].n_cards = 0;
    }
    fc->n_decks = index+1;
  }
  (fc->decks[index].n_cards)++;
  fc->decks[index].cards = realloc(fc->decks[index].cards,
				   (fc->decks[index].n_cards)*sizeof(*(fc->decks[index].cards)));
  fc->decks[index].cards[fc->decks[index].n_cards-1] = ptr;
}

void future_cards_from_deck(deck_t * deck, future_cards_t * fc) {
  if (fc->n_decks > deck->n_cards) {
    fprintf(stderr,"The number of cards in the deck is unsufficient!\n");
    exit(EXIT_FAILURE);
  }
  for (size_t i = 0; i < fc->n_decks; i++) {
    if ((fc->decks[i].cards == NULL) || (fc->decks[i].n_cards == 0)) {
      fprintf(stderr,"Missing unknown card ?%zu",i);
      exit(EXIT_FAILURE);
    }
    for (size_t j = 0; j < fc->decks[i].n_cards; j++) {
      fc->decks[i].cards[j]->value = deck->cards[i]->value;
      fc->decks[i].cards[j]->suit = deck->cards[i]->suit;
    }
  }
}
