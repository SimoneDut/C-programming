#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"
#include "input.h"

long int check_value(const char * string) {

  char * endptr = NULL;
  long int ans = strtol(string,&endptr,10);
  if (endptr == string) { return -1; }
  if (*endptr != '\0') { return -1; }
  return ans;

}

long int * run_a_simulation(const char * fileName, long int nTrials, size_t * size) {

  /*Open the input file and read the hands in it
    (you just wrote read_input!) */

  FILE * f = fopen(fileName,"r");
  if (f == NULL) {
    perror("Could not open the input file!");
    exit(EXIT_FAILURE);
  }

  size_t nHands;
  future_cards_t * fc = malloc(sizeof(*fc));
  fc->decks = NULL;
  fc->n_decks = 0;
  deck_t ** inputHands = read_input(f,&nHands,fc);
  *size = nHands;

  /*Create a deck with the remaining cards
    (you just wrote build_remaining_deck) */

  deck_t * remainingDeck = build_remaining_deck(inputHands,nHands);
  
  /*Create an array to count how many times each hand
    wins, with one more element for if there was a tie
    (so if there are 2 hands, you should have 3 elements).
    and initialize all its values to 0. */

  long int * wins = malloc((nHands+1)*sizeof(*wins));
  for (size_t i = 0; i < nHands+1; i++) {
    wins[i] = 0;
  }
  
  /*Do each Monte Carlo trial (repeat num_trials times)
    Shuffle the deck of remaining cards
    (you wrote shuffle in Course 3) */

  for (long int trial = 0; trial < nTrials; trial++) {

    shuffle(remainingDeck);

  /*Assign unknown cards from the shuffled deck
    (you just wrote future_cards_from_deck) */

    future_cards_from_deck(remainingDeck,fc);

  /*Use compare_hands (from Course 3) to
    figure out which hand won. Note that
    with potentially more than 2 hands,
    this is much like finding the max of
    an array, but using compare_hands
    instead of >.*/

    size_t bestHand = 0;
    int tie = 0;
    int currentResult;

    for (size_t j = 1; j < nHands; j++) {
      currentResult = compare_hands(inputHands[j],inputHands[bestHand]);
      if (currentResult > 0) {
	bestHand = j;
	tie = 0;
      }
      else if (currentResult == 0) {
	tie = 1;
      }	
    }
  
  /*Increment the win count for the winning
   hand (or for the "ties" element of the array
   if there was a tie).*/

    if (tie) { (wins[nHands])++; }
    else { (wins[bestHand])++; }	

  }
  
  /*After you do all your trials, you just need
   to print your results, free any memory
   you allocated, and close any open files.*/

  // FREE

  // future_cards_t * fc = malloc(sizeof(*fc));
  for (size_t count1 = 0; count1 < fc->n_decks; count1++) {
    free(fc->decks[count1].cards);
  }
  free(fc->decks);
  free(fc);

  // deck_t ** inputHands = read_input(f,&nHands,fc);
  for (size_t count2 = 0; count2 < nHands; count2++) {    
    free_deck(inputHands[count2]);
  }
  free(inputHands);

  // deck_t * remainingDeck = build_remaining_deck(inputHands,nHands);
  free_deck(remainingDeck);

  // CLOSE

  if (fclose(f) != 0) {
    perror("Could not close the input file!");
    exit(EXIT_FAILURE);
  }

  /*You should use the following format strings to report your results.
   For each hand, you should printf
   "Hand %zu won %u / %u times (%.2f%%)\n"
   where the %zu is the hand number (0,1,..)  [zu is for size_t]
   the first %u is the number of wins for that hand
   the second %u is the total number of trials
   the %.2f is the percentage that this win/trials ratio gives
   Then you should printf one more line for the ties:
   "And there were %u ties\n"
   Where the %u is just a count of how many ties there were*/

  return wins;
  
}

