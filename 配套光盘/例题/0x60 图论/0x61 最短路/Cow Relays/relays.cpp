#include <cstdio>
#include <cstring>
using namespace std;

FILE *fout = fopen ("relays.out", "w");
FILE *fin = fopen ("relays.in", "r");

const int INF = 1000000000;
const int MAXV = 105;
const int MAXI = 1005;
const int MAXL = 20;

int N, V, T, S, E;

// compress nodes to smaller values
int change [MAXI];

// shortest path between two nodes with a length of a power of two
int dist [MAXL][MAXV][MAXV];

// best path from S to a node
int best [MAXV], best2 [MAXV];

// change a node to a 'compressed' value
inline void check (int &ind)
{
    if (change [ind] == -1)
        change [ind] = V++;

    ind = change [ind];
}

int main () {
// initialize arrays
    memset (change, -1, sizeof (change));
    memset (dist, 63, sizeof (dist));
    memset (best, 63, sizeof (best));

    fscanf (fin, "%d %d %d %d", &N, &T, &S, &E);

    check (S);
    check (E);

    for (int i = 0; i < T; i++) {
        int A, B, L;

        fscanf (fin, "%d %d %d", &L, &A, &B);

        check (A);
        check (B);

// edges are paths of length 1
        dist [0][A][B] <?= L;
        dist [0][B][A] <?= L;
    }

// compute shortest paths whose lengths are powers of two
// a path of length 2^p can be made by two paths of length 2^(p - 1)
    for (int p = 1; (1 << p) <= N; p++)
        for (int i = 0; i < V; i++)
            for (int j = 0; j < V; j++)
                if (dist [p - 1][i][j] < INF)
                    for (int k = 0; k < V; k++)
                        if (dist [p - 1][i][j] + dist [p - 1][j][k] < dist [p][i][k])
                            dist [p][i][k] = dist [p - 1][i][j] + dist [p - 1][j][k];


// combine results of each power of two in the binary representation of N
    best [S] = 0;

    for (int p = 0; (1 << p) <= N; p++)
        if (N & (1 << p)) {
// use a temporary array 'best2' to hold the new values, and copy them to the old array afterward
            memset (best2, 63, sizeof (best2));

            for (int i = 0; i < V; i++)
                if (best [i] < INF)
                    for (int j = 0; j < V; j++)
                        if (best [i] + dist [p][i][j] < best2 [j])
                            best2 [j] = best [i] + dist [p][i][j];

            memcpy (best, best2, sizeof (best2));
        }

// best [E] is now the shortest path from S to E using N edges
    fprintf (fout, "%d\n", best [E]);

    return 0;
}
