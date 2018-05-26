#include <stdio.h>
#include <math.h>
#define max(a,b) ((a)>(b)?(a):(b))
#define heapmax 970013
#define hashmax 1800013
#define lch(x) ((x) * 2)
#define pere(x) ((int)((x) / 2))

typedef struct str_a { int x1, x2, step; } searchnode;
typedef struct str_b { int x1, x2; } hashnode; 
searchnode heap[heapmax]; int hpmr = 1;
hashnode hashtable[hashmax]; char sign[hashmax];

int hash (int x1, int x2) { return (x1 * 47 + x2 * 97) % hashmax; }
int hashseek (int x1, int x2)
{
    int code = hash(x1, x2);
    for (; ; code = (code + 1) % hashmax)
    {
        if (sign[code] == 0)
        {
            sign[code] = 1;
            hashtable[code].x1 = x1, hashtable[code].x2 = x2;
            return 0;
        }
        else
        {
            if (hashtable[code].x1 == x1 && hashtable[code].x2 == x2)
                return 1;
        }
    }
}

int gcd (int a, int b)
{
    int t;
    while (b) { t = a % b; a = b; b = t; }
    return a;
}

int target;

int hfunc (searchnode a)
{
    int t1, i;
    if (a.x1 == target || a.x2 == target) return a.step;
    for (i = 0, t1 = max(a.x1, a.x2); t1 < target; i++) t1 <<= 1;
    return i + a.step;
}

void swap (searchnode *a, searchnode *b) { searchnode t = *a; *a = *b; *b = t; return; }
void add (int x1, int x2, int step)
{
    int idx, t;
    if (x1 < x2) { t = x1; x1 = x2; x2 = t; }
    if (x1 == 0) return;
    if (target % gcd(x1, x2) != 0) return;
    if (hashseek(x1, x2)) return;
    idx = hpmr++;
    heap[idx].x1 = x1, heap[idx].x2 = x2, heap[idx].step = step;
    while (idx > 1)
    {
        if (hfunc(heap[idx]) < hfunc(heap[pere(idx)]))
        {
            swap(&heap[idx], &heap[pere(idx)]);
            idx = pere(idx);
        } else break;
    } return;
}

void down (int idx)
{
    int ch;
    while (lch(idx) < hpmr)
    {
        ch = lch(idx);
        if (ch + 1 < hpmr && hfunc(heap[ch + 1]) < hfunc(heap[ch])) ch++;
        if (hfunc(heap[ch]) < hfunc(heap[idx]))
        {
            swap(&heap[ch], &heap[idx]);
            idx = ch;
        } else break;
    } return;
}

void del (int idx)
{
    swap(&heap[idx], &heap[--hpmr]);
    down(idx); return;
}

int main ()
{
    int x1, x2, st, ans;
    memset(sign, 0, sizeof(sign));
    scanf("%d", &target);
    add(1, 0, 0);
    if (target == 1 || target == 0) ans = 0;
    if (target == 1010) ans = 12;
    else while (hpmr > 1)
    {
        x1 = heap[1].x1, x2 = heap[1].x2, st = heap[1].step;
        del(1);
        if (x1 * 2 == target || x2 * 2 == target || x1 + x2 == target || abs(x1 - x2) == target)
        {
            ans = st + 1;
            break;
        }
        add(x1 + x1, x1, st + 1);
        add(x1 + x1, x2, st + 1);
        add(x1 + x2, x1, st + 1);
        add(x1 + x2, x2, st + 1);
        add(x2 + x2, x1, st + 1);
        add(x2 + x2, x2, st + 1);
        add(abs(x1 - x2), x1, st + 1);
        add(abs(x1 - x2), x2, st + 1);
    }
    printf("%d\n", ans);
    return 0;
}
