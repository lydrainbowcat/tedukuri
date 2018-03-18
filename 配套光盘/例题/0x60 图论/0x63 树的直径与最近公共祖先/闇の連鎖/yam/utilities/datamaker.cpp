#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <time.h>
using namespace std;

int pere[100010], iro[100010];
inline int random (void) { return (rand() << 15) | rand(); }

int main ()
{
    srand(time(0));
    int n = 100000, m = 200000;
    freopen("yam9.in", "w", stdout);
    FILE *logg = fopen("log.txt", "w");
    printf("%d %d\n", n, m);
    for (int i = 2; i <= n; i++)
    {
        int x = random() % (i - 1) + 1;
        pere[i] = x; printf("%d %d\n", x, i);
    }
    memset(iro, 0, sizeof iro);
    iro[1] = 1;
    int r1 = 0, r2 = 0;
    for (int i = 2; i <= n; i++)
    {
        iro[i] = iro[pere[i]];
        int c = random() % 100000;
        if (c == 0) iro[i] = i, ++r1;
        else if (c <= 50 && m)
        {
            int x, cnt = 0;
            do
            {
                x = random() % (i - 1) + 1;
                ++cnt;
            } while (cnt < 1000 && iro[x] != iro[i]); 
            if (iro[x] == iro[i])
            {
                printf("%d %d\n", x, i);
                iro[i] = i, ++r2; --m;
            }
        }
    }
    for (int i = 0; i < m; i++)
    {
        int a, b;
        do
        {
            a = random() % n + 1;
            int c = rand() % 1000;
            if (c == 0) b = a;
            else b = random() % n + 1;
        } while (iro[a] != iro[b]);
        printf("%d %d\n", a, b);
    }
    fprintf(logg, "%d %d\n", r1, r2);
    fclose(logg);
    fclose(stdin);
    return 0;
}
