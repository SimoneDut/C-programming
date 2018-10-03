#include <stdio.h>
#include <stdlib.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};

typedef struct _retire_info retire_info;

double calculate(int Age, double initial_capital, retire_info conditions) {
  double capital = initial_capital;
  for(int i=Age;i<(Age+conditions.months);i++) {
    printf("Age %3d month %2d you have $%.2lf\n",i/12,i%12,capital);
    capital = capital*(1.0+conditions.rate_of_return)+conditions.contribution;
  }    
  return capital;
}

void retirement(int startAge, //in months
	        double initial, //initial savings in dollars
        	retire_info working, //info about working
		retire_info retired) { //info about being retired
  double final;
  final = calculate(startAge,initial,working);
  final = calculate(startAge+working.months,final,retired);
}

int main(void) {
  retire_info working;
  working.months=489;  
  working.contribution=1000;
  working.rate_of_return=0.045/12.0;
  retire_info retired;
  retired.months=384;
  retired.contribution=-4000;
  retired.rate_of_return=0.01/12.0;
  int startAge = 327;
  int initial = 21345;
  retirement(startAge,initial,working,retired);
  return EXIT_SUCCESS;
}
