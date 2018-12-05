#include "future.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*
struct deck_tag {  
  card_t ** cards;  
  size_t n_cards;  
};
typedef struct deck_tag deck_t;

struct card_tag {  
  unsigned value;  
  suit_t suit;
};
typedef struct card_tag card_t;

struct future_cards_tag {
  deck_t * decks;
  size_t n_decks;  
};
typedef struct future_cards_tag future_cards_t;
*/

void add_future_card(future_cards_t * fc, size_t index, card_t * ptr) {
/*This adds ptr into the future cards for the given index (that is,
which ?n it is). So if this is a future card for ?3, then index
   will be 3.  ptr will point at an existing placeholder card
  (it will point into a hand at a card which was added
   with add_empty_card).
   Note that it is entirely possible to have an input like
     Kh Qh As 4c 2c ?3 ?4
     Ac Qc As 4c 2c ?3 ?4
(which might happen if e.g., someone edited a file that
originally have ?0, ?1, and ?2 but replaced them when
they became known). Or you might see ?3 before ?2.
   Your add_future_card should handle such
   cases by reallocing its array to be large enough to handle
the specified index, and just having empty decks for  
   the indicies that have not had add_future_card called
   on them yet.
*/
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
/*This function takes a deck (which has been shuffled),
  and a future_cards_t (which has been filled in with
all the pointers to placeholders) and draws cards from
   the deck and assigns their values and suits to the
   placeholders pointed to in fc.
   For example if the deck is
     As Kh 8c ....
   and fc was created from the input
     3c 4c ?0 ?1 ?2
     5h 9d ?0 ?1 ?2
  then this function will draw As for ?0,
  and fill in the two placeholders for ?0 (which
  you can find with the pointers in fc, as described
  in the video).  Then it will draw Kh for ?1,
   and so on. Think about a case where this function would need to
   print an error message.
*/
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
      fc->decks[i].cards[j]->suid = deck->cards[i]->suit;
    }
  }
}
