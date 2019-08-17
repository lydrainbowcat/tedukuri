#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <time.h>
using namespace std;

inline int random (void)
{
    int res = 0;
    for (int i = 0; i < 4; i++) res = ((res << 8) | (rand() & 0x00000FF));
    return res;
}
int main ()
{
    srand(time(0));
    freopen("exa9.in", "w", stdout);
    int mx = 1000000001, kase = 100;
    for (int i = 0; i < kase; i++)
    {
        int x = random() % mx;
        int y = random() % mx;
        int c = rand() % 3; char t;
        switch (c)
        {
            case 0: t = 'U'; break;
            case 1: t = 'V'; break;
            default: t = 'H'; break;
        }
        printf("%c %d %d\n", t, x, y);
    }
    fclose(stdout);
    return 0;
}
