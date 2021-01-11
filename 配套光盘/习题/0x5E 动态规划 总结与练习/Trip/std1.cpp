#include<bits/stdc++.h>
using namespace std;
int f[82][82], n, m;
char a[82], b[82];
int preA[82][26], preB[82][26];
char ans[82];
vector<char> last[82][82];

void print(int i, int j, int len) {
    if (f[i][j] == 1) {
        ans[len] = 0;
        puts(ans);
        return;
    }
    for (int k = 0; k < last[i][j].size(); k++) {
        char ch = last[i][j][k];
        ans[len] = ch;
        print(preA[i - 1][ch - 'a'], preB[j - 1][ch - 'a'], len + 1);
    }
}

int main() {
    scanf("%s%s", a + 1, b + 1);
    n = strlen(a + 1);
    m = strlen(b + 1);
    reverse(a + 1, a + n + 1); // 倒着做，每次优先转移小的字母，字典序最小
    reverse(b + 1, b + m + 1);
    for (int i = 1; i <= n; i++) { // 预处理i或i之前最后一个ch的位置
        for (int ch = 0; ch < 26; ch++) preA[i][ch] = preA[i - 1][ch];
        preA[i][a[i] - 'a'] = i;
    }
    for (int i = 1; i <= m; i++) {
        for (int ch = 0; ch < 26; ch++) preB[i][ch] = preB[i - 1][ch];
        preB[i][b[i] - 'a'] = i;
    }
    a[++n] = b[++m] = '$'; // 多放一个结尾字符，方便直接从n+1,m+1开始print
    memset(f, 0xcc, sizeof(f));
    f[0][0] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (a[i] == b[j]) {
                for (int ch = 'a'; ch <= 'z'; ch++) {
                    int pa = preA[i - 1][ch - 'a'];
                    int pb = preB[j - 1][ch - 'a'];
                    if (f[pa][pb] + 1 > f[i][j]) {
                        f[i][j] = f[pa][pb] + 1;
                        last[i][j].clear();
                        last[i][j].push_back(ch);
                    } else if (f[pa][pb] + 1 == f[i][j]) {
                        last[i][j].push_back(ch);
                    }
                }
            }
    print(n, m, 0);
}