#include <stdio.h>
#include <stdlib.h>

#define MAX_SOLDIERS 10000

int number_of_soldiers;
long number_of_moves;

struct t_soldier {
                   int x,y;
                 } soldiers[MAX_SOLDIERS];

FILE *fp;

void read_input(void)
{
  int i;

  // reading from "SOLDIERS.IN"

  fp = fopen("SOLDIERS.IN","rt");

  fscanf(fp,"%d",&number_of_soldiers);

  for (i = 0;i < number_of_soldiers;++i)
    fscanf(fp,"%d %d",&(soldiers[i].x),&(soldiers[i].y));

  fclose(fp);
}

// compare function for "qsort", sorting by y coordinate

int sort_y(const void *a,const void *b)
{
  if (((struct t_soldier *) a)->y > ((struct t_soldier *) b)->y )
    return 1;

  if (((struct t_soldier *) a)->y < ((struct t_soldier *) b)->y )
    return -1;

  return 0;
}

// compare function for "qsort", sorting by x coordinate

int sort_x(const void *a,const void *b)
{
  if (((struct t_soldier *) a)->x > ((struct t_soldier *) b)->x)
    return 1;

  if (((struct t_soldier *) a)->x < ((struct t_soldier *) b)->x)
    return -1;

  return 0;
}

// compare function for "qsort", sorting by ascending order

int sort_x_dec(const void *a, const void *b)
{
  if (*((int *) a) > *((int *) b))
    return 1;

  if (*((int *) a) < *((int *) b) )
    return -1;

  return 0;
}

void solve(void)
{
  int i;
  int dest_x,dest_y;
  int x_dec[MAX_SOLDIERS];

  qsort(soldiers,number_of_soldiers,sizeof(soldiers[0]),sort_y);

  // "dest_y" is median of y coordinates of soldiers

  dest_y = soldiers[number_of_soldiers / 2].y;

  qsort(soldiers,number_of_soldiers,sizeof(soldiers[0]),sort_x);

  // decreasing x coordinates of soldiers

  for (i = 0;i < number_of_soldiers;++i)
    x_dec[i] = soldiers[i].x - i;

  qsort(x_dec,number_of_soldiers,sizeof(x_dec[0]),sort_x_dec);

  // "dest_x" is median of decresead x coordinates

  dest_x = x_dec[number_of_soldiers / 2];

  // calculating of "number_of_moves"

  number_of_moves = 0l;

  for (i = 0;i < number_of_soldiers;++i)
    number_of_moves += abs(soldiers[i].x - (dest_x + i)) +
                       abs(soldiers[i].y - dest_y);
}

void write_output(void)
{
  // writing to "SOLDIERS.OUT"

  fp = fopen("SOLDIERS.OUT","wt");

  fprintf(fp,"%ld\n",number_of_moves);

  fclose(fp);
}

int main()
{
  read_input();

  solve();

  write_output();

  return 0;
}