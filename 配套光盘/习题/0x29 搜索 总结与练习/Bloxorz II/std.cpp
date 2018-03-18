#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

const int QR = 500100;
const int stand = 0;
const int hori = 1;
const int verti = 2;

typedef struct str_a { int x, y, sta; } situ;

// uses as turn[x + 100][y + 100][0].
int turn[220][220][3];
situ queue[QR]; int add = 0, now = 0;
char sch[220][220][3];

int sdx[4] = {0, 0, -2, 1};
int sdy[4] = {2, -1, 0, 0};
int sds[4] = {verti, verti, hori, hori};

int hdx[4] = {0, 0, -1, 2};
int hdy[4] = {1, -1, 0, 0};
int hds[4] = {hori, hori, stand, stand};

int vdx[4] = {-1, 1, 0, 0};
int vdy[4] = {0, 0, 1, -2};
int vds[4] = {verti, verti, stand, stand};

int cal (int x, int y)
{
    int ans, dx, dy;
    if (x > 50) dx = (int)((x - 48) / 3);
    else if (x < -50) dx = -(int)((-48 - x) / 3);
    else dx = 0;
    if (y > 50) dy = (int)((y - 48) / 3);
    else if (y < -50) dy = -(int)((-48 - y) / 3);
    else dy = 0;
    x -= dx * 3; y -= dy * 3;
    return 2 * abs(dx) + 2 * abs(dy) + turn[x + 100][y + 100][0];
}

int main ()
{
    freopen("exa9.in", "r", stdin);
    freopen("exa9.out", "w", stdout);
    int curx, cury, curs, tarx, tary, tars, i, j, s, x, y, ans; char ar[5];
    memset(sch, 0, sizeof(sch));
    queue[add].x = 100, queue[add].y = 100, queue[add].sta = stand; add++;
    turn[100][100][stand] = 0;
    sch[100][100][stand] = 1;
    while (add != now)
    {
          curx = queue[now % QR].x;
          cury = queue[now % QR].y;
          curs = queue[now % QR].sta; now++;
          if (curs == stand)
          {
             for (i = 0; i < 4; i++)
             {
                 tarx = curx + sdx[i], tary = cury + sdy[i], tars = sds[i];
                 if ((tarx >= 0 && tarx <= 200 && tary >= 0 && tary <= 200) &&
                     (sch[tarx][tary][tars] == 0 || turn[tarx][tary][tars] > turn[curx][cury][curs] + 1))
                 {
                    turn[tarx][tary][tars] = turn[curx][cury][curs] + 1;
                    queue[add % QR].x = tarx, queue[add % QR].y = tary, queue[add % QR].sta = tars;
                    sch[tarx][tary][tars] = 1;
                    add++;
                 }
             }
          }
          else if (curs == verti)
          {
             for (i = 0; i < 4; i++)
             {
                 tarx = curx + vdx[i], tary = cury + vdy[i], tars = vds[i];
                 if ((tarx >= 0 && tarx <= 200 && tary >= 0 && tary <= 200) &&
                     (sch[tarx][tary][tars] == 0 || turn[tarx][tary][tars] > turn[curx][cury][curs] + 1))
                 {
                    turn[tarx][tary][tars] = turn[curx][cury][curs] + 1;
                    queue[add % QR].x = tarx, queue[add % QR].y = tary, queue[add % QR].sta = tars;
                    sch[tarx][tary][tars] = 1;
                    add++;
                 }
             }
          }
          else if (curs == hori)
          {
             for (i = 0; i < 4; i++)
             {
                 tarx = curx + hdx[i], tary = cury + hdy[i], tars = hds[i];
                 if ((tarx >= 0 && tarx <= 200 && tary >= 0 && tary <= 200) &&
                     (sch[tarx][tary][tars] == 0 || turn[tarx][tary][tars] > turn[curx][cury][curs] + 1))
                 {
                    turn[tarx][tary][tars] = turn[curx][cury][curs] + 1;
                    queue[add % QR].x = tarx, queue[add % QR].y = tary, queue[add % QR].sta = tars;
                    sch[tarx][tary][tars] = 1;
                    add++;
                 }
             }
          }
    }
    while (scanf("%s %d %d", ar, &x, &y) == 3)
    {
          if (ar[0] == 'U')
             printf("%d\n", cal(x, y));
          else if (ar[0] == 'H')
          {
              ans = cal(x - 2, y - 1) + 3;
              for (i = -1; i <= 2; i++)
                  ans = min(ans, cal(x + i, y - 1) + abs(i) + 1);
              for (i = -2; i <= 2; i++)
                  ans = min(ans, cal(x + i, y + 2) + abs(i) + 1);
              printf("%d\n", ans);
          }
          else
          {
              ans = cal(x - 1, y - 2) + 3;
              for (i = -1; i <= 2; i++)
                  ans = min(ans, cal(x - 1, y + i) + abs(i) + 1);
              for (i = -2; i <= 2; i++)
                  ans = min(ans, cal(x + 2, y + i) + abs(i) + 1);
              printf("%d\n", ans);
          }
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}
