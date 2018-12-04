#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  FILE * f = fopen(filename,"r");
  if (f == NULL) {
    perror("Could not open the list file");
    fprintf(stderr,"%s\n",filename);
    exit(EXIT_FAILURE);
  }
  counts_t * ans = createCounts();
  size_t sz = 0;
  ssize_t len = 0;
  char * line = NULL;
  while ((len = getline(&line,&sz,f))>=0) {
    if (len > 1) {
      line[strlen(line)-1]='\0';
      char * val = lookupValue(kvPairs, line);
      addCount(ans,val);
      free(line);
      sz = 0;
    }
  }
  free(line);
  if (fclose(f)!=0) {
    perror("Failed to close the list file");
    fprintf(stderr,"%s\n",filename);
    exit(EXIT_FAILURE);
  }
  return ans;
}

int main(int argc, char ** argv) {
  if (argc <= 1) {
    fprintf(stderr,"Usage: count_values key_value_file list1 list2 ... listn\n");
    return EXIT_FAILURE;
  }
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  kvarray_t * kv = readKVs(argv[1]);
  //count from 2 to argc (call the number you count i)
  for (size_t i = 2; i < argc; i++) {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    counts_t * c = countFile(argv[i], kv);
    //compute the output file name from argv[i] (call this outName)
    char * outName = computeOutputFileName(argv[i]);
    //open the file named by outName (call that f)
    FILE * f = fopen(outName,"w");
    if (f == NULL) {
      perror("Could not create the output file");
      fprintf(stderr,"%s\n",outName);
      return EXIT_FAILURE;
    }
    //print the counts from c into the FILE f
    printCounts(c, f);
    //close f
    if (fclose(f)!=0) {
      perror("Failed to close the output file");
      fprintf(stderr,"%s\n",outName);
      return EXIT_FAILURE;
    }
    //free the memory for outName and c
    free(outName);
    freeCounts(c);
  }
  //free the memory for kv
  freeKVs(kv);
  return EXIT_SUCCESS;
}
