#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

void countLetters(FILE * f, int * freq) {
  int c;
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      c = tolower(c);
      c -= 'a';
      assert((c>=0)&&(c<26));
      freq[c]++;
    }
  }
}

int findMaxLetter(int * freq, int n) {
  int maxIndex = 0;
  int maxValue = 0;
  int totalLetters = 0;
  for (int i = 0; i < n; i++) {
    if (freq[i] > maxValue) {
      maxIndex = i;
      maxValue = freq[i];
    }
    totalLetters += freq[i];
  }
  if (totalLetters == 0) {
    return -1;
  }
  return maxIndex;
}


int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr,"Usage breaker inputFilename\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1],"r");
  if (f == NULL) {
    fprintf(stderr,"Could not open file\n");
    return EXIT_FAILURE;
  }
  int nLetters = 26;
  int frequency[nLetters];
  for (int i = 0; i < nLetters; i++) {
    frequency[i] = 0;
  }
  countLetters(f,frequency);
  if (fclose(f) != 0) {
    fprintf(stderr,"Failed to close the input file\n");
  }
  int index = findMaxLetter(frequency,nLetters);
  if (index < 0) {
    fprintf(stderr,"File empty or without letters");
  }
  int key = (index + 'a' - 'e');
  if (key < 0) {
    key += nLetters;
  }
  fprintf(stdout,"%d\n",key);
  return EXIT_SUCCESS;
}
