// Author: yxc
// https://www.acwing.com/solution/acwing/content/3428/
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

int n;
int g[5][7], bg[5][5][7];
int cnt[11], bcnt[5][11];
bool st[5][7];

struct Move
{
    int x, y, d;
}path[5];

void move(int a, int b, int c)
{
    swap(g[a][b], g[c][b]);

    while (true)
    {
        bool flag = false;

        for (int x = 0; x < 5; x++)
        {
            int z = 0;
            for (int y = 0; y < 7; y++)
                if (g[x][y])
                    g[x][z++] = g[x][y];
            while (z < 7) g[x][z++] = 0;
        }

        memset(st, false, sizeof st);
        for (int x = 0; x < 5; x ++ )
            for (int y = 0; y < 7; y ++ )
                if (g[x][y])
                {
                    int l = x, r = x;
                    while (l - 1 >= 0 && g[l - 1][y] == g[x][y]) l--;
                    while (r + 1 < 5 && g[r + 1][y] == g[x][y]) r++;

                    if (r - l + 1 >= 3)
                    {
                        flag = true;
                        st[x][y] = true;
                    }
                    else
                    {
                        l = r = y;
                        while (l - 1 >= 0 && g[x][l - 1] == g[x][y]) l--;
                        while (r + 1 < 7 && g[x][r + 1] == g[x][y]) r++;

                        if (r - l + 1 >= 3)
                        {
                            flag = true;
                            st[x][y] = true;
                        }
                    }
                }

        if (flag)
        {
            for (int x = 0; x < 5; x ++ )
                for (int y = 0; y < 7; y ++ )
                    if (st[x][y])
                    {
                        cnt[0] --;
                        cnt[g[x][y]] --;
                        g[x][y] = 0;
                    }
        }
        else break;
    }
}

bool dfs(int u)
{
    if (u == n) return !cnt[0];

    for (int i = 1; i <= 10; i++)
        if (cnt[i] == 1 || cnt[i] == 2)
            return false;

    memcpy(bg[u], g, sizeof g);
    memcpy(bcnt[u], cnt, sizeof cnt);
    for (int x = 0; x < 5; x ++ )
        for (int y = 0; y < 7; y ++ )
            if (g[x][y])
            {
                int nx = x + 1;
                if (nx < 5)
                {
                    path[u] = { x, y, 1 };
                    move(x, y, nx);
                    if (dfs(u + 1)) return true;
                    memcpy(g, bg[u], sizeof g);
                    memcpy(cnt, bcnt[u], sizeof cnt);
                }
                nx = x - 1;
                if (nx >= 0 && !g[nx][y])
                {
                    path[u] = { x, y, -1 };
                    move(x, y, nx);
                    if (dfs(u + 1)) return true;
                    memcpy(g, bg[u], sizeof g);
                    memcpy(cnt, bcnt[u], sizeof cnt);
                }
            }

    return false;
}

int main()
{
    cin >> n;
    for (int i = 0; i < 5; i++)
    {
        int j = 0, y;
        while (cin >> y, y)
        {
            cnt[0] ++;
            cnt[y] ++;
            g[i][j++] = y;
        }
    }

    if (dfs(0))
    {
        for (int i = 0; i < n; i++) printf("%d %d %d\n", path[i].x, path[i].y, path[i].d);
    }
    else puts("-1");

    return 0;
}
