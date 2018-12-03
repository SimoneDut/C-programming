#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"

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

*/

void splitLineN(kvarray_t * KVArray, char * line, ssize_t len, ssize_t posEq) {
  (KVArray->lenght)++;
  size_t currSize = KVArray->lenght;
  KVArray->pair = realloc(KVArray->pair,currSize*sizeof(*(KVArray->pair)));
  if (KVArray->pair == NULL) {
    fprintf(stderr,"Couldn't allocate memory\n");
    exit(EXIT_FAILURE);
  }
  (KVArray->pair[currSize-1]).key = malloc((posEq+1)*sizeof(*((KVArray->pair[currSize-1]).key)));
  if ((KVArray->pair[currSize-1]).key == NULL) {
    fprintf(stderr,"Couldn't allocate memory\n");
    exit(EXIT_FAILURE);
  }
  (KVArray->pair[currSize-1]).value = malloc((len-posEq-1)*sizeof(*((KVArray->pair[currSize-1]).value)));
  if ((KVArray->pair[currSize-1]).value == NULL) {
    fprintf(stderr,"Couldn't allocate memory\n");
    exit(EXIT_FAILURE);
  }
  strncpy((KVArray->pair[currSize-1]).key, line, posEq);
  ((KVArray->pair[currSize-1]).key)[posEq]='\0';
  strncpy((KVArray->pair[currSize-1]).value, &line[posEq+1], len-posEq-2);
  ((KVArray->pair[currSize-1]).value)[len-posEq-2]='\0';
}

ssize_t findEqual(char * line, ssize_t len) {
  for (ssize_t i = 0; i < len; i++) {
    if (line[i] == '=') { return i; }
  }
  return -1;
}

kvarray_t * readSplitLines(FILE * f) {
  kvarray_t * ans = malloc(sizeof(*ans));
  if (ans == NULL) {
    fprintf(stderr,"Couldn't allocate memory\n");
    exit(EXIT_FAILURE);
  }	 
  ans->pair = NULL;
  ans->lenght = 0;
  size_t sz = 0;
  ssize_t len = 0;
  char * line = NULL;
  ssize_t posEq = 0;
  size_t count = 0;
  while ((len = getline(&line,&sz,f))>=0) {
    if (len > 1) {
      count++;
      if ((posEq = findEqual(line,len)) == -1) {
	fprintf(stderr,"line %zu's format is wrong\n",count);
	exit(EXIT_FAILURE);
      };
      splitLineN(ans,line,len,posEq);
      free(line);
      sz = 0;
    }
  }  
  if (ans->pair == NULL) {
    fprintf(stderr,"Couldn't read any line from the keys\values file\n");
    exit(EXIT_FAILURE);
  }
  return ans;
}

kvarray_t * readKVs(const char * fname) {
  /*  In readKVs, you will want to open the file, read the lines of text, split them into
    key/value pairs, add the resulting pairs to an array (hint: realloc it to make it larger
each time), close the file, and return the kvarray_t * that has your array.
    Remember that you will want to abstract out complex steps into functions (you should
see at least 2 pieces to naturally pull out into their own functions).
    //WRITE ME
    */
  FILE * f = fopen(fname,"r");
  if (f == NULL) {
    perror("Could not open the keys/values file");
    exit(EXIT_FAILURE);
    }
  kvarray_t * KVArray = readSplitLines(f);
  if (fclose(f)!=0) {
    perror("Failed to close the keys/values file");
    exit(EXIT_FAILURE);
    }
  return KVArray;
}

void freeKVs(kvarray_t * pairs) {
  /* Next, you will write freeKVs, which should free all the memory allocated by readKVs.
That is,  freeKVs(readKVs(filename)) should not leak any memory.
  //WRITE ME
  */
  for (size_t i = 0; i < (pairs->lenght); i++) {
    free((pairs->pair[i]).key);
    free((pairs->pair[i]).value);
  }
  free(pairs->pair);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  /* 
Third, write printKVs which should take a kvarray_t *, and print out
 "key = '%s' value = '%s'\n"
for each key/value pair in the array, with the first %s being whatever the key is,
and the second being whatever value (e.g., key = 'Jean Luc Picard' value = 'Captain').
//WRITE ME
*/
  for (size_t i = 0; i < (pairs->lenght); i++) {
    printf("key = '%s' value = '%s'\n",(pairs->pair[i]).key,(pairs->pair[i]).value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  /*
Finally, write the lookupValue function, which takes a kvarray_t * and a char * (string).
The char * that is passed in represents a key.  This function searches the kvarray_t 
for a matching key, and if found, returns the corresponding value.  If no match is found,
this function returns NULL.
  //WRITE ME
  */
  for (size_t i = 0; i < (pairs->lenght); i++) {
    if (strcmp((pairs->pair[i]).key,key) == 0) { return (pairs->pair[i]).value; }
  }
  return NULL;
}
