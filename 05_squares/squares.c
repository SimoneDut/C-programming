#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
  if (a >= b) {
    return a;
  }
  else {
    return b;
  }
}

int app_s(int x, int y, int size) {
      // check if EITHER
      //    x is less than size1 AND (y is either 0 or size1-1)
      // OR
      //    y is less than size1 AND (x is either 0 or size1-1)
  if ((((x>=0)&&(x<size))&&((y==0)||(y==(size-1))))||(((y>=0)&&(y<size))&&((x==0)||(x==(size-1))))) {
    return 1;
  }
  else {
    return 0;
  }
}


void squares(int size1, int x_offset, int y_offset, int size2) {
  //compute the max of size1 and (x_offset + size2).  Call this w
  int w = max(size1,x_offset+size2);
  //compute the max of size1 and (y_offset + size2).  Call this h
  int h = max(size1,y_offset+size2);
  //count from 0 to h. Call the number you count with y
  for (int j=0;j<h;j++) {
    //count from 0 to w. Call the number you count with x
    for (int i=0;i<w;i++) {
      //check if  EITHER
      //    ((x is between x_offset  and x_offset +size2) AND 
      //     y is equal to either y_offset OR y_offset + size2 - 1 )
      //  OR
      //    ((y is between y_offset and y_offset + size2) AND
      //     x is equal to either x_offset OR x_offset + size2 -1)
      // if so, print a *
      if (app_s(i-x_offset,j-y_offset,size2)==1) {
	printf("*");
      }
      //if not,
      // check if EITHER
      //    x is less than size1 AND (y is either 0 or size1-1)
      // OR
      //    y is less than size1 AND (x is either 0 or size1-1)
      //if so, print a #
      else {
	if (app_s(i,j,size1)==1) {
	    printf("#");
	}
      //else print a space
        else {
	  printf(" ");
	}	
      }
    //when you finish counting x from 0 to w, 
    //print a newline
    }
  printf("\n");
  }
}
