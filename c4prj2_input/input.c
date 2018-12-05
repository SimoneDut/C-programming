#include "input.h"
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

deck_t * hand_from_string(const char * str, future_cards_t * fc) {
  /*
   I abstracted out the code to take one single line   
   and parse it into a hand:
   deck_t * hand_from_string(const char * str, future_cards_t * fc)
   and recommend you do the same.
  */
  /*
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
  */

  /*
     (?0, ?1, ...), you should use add_empty_card to
     create a placeholder in the hand, and then add_future_card
   to make sure you will update it correctly when you draw
   later.  Also remember that you wrote add_card_to
     earlier in this course, as well as card_from_letters
   in Course 2.  These will both be handy here!
 Note that most of the rest of the code assumes that a poker hand
 has AT LEAST 5 cards in it.  Your read_input function should enforce
     this requirement. If there are fewer than 5 cards, print
 a useful error message and exit.
  */

  deck_t * ans = malloc(sizeof(*ans));
  ans->cards = NULL;
  ans->n_cards = 0;

  size_t i = 0;
  size_t index = 0;
  
  while ((str[i]!='\n')&&(str[i]!='\0')) {
    if (str[i]!=' ') {
      if (str[i]=='?') {
	if ((str[i+1]>='0')&&(str[i+1]<='9')) {
	  if ((str[i+2]>='0')&&(str[i+2]<='9')) {
	    if ((str[i+3]==' ')||(str[i+3]=='\n')||(str[i+3]=='\0')) { index = (str[i+1]-'0')*10+(str[i+2]-'0'); }
	    else {
	      fprintf(stderr,"Format error: %c%c%c%c\n",str[i],str[i+1],str[i+2],str[i+3]);
	      exit(EXIT_FAILURE);
	    }
	  }
	  else if ((str[i+2]==' ')||(str[i+2]=='\n')||(str[i+2]=='\0')) { index = str[i+1]-'0'; }
	  else {
	    fprintf(stderr,"Format error: %c%c%c\n",str[i],str[i+1],str[i+2]);
	    exit(EXIT_FAILURE);
	  }
	}
	else {
	  fprintf(stderr,"Format error: %c%c\n",str[i],str[i+1]);
	  exit(EXIT_FAILURE);
	}
	add_future_card(fc,index,add_empty_card(ans));
      }
      else {
	if ((str[i+1]==' ')||(str[i+1]=='\n')||(str[i+1]=='\0')) {
	  fprintf(stderr,"Format error: %c%c\n",str[i],str[i+1]);
	  exit(EXIT_FAILURE);
	}
	else if ((str[i+2]==' ')||(str[i+2]=='\n')||(str[i+2]=='\0')) {
	  add_card_to(ans,card_from_letters(str[i],str[i+1]));
	}
	else {
	  fprintf(stderr,"Format error: %c%c%c\n",str[i],str[i+1],str[i+2]);
	  exit(EXIT_FAILURE);
	}
      }
    }
  }
  if (ans->n_cards < 5) {
    fprintf(stderr,"This line has only %zu cards\n",ans->n_cards);
    exit(EXIT_FAILURE);
  }

  return ans;

}

deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t * fc) {
  
  /*   This function reads the input from f.  Recall that the input
   file has one hand per line (and that we represent a hand
 with a deck_t).  You should allocate a deck_t for each hand
and place it into an array of pointers to deck_ts, which is your
   answer.
   This function needs to tell its caller how many hands it read.
     We could return a struct, but we are going to do this a
different way: it will fill in *n_hands with the number
of hands.  This is a bit different, but you have seen it
before: this is how getline "returns" the string it
   read and the size of the space allocated to that string.
As you read the input, if you encounter future cards
     (?0, ?1, ...), you should use add_empty_card to
     create a placeholder in the hand, and then add_future_card
   to make sure you will update it correctly when you draw
   later.  Also remember that you wrote add_card_to
     earlier in this course, as well as card_from_letters
   in Course 2.  These will both be handy here!
 Note that most of the rest of the code assumes that a poker hand
 has AT LEAST 5 cards in it.  Your read_input function should enforce
     this requirement. If there are fewer than 5 cards, print
 a useful error message and exit.
  */

  deck_t ** ans = NULL;
  *n_hands = 0;

  size_t sz = 0;
  ssize_t len = 0;
  char * line = NULL;
  while ((len = getline(&line,&sz,f))>=0) {
    if (len > 1) {
      (*n_hands)++;
      ans = realloc(ans,(*n_hands)*sizeof(*ans));
      ans[(*n_hands)-1] = hand_from_string(line,fc);
    }
    free(line);
    sz = 0;
  }
  free(line);
  return ans;

}
