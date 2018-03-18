#include <stdio.h>
#define max(a,b) ((a)>(b)?(a):(b))

int chain[110], red[110], amount[110];
int n, color[110], side[110][110], opp[110][110];
int mr = 1, list[110], isinv[110], invert[110][110], dyna[110][110];

int getanc (int a)
{
    if (chain[a] == a) return a;
    else return chain[a] = getanc(chain[a]);
}
int chnanc (int a, int b) { chain[getanc(a)] = getanc(b); }

int team (int x, int col)
{
    int i;
    if (color[x] == 1 - col) return 0;
    else if (color[x] == col) return 1;
    else
    {
        color[x] = col;
        for (i = 1; i <= n; i++)
            if (opp[i][x] == 1) if (team(i, 1 - col) == 0) return 0;
    }
}

int main ()
{
    int i, j, k, flag, blue, anc, tmr, tcon, tred;
    memset(red, 0, sizeof(red));
    memset(amount, 0, sizeof(amount));
    memset(color, 0x7FFFFFFF, sizeof(color));
    memset(side, 0, sizeof(side));
    scanf("%d", &n);
    for (i = 1; i <= n; i++)
    {
        while (1)
        {
              scanf("%d", &j);
              if (j == 0) break;
              else side[i][j] = 1;
        }
    }
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= i; j++)
        {
            if (i == j) opp[i][j] = opp[j][i] = 0;
            else
            {
                if (side[i][j] && side[j][i]) opp[i][j] = opp[j][i] = 0;
                else opp[i][j] = opp[j][i] = 1;
            }
        }
    }  
    for (i = 1; i <= n; i++)
    {
        if (color[i] == -1) flag = team(i, 0);
        if (flag == 0) break;
    }
    if (flag)
    {
       for (i = 1; i <= n; i++) chain[i] = i;
       for (i = 1; i <= n; i++)
       {
           for (j = 1; j <= i; j++)
               if (opp[i][j]) chnanc(i, j);
       }
       for (i = 1; i <= n; i++)
       {
           anc = getanc(i);
           if (amount[anc] == 0) list[mr++] = anc;
           amount[anc]++;
           if (color[i] == 0) red[anc]++;
       }
       memset(dyna, 0, sizeof(dyna));
       dyna[0][0] = 1;
       for (i = 1; i < mr; i++)
       {
           for (j = 0; j <= n / 2; j++)
           {
               dyna[i][j] = 0;
               blue = amount[list[i]] - red[list[i]];
               if (j - red[list[i]] >= 0)
               {
                     if (dyna[i - 1][j - red[list[i]]]) dyna[i][j] = 1;
                     invert[i][j] = 0;
               }
               if (j - blue >= 0 && dyna[i][j] == 0)
               {
                     if (dyna[i - 1][j - blue]) dyna[i][j] = 1;
                     invert[i][j] = 1;
               }
           }
       }
       tmr = mr - 1; tred = 0;
       for (j = (int)(n / 2); j >= 1; j--)
       {
           if (dyna[mr - 1][j])
           {
              tred = j, tcon = j;
              break;
           }
       }
       while (tmr > 0)
       {
             isinv[list[tmr]] = invert[tmr][tcon];
             if (invert[tmr][tcon]) tcon -= (amount[list[tmr]] - red[list[tmr]]);
             else tcon -= red[list[tmr]];
             tmr--;
       }
       for (i = 1; i <= n; i++)
           if (isinv[getanc(i)]) color[i] = 1 - color[i];
       printf("%d", tred);
       for (i = 1; i <= n; i++)
           if (color[i] == 0) printf(" %d", i);
       printf("\n%d", n - tred);
       for (i = 1; i <= n; i++)
           if (color[i] == 1) printf(" %d", i);
       printf("\n");
    }
    else printf("No solution\n");
    //system("pause");
    return 0;
}

