/*  MPA2019   */
#include "mlisp.h"
double f(double x);//DECLARATION
double g(double x);//DECLARATION
//________________ 
double f(double x){//DEFINITION
  return (double(1) / x);
}
double g(double x){//DEFINITION
  return (1 + x);
}
int main(){
 display(g(5)); newline();
 display(k(9)); newline();
 std::cin.get();
 return 0;
}

