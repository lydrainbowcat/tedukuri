#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100
#define INF 4000000L

int n, m;
unsigned long int (*d)[MAXN], (*q)[MAXN];

int main(void)
{
  FILE *f, *g;
  int i, j, k;
  int x, y;
  unsigned long int z, z0;

  d = malloc(sizeof(long int) * MAXN * MAXN);
  q = malloc(sizeof(long int) * MAXN * MAXN);
  if (!d || !q) return 1;

  f = fopen("trip.in", "r");
  if (!f || fscanf(f, "%d%d", &n, &m) != 2)
    return 1;

  for(i=0; i<n; i++)
    for(j=0; j<n; j++)
      d[i][j] = q[i][j] = INF;

  for(i=0; i<m; i++)
    {
      fscanf(f, "%d%d%ld", &x, &y, &z);
      x--, y--;
      if (d[x][y] > z && x != y)
	d[x][y] = d[y][x] = z;
    }
  fclose(f);

  z = INF;
  x = y = 0;
  for(i=0; i<n; i++)
    {
      q[i][i] = 0;
      for(j=0; j<i; j++)
        for(k=0; k<i; k++) // staci od k=j+1 testovat
	  if (j != k)
	    {
	      z0 = q[j][k] + d[i][j] + d[i][k];
	      if (z0 < z)
		{
		  z = z0;
		  x = i;
		  y = j;
		}
	    }
      for(j=0; j<i; j++)
	{
          q[i][j] = INF; // Uz je nastaveno !
          for(k=0; k<i; k++)
	    if (q[i][j] > q[j][k] + d[k][i])
	      q[i][j] = q[j][k] + d[k][i];
	  q[j][i] = q[i][j];
	}
      for(j=0; j<i; j++)
	for(k=0; k<i; k++)
	  if (q[j][k] > q[j][i] + q[i][k])
	    q[j][k] = q[j][i] + q[i][k];
    }

  d[x][y] = d[y][x] = INF;

  memcpy(q, d, sizeof(long int)*MAXN*MAXN);
// memcpy(q, d, sizeof(q)); // Tohle snad ne!!
  for(i=0; i<n; i++)
    q[i][i] = 0;
  for(i=0; i<n; i++)
    for(j=0; j<n; j++)
      for(k=0; k<n; k++)
	if (q[j][k] > q[j][i] + q[i][k])
	  q[j][k] = q[j][i] + q[i][k];

  g = fopen("trip.out", "w");
  if (!g)
    return 2;
  if (z == INF)
    fprintf(g, "No solution.\n");
  else
    {
      while (x != y)
	{
	  fprintf(g, "%d ", y+1);
	  for(i=0; i<n; i++)
	    if (q[y][x] == q[i][x] + d[y][i])
	      {
		y = i;
		break;
	      }
	}
      fprintf(g, "%d\n", x+1);
    }
  fclose(g);
  return 0;
}
