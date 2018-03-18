#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

const int mod = 1000000000;
char serial[310];
int dyna[310][310];

int main ()
{
    freopen("pyr.in", "r", stdin);
    freopen("pyr.out", "w", stdout);
    scanf("%s", serial);
    int mlen = strlen(serial);
    for (int i = 0; i < mlen; i++) dyna[i][i] = 1;
    for (int len = 1; len < mlen; len++)
    {
        for (int i = 0; i + len < mlen; i++)
        {
            int j = i + len;
            dyna[i][j] = 0;
            if (serial[i] == serial[j] && ((j - i + 1) & 1))
            {
                dyna[i][j] = dyna[i + 1][j - 1];
                for (int k = i + 2; k < j; k++)
                {
                    if (serial[k] == serial[i])
                    {
                        dyna[i][j] =
                            (dyna[i][j] + (__int64)dyna[i + 1][k - 1] * dyna[k][j]) % mod;
                    }
                }
            }
        }
    }
    printf("%d\n", dyna[0][mlen - 1]);
    fclose(stdin);
    fclose(stdout);
    return 0;
}
