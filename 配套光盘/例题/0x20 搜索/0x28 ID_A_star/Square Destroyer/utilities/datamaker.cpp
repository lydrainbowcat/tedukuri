#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <time.h>
using namespace std;

bool sele[110];

int main ()
{
    srand(time(0));
    freopen("mag9.in", "w", stdout);
    int n = 5, m = 20, kase = 10;
    int mx = 2 * n * (n + 1);
    printf("%d\n", kase);
    for (int i = 0; i < kase; i++)
    {
        printf("%d\n", n);
        int mc = rand() % m;
        memset(sele, 0, sizeof sele);
        for (int j = 0; j < mc; j++) sele[rand() % mx + 1] = true;
        mc = 0; for (int j = 1; j <= mx; j++) if (sele[j]) ++mc;
        printf("%d", mc);
        for (int j = 1; j <= mx; j++) if (sele[j]) printf(" %d", j);
        printf("\n");
    }
    fclose(stdout);
    return 0;
}
