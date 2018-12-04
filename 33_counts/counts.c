#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"

counts_t * createCounts(void) {
  counts_t * ans = malloc(sizeof(*ans));
  if (ans == NULL) {
    fprintf(stderr,"Couldn't allocate memory\n");
    exit(EXIT_FAILURE);
  }
  ans->oneCount = NULL;
  ans->lenght = 0;
  ans->numUnk = 0;
  return ans;
}

void addCount(counts_t * c, const char * name) {
  if (name == NULL) { (c->numUnk)++; }
  else {
    int found = 0;
    for (size_t i = 0; i < c->lenght; i++) {
      if (strcmp(c->oneCount[i].value,name) == 0) {
	(c->oneCount[i].repetitions)++;
	found = 1;
	break;
      }
    }
    if (found == 0) {
      (c->lenght)++;
      c->oneCount = realloc(c->oneCount, (c->lenght)*sizeof(*(c->oneCount)));
      c->oneCount[(c->lenght)-1].value = malloc((strlen(name)+1)*sizeof(*(c->oneCount[(c->lenght)-1].value)));
      strncpy(c->oneCount[(c->lenght)-1].value, name, (strlen(name)+1));
      c->oneCount[(c->lenght)-1].repetitions = 1;  
    }	
  }	
}

void printCounts(counts_t * c, FILE * outFile) {
  for (size_t i = 0; i < c->lenght; i++) {
    fprintf(outFile,"%s: %zu\n",c->oneCount[i].value,c->oneCount[i].repetitions);
  }
  if (c->numUnk > 0) { fprintf(outFile,"<unknown> : %zu\n",c->numUnk); }
}

void freeCounts(counts_t * c) {
  for (size_t i = 0; i < c->lenght; i++) {
    free(c->oneCount[i].value);
  }
  free(c->oneCount);
  free(c);
}
