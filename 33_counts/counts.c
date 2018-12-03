#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"

/*

struct _kvpair_t {
  char * key;
  char * value;
};
typedef struct _kvpair_t kvpair_t;

struct _kvarray_t {
  kvpair_t * pair;
  size_t lenght;
};
typedef struct _kvarray_t kvarray_t;

struct _one_count_t {
  char * value;
  size_t repetitions;
};
typedef struct _one_count_t one_count_t;

struct _counts_t {
  one_count_t * oneCount;
  size_t lenght;
  size_t numUnk
};
typedef struct _counts_t counts_t;

*/

counts_t * createCounts(void) {
  /*  The first, createCounts should allocate memory for a counts_t structure, and initialize
  it to represent that nothing has been counted yet.						 
//WRITE ME
*/
  counts_t * ans = malloc(sizeof(*ans));
  ans->oneCount = NULL;
  ans->lenght = 0;
  ans->numUnk = 0;
  return ans;
}
void addCount(counts_t * c, const char * name) {
  /*
  The next function, addCount, should increment the count for the corresponding name.  Note
that name will be NULL in the case of something that is unknown, so your code must account
for this case.
//WRITE ME
*/
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
  /*
  The third function, printCounts takes a counts_t and prints that information to
    the FILE outFile. Recall from the description of the entire problem, that this
    function should print in the format:
    
    Captain: 1
    Commander: 2
    Lt. Commander: 1
    <unknown> : 1

    These should appear in the order that the name is first added, with unknown always
appearing last.
    ***If there are no unknown values, you should not print a line for unknown.  That
										   is, you should NEVEr print
										   <unknown> : 0
//WRITE ME
*/
  for (size_t i = 0; i < c->lenght; i++) {
    fprintf(outFile,"%s: %zu\n",c->oneCount[i].value,c->oneCount[i].repetitions);
  }
  if (c->numUnk > 0) { fprintf(outFile,"<unknown> : %zu\n",c->numUnk); }
}

void freeCounts(counts_t * c) {
  /*
  Finally, you should write freeCounts, which should free all the memory associated with
a counts_t.
  */    
//WRITE ME
  for (size_t i = 0; i < c->lenght; i++) {
    free(c->oneCount[i].value);
  }
  free(c->oneCount);
  free(c);
}
