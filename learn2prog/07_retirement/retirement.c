#include <stdio.h>
#include <stdlib.h>


struct _retire_info{
  int months;
  double contribution, rate_of_return;
};

typedef struct _retire_info retire_info;



void retirement (int startAge, double initial, retire_info working, retire_info retired){
    int month_number = 3;
  for (int i=0; i<working.months; i++){
    printf("Age %3d month %2d you have $%.2lf\n", startAge/12 , month_number, initial );
    if (month_number == 11){
      month_number = 0;
    } else{ month_number += 1;}
    startAge += 1;

    initial += initial * working.rate_of_return / 12;  
    initial += working.contribution;
  }


  for (int i=0; i <retired.months; i++){
    printf("Age %3d month %2d you have $%.2lf\n", startAge/12, month_number, initial );
    if ( month_number  == 11 ){
      month_number = 0;
    } else{ month_number += 1;}
    startAge += 1;

    initial += initial * retired.rate_of_return / 12;
    initial -= retired.contribution;
  }

}

int main(void){
  retire_info working, retired;
  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045;  
  retired.months = 384;
  retired.contribution = 4000;
  retired.rate_of_return = 0.01;
  
  retirement(327, 21345, working, retired);

  return EXIT_SUCCESS;

}



