#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

FILE *fp;

int count;
inline int cc (int s, int e, int d)
{
    return (e - s) / d + 1;
}

void qinteng (int s, int e, int d, int v)
{
    fprintf(fp, "%d %d %d\n", s, e, d);
    count += cc(s, e, d);
    int ud = d * v;
    for (int i = 0; i < v; i++)
        fprintf(fp, "%d %d %d\n", s + i * d, e, ud), count += cc(s + i * d, e, ud);
}
inline int random (int m)
{
    return ((rand() << 15) | rand()) % m;
}
int main ()
{
    fp = fopen("defender.in", "w");
    srand(7777);
    int t = 1; fprintf(fp, "%d\n", t);
    for (int kase = 0; kase < t; kase++)
    {
        int n = 200000, per = 2000, sr = 10, range = 10, s, d, tt, tv;
        fprintf(fp, "%d\n", n);
        count = 0;
        while (n >= 3)
        {
            s = random(sr);
            d = random(range) + 2;
            tt = random(per) + 20;
            tv = rand() % 7 + 2;
            if (n - (tv + 1) <= 1) tv = n - 3;
            if (tv == 0) tv = 1;
            qinteng(s, s + (tt - 1) * d, d, tv);
            n -= (tv + 1);
        }
        if (n == 2)
        {
            d = random(range) + 2;
            tt = random(per) + 20;
            fprintf(fp, "%d %d %d\n", s, s + (tt - 1) * d, d), count += cc(s, s + (tt - 1) * d, d);
            fprintf(fp, "%d %d %d\n", s + d, s + (tt - 1) * d, d), count += cc(s + d, s + (tt - 1) * d, d);
        }
        else if (n == 1)
        {
            fprintf(fp, "%d %d %d\n", s, s + d - 1, d), count += 1;
        }
        else printf("人品不济！\n"); 
        printf("CASE %d: %d\n", kase + 1, count);
    }
    system("pause");
    return 0;
}
