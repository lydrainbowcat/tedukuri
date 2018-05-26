// Author: LiRe
#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

#define LL long long
#define X first
#define Y second
#define M 9901
#define mp make_pair

inline LL ksm(LL a, LL b) {
    int ans = 1;
    while(b) {
        if(b & 1) ans = a * ans % M;
        a = a * a % M;
        b >>= 1;
    }
    return ans;
} 

inline LL solve(LL p, LL c) {
    if(!p) return 0;
    if(!c) return 1;
    if(c & 1) 
        return (1 + ksm(p, (c + 1 >> 1))) * solve(p, (c - 1) >> 1) % M;
    else 
        return ((1 + ksm(p, c >> 1)) * solve(p, (c >> 1) - 1) % M + ksm(p, c)) % M; 
}

vector<pair<int, int> > vpi;
bool notprime[10003];
int prime[10003], cnt;
inline void getPrime() {
    prime[1] = 2; cnt = 1;
    for(int i = 3; i <= 10003; i += 2) {
        if(notprime[i]) continue;
        prime[++cnt] = i;
        for(int j = 2; i * j < 10003; ++j)
            notprime[i * j] = 1;
    }
}
inline void fj(LL x) {
    int qwq = 0;
    for(int i = 1; i <= cnt; ++i) {
        qwq = 0;
        while(x % prime[i] == 0)
            x /= prime[i], ++qwq;
        if(qwq) vpi.push_back(mp(prime[i], qwq));
    }
    if(x != 1) vpi.push_back(mp(x, 1));
}

int main() {
    getPrime();
    int a, b;
    cin>>a>>b;
    fj(a);
    LL ans = 1;
    for(int i = 0; i < vpi.size(); ++i) {
        ans = (ans * solve(vpi[i].first, b * vpi[i].second)) % M;
    }
    cout<<ans<<endl;
}