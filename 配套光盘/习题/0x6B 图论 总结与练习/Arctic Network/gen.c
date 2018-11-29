#include <stdio.h>
#include <stdlib.h>

int C,i,j,k,m,n;
int x[1000], y[1000];

main(){
   printf("3\n");
   for (C=1;C<=100;C*=10) {
   for (i=0;i<1000;i++) {
      x[i] = random()%10000;
      y[i] = random()%10000;
   }
      printf("%d 500\n",C);
      for (i=0;i<500;i++) printf("%d %d\n",x[i],y[i]);
   }
}
