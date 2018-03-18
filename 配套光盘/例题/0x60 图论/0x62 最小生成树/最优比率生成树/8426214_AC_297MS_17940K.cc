// Dinkelbachµü´ú·¨
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

double dist[1100][1100], cost[1100][1100];
double ratio, dsum, csum; int n;
inline double len (int a, int b) { return cost[a][b] - ratio * dist[a][b]; }
void prim (void)
{
    double dt[1100], ds[1100], dc[1100];
    bool added[1100];
    for (int i = 1; i < n; i++)
    {
        dt[i] = len(0, i);
        ds[i] = dist[0][i], dc[i] = cost[0][i];
    }
    memset(added, 0, sizeof(added));
    added[0] = true;
    dsum = csum = 0;
    for (int i = 1; i < n; i++)
    {
        int t = -1;
        for (int j = 1; j < n; j++)
        {
            if (added[j]) continue;
            if (t == -1 || dt[j] < dt[t]) t = j;
        }
        dsum += ds[t], csum += dc[t];
        added[t] = true;
        for (int j = 1; j < n; j++)
        {
            if (added[j]) continue;
            if (len(t, j) < dt[j])
            {
                dt[j] = len(t, j);
                ds[j] = dist[t][j], dc[j] = cost[t][j];
            }
        }
    }
}

int x[1100], y[1100], h[1100];
int main ()
{
    while (1)
    {
        scanf("%d", &n);
        if (n == 0) break;
        for (int i = 0; i < n; i++) scanf("%d %d %d", &x[i], &y[i], &h[i]);
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                dist[i][j] = sqrt((double)(x[i] - x[j]) * (x[i] - x[j]) +
                                  (double)(y[i] - y[j]) * (y[i] - y[j]));
                dist[j][i] = dist[i][j];
                cost[i][j] = abs(h[i] - h[j]);
                cost[j][i] = cost[i][j];
            }
        }
        dsum = csum = 0;
        for (int i = 1; i < n; i++) dsum += dist[0][i], csum += cost[0][i];
        ratio = csum / dsum;
        while (1)
        {
            prim(); double tr = csum / dsum;
            if (fabs(tr - ratio) < 1e-04) break;
            else ratio = tr;
        }
        printf("%.3f\n", ratio);
    }
    return 0;
}
