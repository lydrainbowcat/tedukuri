#include<fstream>
#include<vector>

using namespace std;

ifstream fin ("phoneline.in");
ofstream fout ("phoneline.out");

const int MAX = 1000 + 5;

vector <int> a[MAX], b[MAX];
int     e[MAX * 10];

bool    mark[MAX];
int     dis [MAX], saf[MAX], head, tail;

int     n, k, D, M;

void dfs (int u) {
    dis[u] = D;
    mark[u] = true;
    saf[tail++] = u;
    for (int i = 0; i < a[u].size (); i++) {
        if (!mark[a[u][i]] && b[u][i] <= M)
            dfs (a[u][i]);
    }
}
void Bfs (int MM) {
    M = MM;
    memset (mark, 0, sizeof mark);
    head = tail = 0;
    D = 0;
    dfs (n - 1);
    while (head < tail) {
        int k = saf[head++];
        for (int i = 0; i < a[k].size (); ++i) {
            if (!mark[a[k][i]]) {
                D = dis[k] + 1;
                dfs (a[k][i]);
            }
        }
    }
}

void bs (int x, int y) {
    if (y == x + 1) {
        fout << e[y] << endl;
        exit (0);
    }
    int     mid = (y + x) / 2;
    Bfs (e[mid]);
    if (dis[0] <= k)
        bs (x, mid);
    else
        bs (mid, y);
}
int main () {
    int ee;
    fin >> n >> ee >> k;
    int     u, v, w;
    for (int i = 0; i < ee; ++i) {
        fin >> u >> v >> w;
        u--;
        v--;
        a[u].push_back (v);
        b[u].push_back (w);
        a[v].push_back (u);
        b[v].push_back (w);
        e[i + 1] = w;
    }
    sort (e, e + 1 + ee);
    Bfs (0);
    if (!mark[0]) {
        fout << "-1" << endl;
        return 0;
    }
    if (dis[0] <= k) {
        fout << "0" << endl;
        return 0;
    }
    bs (0, ee);
    return 0;
}
