#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int readMatrix(FILE * f, char matrix[10][10]) {
  int c;
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      c = fgetc(f);
      if ((c == '\n') || (c == EOF)) { return i+1; }
      else { matrix[i][j] = c; }
    }
    c = fgetc(f);
    if ((c != '\n') || (c == EOF)) { return i+1; }
  }
  c = fgetc(f);
  if (c != EOF) { return 11; }
  return 0;
}

void rotateMatrix(char matrix[10][10]) {
  char temp;
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      temp = matrix[i][j];
      matrix[i][j] = matrix[9-j][i];
      matrix[9-j][i] = matrix[9-i][9-j];
      matrix[9-i][9-j] = matrix[j][9-i];
      matrix[j][9-i] = temp;
    }
  }
}

void printMatrix(char matrix[10][10]) {
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      fprintf(stdout,"%c",matrix[i][j]);
    }
    fprintf(stdout,"\n");
  }
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr,"Usage rotateMatrix inputFilename\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1],"r");
  if (f == NULL) {
    fprintf(stderr,"Could not open file\n");
    return EXIT_FAILURE;
  }
  char matrix[10][10];
  int readResult;
  if ((readResult = readMatrix(f,matrix)) > 0) {
    fprintf(stderr,"There is a problem with line %d\n",readResult);
    return EXIT_FAILURE;
  };
  if (fclose(f) != 0) {
    fprintf(stderr,"Failed to close the input file\n");
    return EXIT_FAILURE;
  }
  rotateMatrix(matrix);
  printMatrix(matrix);
  return EXIT_SUCCESS;
}
