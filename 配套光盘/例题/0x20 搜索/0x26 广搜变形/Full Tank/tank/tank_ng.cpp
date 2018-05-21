#include <algorithm>
#include <cstdio>
#include <vector>
#include <queue>
#include <stdint.h>

using namespace std;

const int INF = 1 << 28;

const int MAX_n = 1000;
const int MAX_c = 100;

struct RoadTo {
    int city, dist;
    RoadTo(int city, int dist) : city(city), dist(dist) {}
};

struct Node {
    int cost, city, fuel;
    Node(int cost, int city, int fuel) : cost(cost), city(city), fuel(fuel) {}
    bool operator<(const Node& v) const { return cost > v.cost; }
};

int main()
{
    int n, m, q;
    scanf("%d %d", &n, &m);
    int P[MAX_n]; // Fuel prices
    for (int u = 0; u < n; u++) scanf("%d", &P[u]);
    vector<RoadTo> E[MAX_n]; // Neighbour lists
    for (int i = 0; i < m; i++) {
        int u, v, d;
        scanf("%d %d %d", &u, &v, &d);
        E[u].push_back(RoadTo(v, d));
        E[v].push_back(RoadTo(u, d));
    }
    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        int c, s, e;
        scanf("%d %d %d", &c, &s, &e);
        int  C[MAX_n][MAX_c+1]; // Cost of getting to a city with a tank fill
        bool S[MAX_n][MAX_c+1]; // Node is visited
        for (int u = 0; u < n; u++) {
            for (int k = 0; k <= c; k++) {
                C[u][k] = INF;
                S[u][k] = false;
            }
        }
        C[s][0] = 0;
        priority_queue<Node> Q;
        Q.push(Node(0, s, 0));
        while (Q.size()) {
            int t = Q.top().cost, u = Q.top().city, f = Q.top().fuel; Q.pop();
            if (S[u][f]) continue;
            if (u == e) break;
            // Fueling up
            if (f < c) {
                if (t + P[u] < C[u][f+1]) {
                    C[u][f+1] = t + P[u];
                    Q.push(Node(Node(t + P[u], u, f+1)));
                }
            }
            // Going places
            for (size_t i = 0; i < E[u].size(); i++) {
                int v = E[u][i].city, d = E[u][i].dist;
                if (f - d >= 0 && C[u][f] < C[v][f-d]) {
                    C[v][f-d] = C[u][f];
                    Q.push(Node(C[v][f-d], v, f-d));
                }
            }
            S[u][f] = true;
        }
        if (C[e][0] < INF) printf("%d\n", C[e][0]);
        else               printf("impossible\n");
    }
}
