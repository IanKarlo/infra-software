#include <math.h>
#include <stdio.h>

#define FUNC_QUANT 6

//funcoes


int add(int x,int y) {return x+y;}
int mul(int x,int y) {return x*y;}
int dvs(int x,int y) {return x/y;}
int sub(int x,int y) {return x-y;}

int elv(int x,int y) {return pow(x,y);}
int sum(int x,int y){
  int total=0;
  for(int i=x;i<=y;i++) total+=i;
  return total;
}