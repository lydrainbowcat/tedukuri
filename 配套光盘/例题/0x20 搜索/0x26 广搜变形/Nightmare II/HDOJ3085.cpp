// Author: https://blog.csdn.net/lmhlmh_/article/details/82683884
#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
#include <algorithm>
using namespace std;
 
char graph[805][805];   // 地图,从下标1开始记录
int time;       // 时间
int n,m;        // 地图行列数
int t;
int dir[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};    // 方向
struct node {
    // 点
    int x,y;
}gg,mm,zz[2];           // g,m,和ghost
queue<node> q[2],qt;    // gg和mm队列，临时队列
/**
 *  判断某个点是否可能满足条件
 **/
bool isOk(node t) {
    if(t.x < 1 || t.x > n || t.y < 1 || t.y > m)
        return false;   // 越界
    if(graph[t.x][t.y] == 'X' || graph[t.x][t.y] == '\0')
        return false;   // 墙
    for (int i = 0; i < 2; i++) {
        if(2*time >= abs(t.x-zz[i].x) + abs(t.y-zz[i].y))
            return false;     // 距离幽灵太近
    }    
    
    return true;
}
 
/**
 * 广度优先搜索 
 * mark:标记是g还是m
 * num: 一秒最多走的步数
 */
bool bfs(int mark,int num,char start,char endd) {
    node a,b;   // 临时节点
    qt = q[mark];    // 临时队列
    for (int i = 0; i < num; i++) {
        // 遍历所有可能到达的点
        while(!qt.empty()) {
            a = qt.front(),qt.pop(),q[mark].pop();
            if(!isOk(a)) continue;
            for (int i = 0; i < 4; i++) {
                // 4个方向
                b = a;
                b.x += dir[i][0],b.y += dir[i][1];
                if(!isOk(b) || graph[b.x][b.y] == start)
                    continue;         // start避免重复走相同的路
                if(graph[b.x][b.y] == endd)    
                    return true;     // 其中一人能到达另一人可以到达的点
                graph[b.x][b.y] = start;    // 标记走过的点
                q[mark].push(b);
            }
        }
        qt = q[mark];
    }
    return false;
}
 
/**
 * 计算结果 
 */
int solve() {
    // 初始化
    time = 0;
    while(!q[0].empty()) q[0].pop();
    while(!q[1].empty()) q[1].pop();
    while(!qt.empty()) qt.pop();
    
    q[0].push(mm);
    q[1].push(gg);
    
    while(!q[0].empty() && !q[1].empty()) {
        time++;
        bool flag1 = bfs(0,3,'M','G');
        bool flag2 = bfs(1,1,'G','M');
        if(flag1 || flag2)
            return time;
    }
    return -1;
}
 
int main() {
    scanf("%d",&t);
    while(t--) {
        scanf("%d%d",&n,&m);
        memset(graph,'X',sizeof(graph));
        for(int k = 0,i = 1;i <= n;i++) {
            scanf("%s",graph[i]+1);
            for(int j = 1;j <= m;j++) {
                if(graph[i][j] == 'M') mm.x = i,mm.y = j;
                if(graph[i][j] == 'G') gg.x = i,gg.y = j;
                if(graph[i][j] == 'Z') zz[k].x = i,zz[k].y = j,k++;
                
            }
        }
        printf("%d\n",solve());
    }
    return 0;
}
