#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

inline int random (void)
{
    return (rand() << 15) | rand();
}

int main ()
{
    FILE *fp = fopen("mystery.in", "w");
    srand(7777);
    int sr = 20000, range = 2140000000, kase = 3000;
    for (; kase; --kase)
    {
        int s = random() % sr + 1;
        int d = random() % range + 400;
        fprintf(fp, "%d %d\n", s, d);
    }
    fclose(fp);
    return 0;
}
