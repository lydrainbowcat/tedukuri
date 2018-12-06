//Author:XuHt
#include <cstring>
#include <iostream>
using namespace std;
const int N = 30;
char s1[N], s2[N], s3[N];
int n, a[N], b[N], c[N];
int num[N], p[N], t = 0;
bool v[N];

bool pd() {
    int x = 0;
    for (int i = n - 1; i >= 0; i--) {
        int A = num[a[i]], B = num[b[i]], C = num[c[i]];
        if ((A + B + x) % n - C) return 0;
        x = (A + B + x) / n;
    }
    return 1;
}

bool jz() {
    if (num[a[0]] + num[b[0]] >= n) return 1;
    for (int i = n - 1; i >= 0; i--) {
        int A = num[a[i]], B = num[b[i]], C = num[c[i]];
        if (A == -1 || B == -1 || C == -1) continue;
        if ((A + B) % n - C && (A + B + 1) % n - C) return 1;
    }
    return 0;
}

void dfs(int x) {
    if (jz()) return;
    if (x == n) {
        if(pd()) {
            for(int i = 0; i < n; i++) cout << num[i] << " ";
            cout << endl;
            exit(0);
        }
        return;
    }
    for (int i = n - 1; i >= 0; i--)
        if (!v[i]) {
            num[p[x]] = i;
            v[i] = 1;
            dfs(x + 1);
            num[p[x]] = -1;
            v[i] = 0;
        }
}

void w(int x) {
    if (!v[x]) {
        v[x] = 1;
        p[t++] = x;
    }
}

int main() {
    cin >> n;
    cin >> s1 >> s2 >> s3;
    memset(num, -1, sizeof(num));
    memset(v, 0, sizeof(v));
    for (int i = 0; i < n; i++) {
        a[i] = s1[i] - 'A';
        b[i] = s2[i] - 'A';
        c[i] = s3[i] - 'A';
    }
    for (int i = n - 1; i >= 0; i--) {
        w(a[i]);
        w(b[i]);
        w(c[i]);
    }
    memset(v, 0, sizeof(v));
    dfs(0);
    return 0;
}
