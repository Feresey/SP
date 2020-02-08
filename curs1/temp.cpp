/*  CAA2019   */
#include "mlisp.h"
double __CAA2019__try(double x);//DECLARATION
double f(double x, double y);//DECLARATION
//________________ 
double __CAA2019__try(double x){//DEFINITION
  x = f(x, x);
  ;
  return x;
}
double f(double x, double y){//DEFINITION
  return (x * y);
}
int main(){
 display("No calculations!");newline();
 std::cin.get();
 return 0;
}

