#include <stdio.h>
#define MAX 0x7FFFFFFE

int device[51], type[51], mr, ans;
int missile[51], n;

void search (int id)
{
    int i, t, m, r, pl, flag;
    if (mr >= ans) return;
    if (id >= n) { ans = mr; return; }
    flag = 0; m = -MAX;
    for (i = 0; i < mr; i++)
    {
        if (device[i] < missile[id] && type[i] == 0)
        {
            if (device[i] > m)
            {
                m = device[i];
                t = i;
                flag |= 1;
            }
        }
    }
    if (flag & 1)
    {
        r = device[t];
        device[t] = missile[id];
        search(id + 1);
        device[t] = r;
    }
    m = MAX;
    for (i = 0; i < mr; i++)
    {
        if (device[i] > missile[id] && type[i] == 1)
        {
            if (device[i] < m)
            {
                m = device[i];
                t = i;
                flag |= 2;
            }
        }
    }
    if (flag & 2)
    {
        r = device[t];
        device[t] = missile[id];
        search(id + 1);
        device[t] = r;
    }
    
    pl = mr++;
    device[pl] = missile[id];
    if ((flag & 1) == 0) { type[pl] = 0; search(id + 1); }
    if ((flag & 2) == 0) { type[pl] = 1; search(id + 1); }
    mr--; return;
}

int main ()
{
    int i;
    while (1)
    {
        scanf("%d", &n);
        if (n == 0) break;
        mr = 0, ans = MAX;
        for (i = 0; i < n; i++) scanf("%d", &missile[i]);
        search(0);
        printf("%d\n", ans);
    }
    return 0;
}
