#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"

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
  free(line);
  return ans;
}

kvarray_t * readKVs(const char * fname) {
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
  for (size_t i = 0; i < (pairs->lenght); i++) {
    free((pairs->pair[i]).key);
    free((pairs->pair[i]).value);
  }
  free(pairs->pair);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  for (size_t i = 0; i < (pairs->lenght); i++) {
    printf("key = '%s' value = '%s'\n",(pairs->pair[i]).key,(pairs->pair[i]).value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  for (size_t i = 0; i < (pairs->lenght); i++) {
    if (strcmp((pairs->pair[i]).key,key) == 0) { return (pairs->pair[i]).value; }
  }
  return NULL;
}
