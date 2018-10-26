#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n) ;

int main(void) {
  int array1[] = {1,2,3,4,5};
  size_t size1 = 5;
  size_t ans1 = 5;

  int array2[] = {1,2,3,3,10};
  size_t size2 = 5;
  size_t ans2 = 3;
  
  int array3[] = {5,4,3,2,1};
  size_t size3 = 5;
  size_t ans3 = 1;
  
  int array4[] = {1,2,3,4,5,1,2,3,4,5};
  size_t size4 = 10;
  size_t ans4 = 5;
  
  int array5[] = {0,1,2,3,4,5};
  size_t size5 = 6;
  size_t ans5 = 6;
  
  int array6[] = {-2,-1,0,1,2,3,4,5};
  size_t size6 = 8;
  size_t ans6 = 8;
  
  int array7[] = {-5,-3,-1};
  size_t size7 = 3;
  size_t ans7 = 3;
  
  int array8[] = {1000000000,1100000000,1200000000};
  size_t size8 = 3;
  size_t ans8 = 3;
  
  int array9[] = {-1200000000,-1100000000,-1000000000};
  size_t size9 = 3;
  size_t ans9 = 3;
  
  int array10[10];
  for (size_t i = 0; i < 10; i++) {
    if (i % 2 == 0) {array10[i] = i;}
    else {array10[i] = -i;}
  }
  size_t size10 = 10;
  size_t ans10 = 2;
  
  int array11[] = {1,2,3};
  size_t size11 = 0; //with size 0
  size_t ans11 = 0; //with size 0
  
  int array12[] = {0};
  size_t size12 = 1;
  size_t ans12 = 1;

  if (maxSeq(array1, size1) != ans1) {
    printf("Failed on array1, instead of %d, gave %d", (int)ans1, (int)maxSeq(array1, size1));
    return EXIT_FAILURE;
  }
  if (maxSeq(array2, size2) != ans2) {
    printf("Failed on array2, instead of %d, gave %d", (int)ans2, (int)maxSeq(array2, size2));
    return EXIT_FAILURE;
  }
  if (maxSeq(array3, size3) != ans3) {
    printf("Failed on array3, instead of %d, gave %d", (int)ans3, (int)maxSeq(array3, size3));
    return EXIT_FAILURE;
  }
  if (maxSeq(array4, size4) != ans4) {
    printf("Failed on array4, instead of %d, gave %d", (int)ans4, (int)maxSeq(array4, size4));
    return EXIT_FAILURE;
  }
  if (maxSeq(array5, size5) != ans5) {
    printf("Failed on array5, instead of %d, gave %d", (int)ans5, (int)maxSeq(array5, size5));
    return EXIT_FAILURE;
  }
  if (maxSeq(array6, size6) != ans6) {
    printf("Failed on array6, instead of %d, gave %d", (int)ans6, (int)maxSeq(array6, size6));
    return EXIT_FAILURE;
  }
  if (maxSeq(array7, size7) != ans7) {
    printf("Failed on array7, instead of %d, gave %d", (int)ans7, (int)maxSeq(array7, size7));
    return EXIT_FAILURE;
  }
  if (maxSeq(array8, size8) != ans8) {
    printf("Failed on array8, instead of %d, gave %d", (int)ans8, (int)maxSeq(array8, size8));
    return EXIT_FAILURE;
  }
  if (maxSeq(array9, size9) != ans9) {
    printf("Failed on array9, instead of %d, gave %d", (int)ans9, (int)maxSeq(array9, size9));
    return EXIT_FAILURE;
  }
  if (maxSeq(array10, size10) != ans10) {
    printf("Failed on array10, instead of %d, gave %d", (int)ans10, (int)maxSeq(array10, size10));
    return EXIT_FAILURE;
  }
  if (maxSeq(array11, size11) != ans11) {
    printf("Failed on array11, instead of %d, gave %d", (int)ans11, (int)maxSeq(array11, size11));
    return EXIT_FAILURE;
  }
  if (maxSeq(array12, size12) != ans12) {
    printf("Failed on array12, instead of %d, gave %d", (int)ans12, (int)maxSeq(array12, size12));
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
