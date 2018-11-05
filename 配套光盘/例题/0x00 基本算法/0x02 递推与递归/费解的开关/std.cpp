// Author: LiRe
#include <iostream>
#include <cstdio>
using namespace std;
#define INF 0x3fffff
char k[5][5]; int a[5][5];
int vx[5] = {-1, 0, 1, 0, 0}, vy[5] = {0, 1, 0, -1, 0};
inline void click(int c, int t) {
    for(int i = 0; i < 5; ++i)
        if(c + vx[i] >= 0 && t + vy[i] >= 0 && c + vx[i] < 5 && t + vy[i] < 5){
            a[c + vx[i]][t + vy[i]] ^= 1;
        }

}
int main() {
    int T; 
    scanf("%d", &T);
    while(T--) {
        for(int i = 0; i < 5; ++i)
            for(int j = 0; j < 5; ++j)
                cin>>k[i][j];
        for(int i = 0; i < 5; ++i)
            for(int j = 0; j < 5; ++j)
                a[i][j] = (int)(k[i][j] - '0');
        int ans = INF, cnt = 0, flag = 0;
        for(int i = 0; i < 32; ++i) {
            flag = 0; cnt = 0;
            for(int j = 0; j < 5; ++j)
                if((i >> j) & 1) ++cnt, click(0, j);
            for(int j = 0; j < 4; ++j) {
                for(int k = 0; k < 5; ++k) {
                    if(!a[j][k]) ++cnt, click(j + 1, k);
                }

            }
            for(int i = 0; i < 5; ++i)
                for(int j = 0; j < 5; ++j)
                    if(!a[i][j]) {flag = 1; break;}
            if(!flag) ans = min(ans, cnt);
            for(int i = 0; i < 5; ++i)
                for(int j = 0; j < 5; ++j)
                    a[i][j] = k[i][j] - '0';
        }
        if(ans == INF || ans > 6) printf("%d\n", -1);
        else printf("%d\n", ans);
    }

}
