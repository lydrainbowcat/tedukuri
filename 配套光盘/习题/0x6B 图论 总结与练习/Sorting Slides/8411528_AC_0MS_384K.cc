#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

struct slide { int xmin, xmax, ymin, ymax; };
struct plc { int x, y; };
inline bool valid (slide s, plc p)
{
    return s.xmin < p.x && p.x < s.xmax && s.ymin < p.y && p.y < s.ymax;
}
slide sa[1010]; plc pa[1010];
int oku[1010], shujin[1010], n; bool sch[1010];
bool match (int s)
{
    for (int i = 0; i < n; i++)
    {
        if (sch[i]) continue;
        if (valid(sa[s], pa[i]))
        {
            sch[i] = true;
            if (shujin[i] == -1 || match(shujin[i]))
            {
                shujin[i] = s;
                oku[s] = i;
                return true;
            }
        }
    } return false;
}
bool deter (int s, int forbid)
{
    for (int i = 0; i < n; i++)
    {
        if (i == forbid || sch[i]) continue;
        if (valid(sa[s], pa[i]))
        {
            sch[i] = true;
            if (shujin[i] == -1 || deter(shujin[i], -1)) return true;
        }
    } return false;
}

int main ()
{
    bool displayed; int k = 0;
    while (1)
    {
        scanf("%d", &n); ++k;
        if (n == 0) break;
        for (int i = 0; i < n; i++) scanf("%d %d %d %d", &sa[i].xmin, &sa[i].xmax, &sa[i].ymin, &sa[i].ymax);
        for (int i = 0; i < n; i++) scanf("%d %d", &pa[i].x, &pa[i].y);
        memset(oku, -1, sizeof(oku)), memset(shujin, -1, sizeof(shujin)), displayed = false;
        for (int i = 0; i < n; i++)
        {
            memset(sch, 0, sizeof(sch));
            match(i);
        }
        printf("Heap %d\n", k);
        for (int i = 0; i < n; i++) if (oku[i] != -1)
        {
            memset(sch, 0, sizeof(sch));
            shujin[oku[i]] = -1;
            if (deter(i, oku[i]) == false) printf("(%c,%d) ", 'A' + i, oku[i] + 1), displayed = true;
            shujin[oku[i]] = i;
        }
        if (displayed == false) printf("none\n\n");
        else printf("\n\n");
    }
    return 0;
}
