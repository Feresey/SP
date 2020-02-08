/*  MPA2019   */
#include "mlisp.h"
double __MPA2019__try(double x);//DECLARATION
//________________ 
double __MPA2019__try(double x){//DEFINITION
  x = x * x;
  return x;
}
int main(){
 display(__MPA2019__try(2)); newline();
 std::cin.get();
 return 0;
}

