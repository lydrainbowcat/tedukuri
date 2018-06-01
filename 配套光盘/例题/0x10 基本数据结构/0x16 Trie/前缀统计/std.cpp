#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int SIZE=1000010;
int trie[SIZE][26], tot = 1; // 初始化，假设字符串由小写字母构成
int ed[SIZE];
int n, m;
char str[SIZE];

void insert(char* str) { // 插入一个字符串
    int len = strlen(str), p = 1;
    for (int k = 0; k < len; k++) {
        int ch = str[k]-'a';
        if (trie[p][ch] == 0) trie[p][ch] = ++tot;
        p = trie[p][ch];
    }
    ed[p]++;
}

int search(char* str) {
    int len = strlen(str), p = 1;
    int ans = 0;
    for (int k = 0; k < len; k++) {
        p = trie[p][str[k]-'a'];
        if (p == 0) return ans;
        ans += ed[p];
    }
    return ans;
}

int main() {
    cin>>n>>m;
    for(int i=1;i<=n;i++) {
        scanf("%s",str);
        insert(str);
    }
    for(int i=1;i<=m;i++) {
        scanf("%s",str);
        printf("%d\n", search(str));
    }
}