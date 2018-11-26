//Author:XuHt
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int MAX = 10006, N = 506;
int xx[MAX], yy[MAX];
int c, n, tx = 0, ty = 0;
int x[N], y[N], s[N][N];
struct P {
    int x, y;
} p[N];

bool pd(int k) {
    for (int i = xx[k]; i <= tx; i++)
        for (int j = yy[k]; j <= ty; j++) {
            int x0 = 0, y0 = 0;
            if (x[i]-k >= 0) x0 = xx[x[i]-k];
            if (y[j]-k >= 0) y0 = yy[y[j]-k];
            if (s[i][j] - s[x0][j] - s[i][y0] + s[x0][y0] >= c) return 1;
        }
    return 0;
}

int main() {
    memset(xx, 0, sizeof(xx));
    memset(yy, 0, sizeof(yy));
    memset(s, 0, sizeof(s));
    cin >> c >> n;
    for (int i = 1; i <= n; i++) {
        cin >> p[i].x >> p[i].y;
        xx[p[i].x]++;
        yy[p[i].y]++;
    }
    for (int i = 1; i <= 10000; i++) {
        if (xx[i]) x[++tx] = i;
        xx[i] = tx;
        if (yy[i]) y[++ty] = i;
        yy[i] = ty;
    }
    for (int i = 1; i <= n; i++) s[xx[p[i].x]][yy[p[i].y]]++;
    for (int i = 1; i <= tx; i++)
        for(int j = 1; j <= ty; j++)
            s[i][j] = s[i-1][j] + s[i][j-1] - s[i-1][j-1] + s[i][j];
    int l = 1, r = 10000;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (pd(mid)) r = mid;
        else l = mid + 1;
    }
    cout << l << endl;
    return 0;
}
