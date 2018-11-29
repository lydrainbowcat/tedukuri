/* 
   The proper way to do this is with Union Find, but 
   binary search works OK, too.  O(n^2 log d) where
   d is the max distance.  

   The recursive connected components implementaiton
   is a dog on Sun SPARC.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int i,j,k,N,C,P;
int x[1000],y[1000];
double dsq,delta;
int mark[1000];

void set(int w, int c, double d) {
   int i,j,k;
   if (mark[w]) return;
   mark[w] = c;
   for (i=0;i<P;i++) {
      if ((x[i]-x[w])*(x[i]-x[w]) + (y[i]-y[w])*(y[i]-y[w]) < d) {
         set(i,c,d);
      }
   }
}

int try(double d) {
   int i,j,k=0;
   memset(mark,0,sizeof(mark));
   for (i=0;i<P;i++) {
      if (mark[i]) continue;
      set(i,++k,d);
   }
   return k;
}

main(){
   scanf("%d",&N);
   while (N--) {
      scanf("%d%d",&C,&P);
      for (i=0;i<P;i++) scanf("%d%d",&x[i],&y[i]);
      dsq = 100;
      for (delta = 100000000;delta > .00001; delta *=.5) {
         if (try(dsq) > C) dsq += delta;
         else dsq -= delta;
      }
      printf("%0.2lf\n",sqrt(dsq));
   }
}
