
#include "cards.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  card_t c;
  hand_ranking_t r;
  unsigned i = 0;
  c.value = 6;
  c.suit = SPADES;
  assert_card_valid(c);
  printf("6 of SPADES is valid\n");
  c.value = VALUE_KING;
  c.suit = HEARTS;
  assert_card_valid(c);
  printf("KING of HEARTS is valid\n");
  for (r = STRAIGHT_FLUSH; r <= NOTHING; r++) {
    printf("%s\n",ranking_to_string(r));
  }
  c.suit = SPADES;
  for (c.suit = SPADES; c.suit <= CLUBS; c.suit++) {
    for (c.value = 2; c.value <= VALUE_ACE; c.value++) {
      print_card(c);
      printf(" ");
      print_card(card_from_num(i));
      i++;
      printf("\n");
    }
  }
  return EXIT_SUCCESS;
}
