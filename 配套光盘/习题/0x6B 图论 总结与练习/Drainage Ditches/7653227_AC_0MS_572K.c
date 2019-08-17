#include <stdio.h>
#define MAX 0x7FFFFFFF
#define min(a,b) ((a)<(b)?(a):(b))

int matrix[210][210];
int queue[1010], now, add;
char sch[210]; int pere[210];

int main ()
{
    int m, n, a, b, l, i, ans, cur, naga;
    while (scanf("%d %d", &n, &m) == 2) {
    memset(matrix, 0, sizeof(matrix));
    ans = 0;
    for (i = 0; i < n; i++)
    {
        scanf("%d %d %d", &a, &b, &l);
        a--, b--;
        matrix[a][b] += l;
    }
    while (1)
    {
        now = add = 0;
        memset(sch, 0, sizeof(sch));
        memset(pere, 0, sizeof(pere));
        queue[add++] = 0; sch[0] = 1;
        while (now != add)
        {
            cur = queue[now++];
            for (i = 0; i < m; i++)
            {
                if (matrix[cur][i] && sch[i] == 0)
                {
                    sch[i] = 1;
                    queue[add++] = i;
                    pere[i] = cur;
                    if (i == m - 1) goto outerloop;
                }
            }
        } outerloop:
        if (sch[m - 1] == 0) break;
        naga = MAX;
        for (i = m - 1; i != 0; i = pere[i])
            naga = min(naga, matrix[pere[i]][i]);
        ans += naga;
        for (i = m - 1; i != 0; i = pere[i])
        {
            matrix[pere[i]][i] -= naga;
            matrix[i][pere[i]] += naga;
        }
    }
    printf("%d\n", ans); }
    return 0;
}
