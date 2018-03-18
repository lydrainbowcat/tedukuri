#include <cstdio>
#include <cstring>
using namespace std;

typedef long long ll;
const int md = 10000007;
int n, m;
const int N = 13;
struct mat {
    int a[N][N], n, m;
    mat() {
        n = m = 0;
        memset(a, 0, sizeof(a));
    }
};
inline mat operator *(const mat &a, const mat &b) {
    mat res;
    res.n = a.n, res.m = b.m;
    for (int i=0; i<=res.n; ++i)
        for (int j=0; j<=res.m; ++j) {
            int &ans = res.a[i][j];
            ans = 0;
            for (int k=0; k<=a.m; ++k)
                ans = (ans + (ll)a.a[i][k] * b.a[k][j]) % md;
        }
    return res;
}
inline mat pow(mat a, int b) {
    mat res;
    res.n = a.n, res.m = a.m;
    for (int i=0; i<=a.n; ++i)
        res.a[i][i] = 1;
    for (; b; b>>=1) {
        if (b & 1) res = res * a;
        a = a * a;
    }
    return res;
}
mat a, b;
bool run() {
    if (scanf("%d%d", &n, &m) == EOF) return 0;
    a.n = 0, a.m = n+1, a.a[0][0] = 0;
    for (int i=1; i<=n; ++i)
        scanf("%d", &a.a[0][i]), a.a[0][i] %= md;
    if (m) {
        a.a[0][0] = 23;
        a.a[0][n+1] = 3;
        b = mat();
        b.n = b.m = n+1;
        for (int i=0; i<=n; ++i) b.a[0][i] = 10, b.a[n+1][i] = 1;
        for (int i=1; i<=n; ++i)
            for (int j=i; j<=n; ++j)
                b.a[i][j] = 1;
        b.a[n+1][n+1] = 1;
        a = a * pow(b, m);
    }
    printf("%d\n", a.a[0][n]);
    return 1;
}
int main() {
    while (run());
    return 0;
}