#include <stdio.h>
#define MAX 19931117
#define min(a,b) ((a)<(b)?(a):(b))

int n, b;
int rank[1100][55], mat[55][1100], limit[55];
char sch[55]; 

int match (int cow, int start, int end)
{
    int i, j, cur;
    for (i = start; i <= end; i++)
    {
        cur = rank[cow][i];
        if (sch[cur]) continue;
        sch[cur] = 1;
        if (mat[cur][0] < limit[cur])
        {
            mat[cur][++mat[cur][0]] = cow;
            return 1;
        }
        else
        {
            for (j = 1; j <= mat[cur][0]; j++)
            {
                if (match(mat[cur][j], start, end))
                {
                    mat[cur][j] = cow;
                    return 1;
                }
            }
        }
    } return 0;
}

int vali (int start, int end)
{
    int i, st;
    for (i = 0; i < b; i++) mat[i][0] = 0;
    for (i = 0; i < n; i++)
    {
        memset(sch, 0, sizeof(sch));
        if (match(i, start, end) == 0) return 0;
    } return 1;
}

int main ()
{
    int i, j, st, ed, ans = MAX;
    scanf("%d %d", &n, &b);
    st = 0, ed = 0;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < b; j++)
        {
            scanf("%d", &rank[i][j]);
            rank[i][j]--;
        }
    }
    for (i = 0; i < b; i++)
        scanf("%d", &limit[i]);
    while (1)
    {
        if (vali(st, ed))
        {
            ans = min(ans, ed - st + 1);
            if (ans == 1) break;
            else st++;
        }
        else ed++;
        if (ed == b) break;
    }
    printf("%d\n", ans);
    return 0;
}
