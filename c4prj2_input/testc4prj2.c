#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"
#include "input.h"

int main() {
  deck_t * null_deck = malloc(sizeof(*null_deck));
  null_deck->cards = NULL;
  null_deck->n_cards = 0;
  deck_t * full_deck = make_deck_exclude(null_deck);
  print_hand(full_deck);
  printf("\n");
  
  future_cards_t * fc1 = malloc(sizeof(*fc1));
  fc1->decks = NULL;
  fc1->n_decks = 0;
  deck_t * some_deck1 = hand_from_string("4h 5h 6h 7h 8h", fc1);
  print_hand(some_deck1);
  printf("\n");

  deck_t * some_deck2 = hand_from_string("4h ?2 ?2 ?1 ?4", fc1);
  some_deck2->n_cards = 1;
  print_hand(some_deck2);
  some_deck2->n_cards = 5;
  printf("\n");
  printf("%zu\n",fc1->n_decks);
  printf("%zu\n",fc1->decks[0].n_cards);
  printf("%zu\n",fc1->decks[1].n_cards);
  printf("%zu\n",fc1->decks[2].n_cards);
  printf("%zu\n",fc1->decks[3].n_cards);
  printf("%zu\n",fc1->decks[4].n_cards);

  
  FILE * f = fopen("test.txt","r");
  if (f == NULL) { exit(EXIT_FAILURE); }
  future_cards_t * fc2 = malloc(sizeof(*fc2));
  fc2->decks = NULL;
  fc2->n_decks = 0;
  size_t n_hands;
  deck_t ** input_decks = read_input(f, &n_hands, fc2);

  if (fclose(f)!=0) { exit(EXIT_FAILURE); }
  
  printf("Input deck(s): %zu\n",n_hands);
  for (size_t i = 0; i < n_hands; i++) {
    printf("Hand number %zu has %zu card(s):\n",i+1,input_decks[i]->n_cards);
    for (size_t j = 0; j < input_decks[i]->n_cards; j++) {
      printf("Card %zu has value %d and suit %d\n",j+1,input_decks[i]->cards[j]->value,input_decks[i]->cards[j]->suit);
    }
    free_deck(input_decks[i]);
  }
  free(input_decks);
  printf("fc2 has %zu deck(s):\n",fc2->n_decks);
  for (size_t i = 0; i < fc2->n_decks; i++) {
    printf("Deck number %zu (cards ?%zu) has %zu card(s):\n",i+1,i,fc2->decks[i].n_cards);
  }

  free_deck(null_deck);
  free_deck(full_deck);
  free_deck(some_deck1);
  free_deck(some_deck2);
  for (size_t i = 0; i < fc1->n_decks; i++) {
    free(fc1->decks[i].cards);
  }
  free(fc1->decks);
  free(fc1);
  for (size_t i = 0; i < fc2->n_decks; i++) {
    free(fc2->decks[i].cards);
  }
  free(fc2->decks);
  free(fc2);
  
  return EXIT_SUCCESS;
};
