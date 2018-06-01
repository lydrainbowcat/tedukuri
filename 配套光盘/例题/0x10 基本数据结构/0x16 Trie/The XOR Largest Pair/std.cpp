#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int SIZE=100010;
int trie[SIZE*32+5][2], tot = 1; // 初始化，假设字符串由小写字母构成
int a[SIZE], n, ans;

void insert(int val) { // 插入一个二进制数
    int p = 1;
    for (int k = 30; k >= 0; k--) {
        int ch = val >> k & 1;
        if (trie[p][ch] == 0) trie[p][ch] = ++tot;
        p = trie[p][ch];
    }
}

int search(int val) {
    int p = 1;
    int ans = 0;
    for (int k = 30; k >= 0; k--) {
        int ch = val >> k & 1;
        if (trie[p][ch ^ 1]) { // 走相反的位
            p = trie[p][ch ^ 1];
            ans |= 1 << k;
        } else { // 只能走相同的位
            p = trie[p][ch];
        }
    }
    return ans;
}

int main() {
    cin>>n;
    for(int i=1;i<=n;i++) {
        scanf("%d", &a[i]);
        insert(a[i]);
        ans=max(ans, search(a[i]));
    }
    cout<<ans<<endl;
}
