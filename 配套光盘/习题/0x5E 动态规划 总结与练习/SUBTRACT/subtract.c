
#include <stdio.h>

#define MAX_N 100
#define MAX_VALUE 100
#define FLAG -5

int n,t;
int numbers[MAX_N];
int signs[MAX_N];

FILE *fp;

void read_input(void)
{
  int i;

  // reading from "SUBTRACT.IN"

  fp = fopen("SUBTRACT.IN","rt");

  fscanf(fp,"%d %d",&n,&t);

  for (i = 0;i < n;++i)
    fscanf(fp,"%d",numbers + i);

  fclose(fp);
}

void solve(void)
{
  int i,j;
  int sum,target,number;
  int table[2 * MAX_VALUE * MAX_N + 1];

  // calculating "sum" of all numbers and "target"
  // first number in sequence must be plus, second must be minus

  sum = 0;

  for (i = 2;i < n;++i)
    sum += numbers[i];

  target = sum - (t - (numbers[0] - numbers[1]));

  // dynamically generating "table", looking for target

  table[0] = -1;

  for (i = 1;i <= target;++i)
    table[i] = FLAG;

  for (i = 2;i < n;++i)
  {
    for (j = target - 1;j >= 0;--j)
      if (table[j] != FLAG)
      {
        if (table[j + 2 * numbers[i]] == FLAG)
          table[j + 2 * numbers[i]] = i;

        if (table[target] != FLAG)
          break;
      }

    if (table[target] != FLAG)
      break;
  }

  // generating "signs", some numbers will have plus sign in front of them
  // some numbers will have minus sign

  signs[0] = 1;

  signs[1] = -1;

  for (i = 2;i < n;++i)
    signs[i] = 1;

  number = target;

  do
  {
    if (!number)
      break;

    signs[table[number]] = -1;
    number -= 2 * numbers[table[number]];
  } while (1);

}

void write_output(void)
{
  int i;
  int number,counter,temp;

  // writing to "SUBTRACT.OUT"

  fp = fopen("SUBTRACT.OUT","wt");

  // transforming "signs" to sequence of contractions
  // going from end of "signs", looking for subsequence with minus sign on
  // the beginning and plus signs on the rest of subsequence

  number = n - 1;
  counter = 0;

  do
  {
    while (signs[number] == -1)
      --number;

    if (!number)
      break;

    temp = 0;

    while (signs[number] == 1)
    {
      --number;
      ++temp;
    }

    for (i = 0;i < temp;++i)
    {
      fprintf(fp,"%d\n",number + 1);
      ++counter;
    }

    --number;
  } while (1);

  // other contractions is 1, total number of contractions must be n-1

  for (i = 0;i < n - 1 - counter;++i)
    fprintf(fp,"1\n");

  fclose(fp);
}

int main(void)
{
  read_input();

  solve();

  write_output();

  return 0;
}
