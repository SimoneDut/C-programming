#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n) {
  if (n<=0) {return 0;}
  size_t longestSeq = 1;
  size_t tempSeq = 1;
  for (size_t i=1; i<n; i++) {
    if (array[i]>array[i-1]) {tempSeq++;}
    else {tempSeq=1;}
    if (tempSeq>longestSeq) {longestSeq=tempSeq;}
  }
  return longestSeq;
}
