#include <stdio.h>
#define max(a,b) ((a)>(b)?(a):(b))

int chess[24];
int seqans[1100];

int mov[8][7] = {{0, 2, 6, 11, 15, 20, 22},
                 {1, 3, 8, 12, 17, 21, 23},
                 {10, 9, 8, 7, 6, 5, 4},
                 {19, 18, 17, 16, 15, 14, 13},
                 {23, 21, 17, 12, 8, 3, 1},
                 {22, 20, 15, 11, 6, 2, 0},
                 {13, 14, 15, 16, 17, 18, 19},
                 {4, 5, 6, 7, 8, 9, 10}};
int rnd[8] = {6, 7, 8, 12, 17, 16, 15, 11};
int reverse[8] = {5, 4, 7, 6, 1, 0, 3, 2};
int maxdepth;

int hfunc ()
{
    int cnt[3] = {0, 0, 0}, i;
    for (i = 0; i < 8; i++)
        cnt[chess[rnd[i]] - 1]++;
    return 8 - max(cnt[0], max(cnt[1], cnt[2]));
}

void move (int cdr)
{
    int t = chess[mov[cdr][0]], i;
    for (i = 0; i < 6; i++)
        chess[mov[cdr][i]] = chess[mov[cdr][i + 1]];
    chess[mov[cdr][6]] = t;
    return;
}

int dfs (int depth)
{
    int h, i;
    for (i = 0; i < 8; i++)
    {
        seqans[depth] = i;
        move(i);
        h = hfunc();
        if (h == 0) return 1;
        else if (h + depth < maxdepth)
        {
             if (dfs(depth + 1)) return 1;
        }
        move(reverse[i]);
    } return 0;
}

int main ()
{
    int i;
    while (1)
    {
          scanf("%d", &chess[0]);
          if (chess[0] == 0) break;
          for (i = 1; i < 24; i++)
              scanf("%d", &chess[i]);
          if (hfunc() == 0)
             printf("No moves needed\n%d\n", chess[6]);
          else
          {
              maxdepth = hfunc();
              while (dfs(0) == 0) maxdepth++;
              for (i = 0; i < maxdepth; i++)
                  printf("%c", seqans[i] + 65);
              printf("\n%d\n", chess[6]);
          }
    }
    return 0;
}
