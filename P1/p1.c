#include <stdio.h>
void f(int a, int b, int c){
  unsigned int i,j,k;
  unsigned int array[5];
  i=555;
  j=666;
  k=777;
  for (j=0;j<5;j++) array[j]=b+j+1;
  if (b<200) f(a,b*10,c*3);
  	else for (j=0;j<150;j++) printf("0x%x\t------>\t0x%x (%u)\n",&array[j],array[j],array[j]);
  }
  	
  main(){
  	f(1,2,3);
  }