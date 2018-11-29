/*
   Solves the problem using dynamic programming,
   time complexity: O ( item_nr * slot_nr )
   (should be faster than sol2.c)
*/

#include <stdio.h>

#define   MAX_SLOT_NR  	101 
#define   MAX_ITEM_NR   101

/* the table weight keeps the weight of each item in each slot  */
/* it will also be used to calculate the best (maximum) weights */
int    weight[MAX_ITEM_NR][MAX_SLOT_NR];

/* the table index will be used to keep the solution(s) */
int    f_index[MAX_ITEM_NR][MAX_SLOT_NR];

int    slot_nr;   /* the number of slots */
int    item_nr;   /* the number of items */
FILE *outf;

void  get_input();
void  solve();
void  print_solution();
void  print_slots(int item, int slot);
void  print_table(int* table);


void get_input()
/* gets 'slot_nr', 'item_nr' from the file 'input.txt'    */
/* and fills the table 'weight' with data from this file  */
{
  int i,j;

  FILE *f = fopen("FLOWER.INP", "r");

  fscanf(f, "%d %d\n", &item_nr, &slot_nr);

  for (i=0; i < item_nr; i++)
    for (j=0; j < slot_nr; j++)
      fscanf(f, "%d ", &(weight[i][j]) );

  fclose(f);
}


void solve()
/* calculates the maximum sum of weights for each item in each slot */
/* and also fills the 'index' table with info about how we obtained */
/* this maximum (needed to output the solutions)                    */
{
  int i, j, k;
  int wmax;
  int imax;

  for (i=1; i < item_nr; i++)
    {
      imax = i-1;
      wmax = weight[i-1][imax];
      for (j=i; j <= (slot_nr - item_nr + i); j++)
        {
          if (weight[i-1][j-1] > wmax)
            {
              wmax = weight[i-1][j-1];
              imax = j-1;   /* record the index of maximum */
            }
          weight[i][j] += wmax;
          f_index[i][j] = imax;
        }
    }
}


void print_solution()
{
  int wmax;
  int imax;
  int j;

  /* take as max the first one */
  imax = item_nr - 1;
  wmax = weight[item_nr-1][imax];

  for (j=item_nr-1; j < slot_nr; j++) 
    if ( weight[item_nr-1][j] > wmax )
      {
        wmax = weight[item_nr-1][j];
        imax = j;
      }

  fprintf(outf, "%d\n", weight[item_nr-1][imax]);
  print_slots(item_nr-1, imax);
}


void print_slots(int item, int slot)
/* postorder recursive function */
{
  int prev_slot;

  if (item == 0)   fprintf(outf, "%d ", slot+1);
  else
    {
      prev_slot = f_index[item][slot];
      print_slots(item-1, prev_slot);
      fprintf(outf, "%d ", slot+1);
    }
}

/*  for debugging purposes
void print_table(int* table)
{
  int i, j;

  printf("\n  %d  %d \n\n", item_nr, slot_nr);
  for (i=0; i < item_nr; i++)
    {
      for (j=0; j < slot_nr; j++)
         printf(" %4d", *(table + i*MAX_SLOT_NR + j) );
      printf("\n");
    }
}*/


int main()
{
  get_input();

/* for debug
  printf("\n input table (weights): ");
  print_table((int*)weight);
*/

  solve();

/* for debug
  printf("\n processed table (cumulative weights): ");
  print_table((int*)weight);

  printf("\n index table: ");
  print_table((int*)index);
*/

  outf = fopen("FLOWER.OUT", "w");
  print_solution();
  fclose(outf);

  return 0;
}
