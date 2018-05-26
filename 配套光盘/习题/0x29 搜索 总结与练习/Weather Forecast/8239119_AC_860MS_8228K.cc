#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

bool dyna[9][370][7][7][7][7];
bool festival[370][16];

int dx[9] = {0, 1, -1, 0, 0, 2, -2, 0, 0};
int dy[9] = {0, 0, 0, 1, -1, 0, 0, 2, -2};

inline bool fes (int day, int x, int y) { return festival[day][x * 4 + y]; }
bool shift (int cloud, int day, int lt, int lb, int rt, int rb)
{
    int rx, ry, kx, ky, tlt, tlb, trt, trb;
    bool ans = false;
    if (dyna[cloud][day][lt][lb][rt][rb] == false) return false;
    rx = cloud / 3;
    ry = cloud % 3;
    for (int i = 0; i < 9; i++)
    {
        kx = rx + dx[i];
        ky = ry + dy[i];
        if (kx < 0 || kx > 2 || ky < 0 || ky > 2) continue;
        if (fes(day + 1, kx, ky) || 
            fes(day + 1, kx + 1, ky) ||
            fes(day + 1, kx, ky + 1) || 
            fes(day + 1, kx + 1, ky + 1)) continue;
        tlt = lt + 1, tlb = lb + 1, trt = rt + 1, trb = rb + 1;
        if (kx == 0 && ky == 0) tlt = 0;
        else if (kx == 0 && ky == 2) trt = 0;
        else if (kx == 2 && ky == 0) tlb = 0;
        else if (kx == 2 && ky == 2) trb = 0;
        if (tlt > 6 || trt > 6 || tlb > 6 || trb > 6) continue;
        dyna[kx * 3 + ky][day + 1][tlt][tlb][trt][trb] = true;
        ans = true;
    } return ans;
}

int main ()
{
    int n, i, j, a, cloud, lt, lb, rt, rb;
    bool rec, ans;
    while (1)
    {
        scanf("%d", &n);
        ans = true;
        if (n == 0) break;
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < 16; j++)
            {
                scanf("%d", &a);
                festival[i][j] = (a == 1);
            }
        }
        if (fes(0, 1, 1) || fes(0, 2, 1) || fes(0, 1, 2) || fes(0, 2, 2)) ans = false;
        else
        {
            memset(dyna, 0, sizeof(dyna));
            dyna[4][0][1][1][1][1] = true;
            for (i = 0; i < n - 1; i++)
            {
                rec = false;
                for (cloud = 0; cloud < 9; cloud++)
                {
                    for (lt = 0; lt < 7; lt++)
                    {
                        for (lb = 0; lb < 7; lb++)
                        {
                            for (rt = 0; rt < 7; rt++)
                            {
                                for (rb = 0; rb < 7; rb++)
                                {
                                    if (shift(cloud, i, lt, lb, rt, rb))
                                        rec = true;
                                }
                            }
                        }
                    }
                }
                if (rec == false)
                {
                    ans = false;
                    break;
                }
            }
        }
        if (ans) printf("1\n");
        else printf("0\n");
    }
    return 0;
}
