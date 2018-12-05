#include "input.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

deck_t * hand_from_string(const char * str, future_cards_t * fc) {
  deck_t * ans = malloc(sizeof(*ans));
  ans->cards = NULL;
  ans->n_cards = 0;
  size_t i = 0;
  size_t index = 0;
  size_t move = 0;
  while ((str[i]!='\n')&&(str[i]!='\0')) {
    if (str[i]!=' ') {
      if (str[i]=='?') {
	if ((str[i+1]>='0')&&(str[i+1]<='9')) {
	  if ((str[i+2]>='0')&&(str[i+2]<='9')) {
	    if ((str[i+3]==' ')||(str[i+3]=='\n')||(str[i+3]=='\0')) {
	      index = (str[i+1]-'0')*10+(str[i+2]-'0');
	      move = 3;
	    }
	    else {
	      fprintf(stderr,"Format error: %c%c%c%c\n",str[i],str[i+1],str[i+2],str[i+3]);
	      exit(EXIT_FAILURE);
	    }
	  }
	  else if ((str[i+2]==' ')||(str[i+2]=='\n')||(str[i+2]=='\0')) {
	    index = str[i+1]-'0';
	    move = 2;
	  }
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
	  move = 2;
	}
	else {
	  fprintf(stderr,"Format error: %c%c%c\n",str[i],str[i+1],str[i+2]);
	  exit(EXIT_FAILURE);
	}
      }
    }
    if (move < 2) { move = 1; }
    i += move;
    move = 0;
  }
  if (ans->n_cards < 5) {
    fprintf(stderr,"This line has only %zu cards\n",ans->n_cards);
    exit(EXIT_FAILURE);
  }
  return ans;
}

deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t * fc) {
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