int main(int argc, char ** argv) {

  /*Check command line arguments/report errors*/

  if ((argc<2)||(argc>3)) {
    fprintf(stderr,"Usage: poker inputFileName (numberOfTrials)\n");
    return EXIT_FAILURE;
  }
  long int nTrials;
  if (argc == 3) {
    nTrials = check_value(argv[2]);
    if (nTrials <= 0) {
      fprintf(stderr,"numberOfTrials must be a positive integer!\n");
      return EXIT_FAILURE;
    }
  }
  else {
    nTrials = 10000;
  }

  int debug = 0;
  if (!strcmp(argv[1],"-debug")) { debug = 1; }

  if (!debug) {
    size_t size;
    long int * wins = run_a_simulation(argv[1],nTrials,&size);
    // PRINT
    for (size_t k = 0; k < size; k++) {
      printf("Hand %zu won %u / %u times (%.2f%%)\n",
	     k,(unsigned int)wins[k],(unsigned int)nTrials,100*(wins[k]/(float)nTrials));
    }
    printf("And there were %u ties\n",(unsigned int)wins[size]);
    // FREE
    free(wins);
  }
  else {
    const char * dirPath = "./provided-tests/";
    const char * prefix = "test";
    const char * suffix = ".txt";
    char number[] = "00";
    char * fileName = malloc((strlen(dirPath)+strlen(prefix)+2+strlen(suffix)+1)*sizeof(*fileName));

    FILE * outFile = fopen("./provided-tests/my_answers.txt","w");
    if (outFile == NULL) {
      perror("Could not open the output file!");
      exit(EXIT_FAILURE);
    }

    for (char n = 1; n <= 16; n++) {
      char n1 = n/10 + '0';
      char n2 = n - (n/10)*10 + '0';
      number[0] = n1;
      number[1] = n2;
      strcat(strcat(strcat(strcpy(fileName,dirPath),prefix),number),suffix);
      size_t size;
      long int * wins = run_a_simulation(fileName,nTrials,&size);
      // PRINT
      fprintf(outFile,"%s%s%s: ",prefix,number,suffix);
      for (size_t k = 0; k < size-1; k++) {
	fprintf(outFile,"Hand %zu = %0.f%%,",k,100*(wins[k]/(float)nTrials));
	if (100*(wins[k]/(float)nTrials)<99.5) { fprintf(outFile," "); }
	if (100*(wins[k]/(float)nTrials)<9.5) { fprintf(outFile," "); }
	if ((k % 3) == 0) { fprintf(outFile," "); }
	if ((k % 3) == 2) { fprintf(outFile,"\n            "); }
      }
      fprintf(outFile,"Hand %zu = %0.f%%\t",size-1,100*(wins[size-1]/(float)nTrials));
      fprintf(outFile,"\n");
      // FREE
      free(wins);
    }
    free(fileName);
    if (fclose(outFile) != 0) {
      perror("Could not close the output file!");
      exit(EXIT_FAILURE);
    }
  }

/*  test01.txt: Hand 0 = 95%,  Hand 1 = 5%
    test02.txt: Hand 0 = 14%,  Hand 1 = 86%
    test03.txt: Hand 0 = 69%,  Hand 1 = 31%
    test04.txt: Hand 0 = 63%,  Hand 1 = 36%
    test05.txt: Hand 0 = 27%,  Hand 1 = 73%
    test06.txt: Hand 0 = 20%,  Hand 1 = 80%
    test07.txt: Hand 0 = 100%, Hand 1 = 0%
    test08.txt: Hand 0 = 1%,   Hand 1 = 1%
    test09.txt: Hand 0 = 0%,   Hand 1 = 4%
    test10.txt: Hand 0 = 0%,   Hand 1 = 18%
    test11.txt: Hand 0 = 41%,  Hand 1 = 58%
    test12.txt: Hand 0 = 84%,  Hand 1 = 16%
    test13.txt: Hand 0 = 77%,  Hand 1 = 23%
    test14.txt: Hand 0 = 0%,   Hand 1 = 0%,  Hand 2 = 31%
    test15.txt: Hand 0 = 2%,   Hand 1 = 13%, Hand 2 = 84%
    test16.txt: Hand 0 = 4%,   Hand 1 = 5%,  Hand 2 = 12%,
    Hand 3 = 8%,   Hand 4 = 58%, Hand 5 = 12%
*/

  return EXIT_SUCCESS;

}
