#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}

//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

char ** readData(FILE * f, size_t * count_p) {
  char ** lines = NULL;
  char * curr = NULL;
  size_t sz;
  *count_p = 0;
  while (getline(&curr,&sz,f)>=0) {
    if ((f == stdin) && (curr[0] == '\n')) {
      free(curr);
      return lines;
    }
    lines = realloc(lines,((*count_p)+1)*sizeof(*lines));
    lines[*count_p] = curr;
    curr = NULL;
    (*count_p)++;
  }
  free(curr);
  return lines;
}

void printData(char ** data, size_t count) {
  for (size_t i = 0; i < count; i++) {
    printf("%s",data[i]);
  }
}

void freeData(char ** data, size_t count) {
  for (size_t i = 0; i < count; i++) {
    free(data[i]);
  }
  free(data);
}

void processFile(FILE * f) {
  size_t count = 0;
  char ** data = readData(f,&count);
  if (count > 1) { sortData(data,count); }
  printData(data,count);
  freeData(data,count);
}

int main(int argc, char ** argv) {
  if (argc < 1) {
    fprintf(stderr,"Wrong usage format\n");
    return EXIT_FAILURE;
  }
  else if (argc == 1) {
    processFile(stdin);
  }
  else {
    for (int i=1; i<argc; i++) {
      FILE * f = fopen(argv[i], "r");
      if (f == NULL) {
	perror("Could not open file");
	return EXIT_FAILURE;
      }
      processFile(f);
      if (fclose(f) != 0) {
	perror("Could not close file");
	return EXIT_FAILURE;
      }
    }
  }
  return EXIT_SUCCESS;
}
