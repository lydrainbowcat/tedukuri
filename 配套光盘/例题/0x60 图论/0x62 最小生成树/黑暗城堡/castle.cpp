#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const __int64 mod = (1LL << 31) - 1;
const int mi = 199311170;
int mat[1010][1010], n; int dist[1010]; bool sign[1010];
void ginit (void)
{
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) mat[i][j] = mi;
    for (int i = 0; i < n; i++) mat[i][i] = 0;
}
void glink (int a, int b, int l)
{
    mat[a][b] = mat[b][a] = min(mat[a][b], l);
}
void dijkstra (void)
{
    for (int i = 0; i < n; i++) dist[i] = mi, sign[i] = false;
    dist[0] = 0;
    for (int i = 0; i < n; i++)
    {
        int cur = -1;
        for (int j = 0; j < n; j++) 
        {
            if (!sign[j])
            {
                if (cur == -1 || dist[j] < dist[cur]) cur = j;
            }
        }
        sign[cur] = true;
        for (int j = 0; j < n; j++)
        {
            if (!sign[j])
            {
                if (dist[j] > dist[cur] + mat[cur][j]) dist[j] = dist[cur] + mat[cur][j];
            }
        }
    }
}
int list[1010]; __int64 ans = 1;
bool comp (const int& a, const int& b)
{
    return dist[a] < dist[b];
}
int main ()
{
    freopen("castle.in", "r", stdin);
    freopen("castle.out", "w", stdout);
    int m; scanf("%d %d", &n, &m);
    ginit();
    for (int i = 0; i < m; i++)
    {
        int x, y, l; scanf("%d %d %d", &x, &y, &l);
        glink(x - 1, y - 1, l);
    }
    dijkstra();
    for (int i = 0; i < n; i++) list[i] = i;
    sort(list, list + n, comp);
    for (int i = 1; i < n; i++)
    {
        int tt = 0;
        for (int j = 0; j < i; j++)
        {
            if (dist[list[j]] + mat[list[j]][list[i]] == dist[list[i]]) ++tt;
        }
        ans = (ans * tt) % mod;
    }
    printf("%I64d\n", ans);
    fclose(stdin);
    fclose(stdout);
    return 0;
}
