#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);

unsigned my_power(unsigned x, unsigned y) {
  if (y == 0) {
    return 1;
  }
  else {
    return x * my_power(x,y-1);
  }
}

void run_check(unsigned x, unsigned y, unsigned expected_ans) {
  unsigned given_ans = power(x,y);
  if (given_ans!=expected_ans) {
    printf("%d to the power of %d gives %d instead of %d",x,y,given_ans,expected_ans);
    exit(EXIT_FAILURE);
  }
}

int main() {
  for (int x=0; x<=9; x++) {
    for (int y=0; y<=9; y++) {
      run_check((unsigned int)x,(unsigned int)y,my_power((unsigned int)x,(unsigned int)y));
    }
  }
  return EXIT_SUCCESS;
}
