#include <stdio.h>

// TYPE 1: start, TYPE -1: end

typedef struct str_a { int place, type, st, ed; } side;
int comp (const void *a, const void *b) { return ((side *)a)->place - ((side *)b)->place; }

side listx[10010], listy[10010];
// Got value by lshx[x + 10010] esp.
int lshx[20020], lshy[20020];
int codex[10010], codey[10010], cxmr, cymr;
int stackx[10010], stacky[10010];

// A horizonal side: place: y, st: x1, ed: x2, x1 and x2 is in lshx, rush stackx.
// A vertical  side: place: x, st: y1, ed: y2, y1 and y2 is in lshy, ruch stacky.

int main ()
{
    int x1, y1, x2, y2, n, i, j, ans;
    memset(lshx, 0, sizeof(lshx));
    memset(lshy, 0, sizeof(lshy));
    memset(stackx, 0, sizeof(stackx));
    memset(stacky, 0, sizeof(stacky));
    cxmr = cymr = ans = 0;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        x1 += 10010, y1 += 10010, x2 += 10010, y2 += 10010;
        lshx[x1] = lshx[x2] = lshy[y1] = lshy[y2] = 1;
        listx[i * 2].place = y1, listx[i * 2].type = 1, listx[i * 2].st = x1, listx[i * 2].ed = x2;
        listx[i * 2 + 1].place = y2, listx[i * 2 + 1].type = -1, listx[i * 2 + 1].st = x1, listx[i * 2 + 1].ed = x2;
        listy[i * 2].place = x1, listy[i * 2].type = 1, listy[i * 2].st = y1, listy[i * 2].ed = y2;
        listy[i * 2 + 1].place = x2, listy[i * 2 + 1].type = -1, listy[i * 2 + 1].st = y1, listy[i * 2 + 1].ed = y2;
    }
    qsort(listx, n * 2, sizeof(listx[0]), comp);
    qsort(listy, n * 2, sizeof(listy[0]), comp);
    for (i = 0; i < 20020; i++)
    {
        if (lshx[i]) { lshx[i] = cxmr; codex[cxmr++] = i; }
        if (lshy[i]) { lshy[i] = cymr; codey[cymr++] = i; }
    }
    for (i = 0; i < n * 2; i++)
    {
        listx[i].st = lshx[listx[i].st];
        listx[i].ed = lshx[listx[i].ed];
        listy[i].st = lshy[listy[i].st];
        listy[i].ed = lshy[listy[i].ed];
    }
    for (i = 0; i < n * 2; i++)
    {
        //printf("SIDEX %d, ST = %d, ED = %d, PLACE = %d, TYPE = %d\n", i, listx[i].st, listx[i].ed, listx[i].place, listx[i].type); 
        for (j = listx[i].st; j < listx[i].ed; j++)
        {
            stackx[j] += listx[i].type;
            if (stackx[j] == 0) ans += codex[j + 1] - codex[j];
        }
    }
    for (i = 0; i < n * 2; i++)
    {
        //printf("SIDEY %d, ST = %d, ED = %d, PLACE = %d, TYPE = %d\n", i, listy[i].st, listy[i].ed, listy[i].place, listy[i].type); 
        for (j = listy[i].st; j < listy[i].ed; j++)
        {
            stacky[j] += listy[i].type;
            if (stacky[j] == 0) ans += codey[j + 1] - codey[j];
        }
    }
    printf("%d\n", ans * 2);
    //system("pause");
    return 0;
}
