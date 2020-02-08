/*  MPA2019   */
#include "mlisp.h"
double a = 0;
double b = 1;
double fun(double x);//DECLARATION
double eps = 0.00001;
double golden__section__search(double a, double b);//DECLARATION
double golden__start(double a, double b);//DECLARATION
double mphi = 0;
double __MPA2019__try(double a, double b, double xa, double ya, double xb, double yb);//DECLARATION
double xmin = 0;
//________________ 
double fun(double x){//DEFINITION
  { //let
    double z = (x - 13 * (double(1) / 14) * (double(1) / e));
    return (z - 2 * sin(z) * cos(z) - 0.5);
  } //let
}
double golden__section__search(double a, double b){//DEFINITION
  { //let
    double xmin = (((a < b)) ? golden__start(a, b) : golden__start(b, a));
    newline();
    return xmin;
  } //let
}
double golden__start(double a, double b){//DEFINITION
  mphi = 0.5 * (3 - sqrt(5));
  { //let
    double xa = (a + mphi * (b - a));
    double xb = (b - mphi * (b - a));
    return __MPA2019__try(a, b, xa, fun(xa), xb, fun(xb));
  } //let
}
double __MPA2019__try(double a, double b, double xa, double ya, double xb, double yb){//DEFINITION
  return (abs((a - b)) < eps) ? ((a + b) * 0.5) : (display("+"), (ya < yb) ? (b = xb, xb = xa, yb = ya, xa = (a + mphi * (b - a)), __MPA2019__try(a, b, xa, fun(xa), xb, yb)) : (a = xa, xa = xb, ya = yb, xb = (b - mphi * (b - a)), __MPA2019__try(a, b, xa, ya, xb, fun(xb))));
}
int main(){
 xmin = golden__section__search(a, b);
 display("interval=\t[");
 display(a);
 display(" , ");
 display(b);
 display("]\n");
 display("xmin=\t\t");
 display(xmin); newline();
 display("f(xmin)=\t");
 display(fun(xmin)); newline();
 std::cin.get();
 return 0;
}

