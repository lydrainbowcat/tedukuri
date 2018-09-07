/*
 * D - Running Median
 * ACM International Collegiate Programming Contest
 * Greater New York Region
 * October 18, 2009
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#define NUMS_PER_LINE   10

char inbuf[256];

int indata[10000];
int outdata[5010];

int readcnt = 0;
char *curPtr = &(inbuf[0]);
int incnt = 0;
int linecnt = 0;
int outcnt = 0;
int remcnt = 0;

void GInit(int probsz)
{
   readcnt = NUMS_PER_LINE;
   curPtr = &(inbuf[0]);
   incnt = 0;
   linecnt = 0;
   outcnt = 0;
   remcnt = probsz;
}

int ReadInput(int *value, int curprob)
{
   int val;
   if(readcnt >= NUMS_PER_LINE)
   {
      linecnt++;
      readcnt = 0;
      curPtr = &(inbuf[0]);
      if(fgets(&(inbuf[0]), 255, stdin) == NULL)
      {
         fprintf(stderr, "Data read failed on problem %d value %d line %d\n",
            curprob, incnt, linecnt);
         return -10;
      }
   }
   val = atoi(curPtr);
   readcnt++;
   indata[incnt++] = val;
   *value = val;
   remcnt--;
   if(readcnt < NUMS_PER_LINE)
   {
      while((*curPtr != 0) && !isspace(*curPtr)) curPtr++;
      if((remcnt > 0) && (*curPtr != ' '))
      {
         fprintf(stderr, "missing space on problem %d value %d line %d\n",
            curprob, incnt, linecnt);
         return -11;
      }
      curPtr++;
      if((remcnt > 0) && ((*curPtr == 0) || isspace(*curPtr)))
      {
         fprintf(stderr, "bad format on problem %d value %d line %d\n",
            curprob, incnt, linecnt);
         return -12;
      }
   }
   return 0;
}

int NextMedian(int new1, int new2)
{
   int tmp, i;
   if(new1 > new2)
   {
      tmp = new1;
      new1 = new2;
      new2 = tmp;
   }
   i = incnt - 3;   // last before new guys
   while((i >= 0) && (indata[i] > new2))
   {
      indata[i+2] = indata[i];
      i--;
   }
   indata[i+2] = new2;
   while((i >= 0) && (indata[i] > new1))
   {
      indata[i+1] = indata[i];
      i--;
   }
   indata[i+1] = new1;
   return indata[incnt/2];
}

int PrintSoln(int value, int last)
{
   outcnt++;
   if((outcnt == NUMS_PER_LINE) || last)
   {
      outcnt = 0;
      printf("%d\n", value);
   }
   else
   {
      printf("%d ", value);
   }
   return 0;
}

int main()
{
   int nprob, curprob, probsz, ret, index;
   int v1, v2, med;

   if(fgets(&(inbuf[0]), 255, stdin) == NULL)
   {
      fprintf(stderr, "Read failed on problem count\n");
      return -1;
   }
   if(sscanf(&(inbuf[0]), "%d", &nprob) != 1)
   {
      fprintf(stderr, "Scan failed on problem count\n");
      return -2;
   }
   for(curprob = 1; curprob <= nprob ; curprob++)
   {
      if(fgets(&(inbuf[0]), 255, stdin) == NULL)
      {
         fprintf(stderr, "Read failed on problem %d size\n", curprob);
         return -3;
      }
      if(sscanf(&(inbuf[0]), "%d %d", &index, &probsz) != 2)
      {
         fprintf(stderr, "Scan failed on problem %d size\n", curprob);
         return -4;
      }
      if(probsz < 1)
      {
         fprintf(stderr, "problem size %d is < 1 in problem %d\n", probsz, curprob);
         return -5;
      }
      if((probsz & 1) == 0)
      {
         fprintf(stderr, "problem size %d is even in problem %d\n", probsz, curprob);
         return -6;
      }
      if(index != curprob)
      {
         fprintf(stderr, "problem index %d not = expected problem %d\n", index, curprob);
         return -7;
      }
      printf("%d %d\n", curprob, (probsz + 1)/2);
      GInit(probsz);
      if((ret = ReadInput(&v1, curprob)) != 0)
      {
         return ret;
      }
      if(probsz == 1)
      {
         PrintSoln(v1, 1);
      }
      else
      {
         PrintSoln(v1, 0);
         while(incnt < (probsz - 2))
         {
            if((ret = ReadInput(&v1, curprob)) != 0)
            {
               return ret;
            }
            if((ret = ReadInput(&v2, curprob)) != 0)
            {
               return ret;
            }
            med = NextMedian(v1, v2);
            PrintSoln(med, 0);
         }
         if((ret = ReadInput(&v1, curprob)) != 0)
         {
            return ret;
         }
         if((ret = ReadInput(&v2, curprob)) != 0)
         {
            return ret;
         }
         med = NextMedian(v1, v2);
         PrintSoln(med, 1);
      }
   }
   return 0;
}
