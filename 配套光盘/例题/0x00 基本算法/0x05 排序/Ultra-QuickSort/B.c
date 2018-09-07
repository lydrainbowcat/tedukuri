#include <stdlib.h>
#include <stdio.h>

int N;
#define RANGE 100000;

int p[1000000],new[1000000];
long long count;

main(){
  register i,j;
  while (1 == scanf("%d",&N) && N) {
   for (i=0;i<N;i++) scanf("%d",&p[i]);
   count=0;
   sort(0,N);
   printf("%lld\n",count);
 }
}

sort(int a, int b){
   register mx, mn, md, below, mdi, ni, i, j;

   if (a >= b) return;

   /* naive pivot selection - handles obvious pathologies */

   md = p[a+(b-a)/2];
   
   /* move everything above the pivot over everything below */

   for (mdi=i=a;i<b;i++) if (p[i] < md) mdi++;
   below = mdi-a;
   for (ni=i=a;i<b;i++){
      if (p[i] < md) {
         new[ni++] = p[i];
         below--;
      }else{
         new[mdi++] = p[i];
         count += below;
      }
   }

   /* shuffle the pivot to the middle */

   for (mdi=a;new[mdi] != md;mdi++);
   for (mdi;mdi && new[mdi-1] > md;mdi--){
      int tmp = new[mdi-1];
      new[mdi-1] = new[mdi];
      new[mdi] = tmp;
      count++;
   }
   for (i=a;i<b;i++) p[i] = new[i];
         
   sort(a,mdi);
   while(mdi < b && p[mdi] == md) mdi++;  /* skip pivot & duplicates */
   sort(mdi,b);
}
