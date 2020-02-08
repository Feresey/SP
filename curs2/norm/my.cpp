/*  MPA2019   */
#include "mlisp.h"
double even__bits(double n);//DECLARATION
//________________ 
double even__bits(double n){//DEFINITION
  return (n == 0) ? (1) : (odd__bits(quotient(n, 2)));
}
int main(){
 display("No calculations!");newline();
 std::cin.get();
 return 0;
}

