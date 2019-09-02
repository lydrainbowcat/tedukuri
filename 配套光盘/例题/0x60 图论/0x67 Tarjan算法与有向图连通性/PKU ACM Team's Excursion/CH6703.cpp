#include <cstdio>
#include <queue>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

const ll maxn = 300010,maxm = 400010,inf = 0x7fffffff;
const ll mod = 1e9+7;
ll T,n,m,s,t,q,head[maxn],to[maxm],nextt[maxm],w[maxm],tot = 1,d[maxn],last[maxm],du[maxn],du2[maxn],pre[maxn],flag[maxn];
ll head2[maxn],to2[maxm],nextt2[maxm],w2[maxm],tot2 = 1,path[maxn],cnt,sum[maxn],f[maxn],g[maxn],ans,flag2[maxn],tdu[maxn];
ll fs[maxn],ft[maxn];

void add(ll x,ll y,ll z)
{
    w[++tot] = z;
    to[tot] = y;
    last[tot] = x;
    nextt[tot] = head[x];
    head[x] = tot;
    du[y]++;
}

void add2(ll x,ll y,ll z)
{
    w2[++tot2] = z;
    to2[tot2] = y;
    nextt2[tot2] = head2[x];
    head2[x] = tot2;
    du2[y]++;
}

void topo1()
{
    memcpy(tdu,du,sizeof(du));
    queue <ll> q;
    fs[s] = 1;
    for (ll i = 1; i <= n; i++)
        if (!tdu[i])
            q.push(i);
    while (!q.empty())
    {
        ll u = q.front();
        q.pop();
        for (ll i = head[u]; i; i = nextt[i])
        {
            ll v = to[i];
            fs[v] += fs[u];
            fs[v] %= mod;
            if (--tdu[v] == 0)
                q.push(v);
        }
    }
}

void topo2()
{
    queue<ll> q;
    ft[t] = 1;
    for (ll i = 1; i <= n; i++)
        if (!du2[i])
            q.push(i);
    while (!q.empty())
    {
        ll u = q.front();
        q.pop();
        for (ll i = head2[u]; i; i = nextt2[i])
        {
            ll v = to2[i];
            ft[v] += ft[u];
            ft[v] %= mod;
            if (--du2[v] == 0)
                q.push(v);
        }
    }
}

void topo3()
{
    queue <ll> q;
    for (ll i = 1; i <= n; i++)
        if (!du[i])
            q.push(i);
    while (!q.empty())
    {
        ll u = q.front();
        q.pop();
        for (ll i = head[u];i;i = nextt[i])
        {
            ll v = to[i];
            if (d[v] > d[u] + w[i])
            {
                d[v] = d[u] + w[i];
                pre[v] = u;
            }
            if (--du[v] == 0)
                q.push(v);
        }
    }
}

void dfs(ll u,ll dist)
{
    for (ll i = head[u]; i; i = nextt[i])
    {
        ll v = to[i];
        if (d[v] > dist + w[i])
        {
            pre[v] = u;
            d[v] = dist + w[i];
            dfs(v,dist + w[i]);
        }
    }
}

void solve1()
{
    ll cur = 1;
    for (ll i = 1; i <= cnt; i++)
    {
        while (d[path[i]] - d[path[cur]] > q)
            cur++;
        f[i] = f[i - 1];
        ll temp = sum[path[i]] - sum[path[cur]];
        if (flag[path[cur]])
            temp += q - (d[path[i]] - d[path[cur]]);
        f[i] = max(f[i],temp);
    }
}

void solve2()
{
    ll cur = cnt;
    for (ll i = cnt; i >= 1; i--)
    {
        while (d[path[cur]] - d[path[i]] > q)
            cur--;
        g[i] = g[i + 1];
        ll temp = sum[path[cur]] - sum[path[i]];
        if (flag2[path[cur]])
            temp += q - (d[path[cur]] - d[path[i]]);
        g[i] = max(g[i],temp);
    }
}

int main()
{
    scanf("%lld",&T);
    while (T--)
    {
        ans = inf;
        memset(head,0,sizeof(head));
        memset(head2,0,sizeof(head2));
        memset(sum,0,sizeof(sum));
        memset(fs,0,sizeof(fs));
        memset(ft,0,sizeof(ft));
        memset(flag,0,sizeof(flag));
        memset(flag2,0,sizeof(flag2));
        memset(f,0,sizeof(f));
        memset(g,0,sizeof(g));
        tot = tot2 = 0;
        scanf("%lld%lld%lld%lld%lld",&n,&m,&s,&t,&q);
        for (ll i = 1; i <= n; i++)
            d[i] = inf;
        s++;
        t++;
        for (ll i = 1; i <= m; i++)
        {
            ll a,b,c;
            scanf("%lld%lld%lld",&a,&b,&c);
            a++;
            b++;
            add(a,b,c);
            add2(b,a,c);
        }
        topo1();
        topo2();
        for (ll i = 1; i <= tot; i++)
        {
            ll x = last[i],y = to[i];
            if (fs[x] * ft[y] % mod == fs[t])
            {
                sum[y] = w[i];
                flag[y] = 1;
                flag2[x] = 1;
            }
        }
        d[s] = 0;
        topo3();
        if (d[t] == inf)
            puts("-1");
        else
        {
            cnt = 0;
            ll p = t;
            do
            {
                path[++cnt] = p;
                p = pre[p];
            }
            while (p != s);
            path[++cnt] = s;
            reverse(path + 1,path + 1 + cnt);
            for (ll i = 1; i <= cnt; i++)
                sum[path[i]] += sum[path[i - 1]];
            solve1();
            solve2();
            ll temp = sum[path[cnt]];
            for (ll i = 1; i <= cnt; i++)
                ans = min(ans,temp - (f[i] + g[i]));
            printf("%lld\n",ans);
        }
    }

    return 0;
}