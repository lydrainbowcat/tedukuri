#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int cap = 500010;
int dist[510][510]; char map[510][510]; bool proc[510][510];
pair<int, int> queue[cap * 2]; int r, c, li, ri;
inline bool valid (int x, int y) { return x >= 0 && x <= r && y >= 0 && y <= c; }
inline void que_add (int x, int y, int v)
{
    if (dist[x][y] < 0 || v < dist[x][y])
    {
        dist[x][y] = v;
        if (li == ri || v > dist[queue[li].first][queue[li].second]) queue[ri++] = make_pair(x, y);
        else queue[--li] = make_pair(x, y);
    }
}
int main ()
{
    freopen("cir.in", "r", stdin);
    freopen("cir.out", "w", stdout);
    int kase; for (scanf("%d", &kase); kase; --kase)
    {
        scanf("%d %d", &r, &c);
        if ((r + c) % 2)
        {
            for (int i = 0; i < r; i++) scanf("%s", map[i]);
            printf("NO SOLUTION\n");
        }
        else
        {
            for (int i = 0; i < r; i++) scanf("%s", map[i]);
            li = ri = cap; queue[ri++] = make_pair(0, 0);
            memset(dist, -1, sizeof dist), dist[0][0] = 0;
            memset(proc, false, sizeof proc);
            while (li != ri)
            {
                int cx = queue[li].first, cy = queue[li].second; ++li;
                if (valid(cx - 1, cy - 1))
                {
                    if (map[cx - 1][cy - 1] == '\\') que_add(cx - 1, cy - 1, dist[cx][cy]);
                    else que_add(cx - 1, cy - 1, dist[cx][cy] + 1);
                }
                if (valid(cx - 1, cy + 1))
                {
                    if (map[cx - 1][cy] == '/') que_add(cx - 1, cy + 1, dist[cx][cy]);
                    else que_add(cx - 1, cy + 1, dist[cx][cy] + 1);
                }
                if (valid(cx + 1, cy - 1))
                {
                    if (map[cx][cy - 1] == '/') que_add(cx + 1, cy - 1, dist[cx][cy]);
                    else que_add(cx + 1, cy - 1, dist[cx][cy] + 1);
                }
                if (valid(cx + 1, cy + 1))
                {
                    if (map[cx][cy] == '\\') que_add(cx + 1, cy + 1, dist[cx][cy]);
                    else que_add(cx + 1, cy + 1, dist[cx][cy] + 1);
                }
            }
            printf("%d\n", dist[r][c]);
        }
    }
    return 0;
}
