#include <stdio.h>
#include <math.h>

#include <algorithm>

//const int MAX_S = 100;
const int MAX_P = 500;
const int MAX_EDGES = MAX_P * (MAX_P - 1) / 2;

int S; // satellite uplinks available
int P; // number of outposts
int x[MAX_P], y[MAX_P]; // outpost coordinates

// Strategy:
//   Using union-find to keep track of connected components,
//   add edges to the network in increasing order of D,
//   until there are only as many components as satellite links
//   remaining.

struct Edge {
	int a, b; // connecting outposts
	int d; // squared distance
};

int E; // number of edges
Edge e[MAX_EDGES]; // all edges

int C; // number of components
int D; // minimum D (squared)
int u[MAX_P]; // parent-function for union-find
int w[MAX_P]; // rank function for union-find

bool compare_distance(Edge const &a, Edge const &b) {
	return a.d < b.d;
}

void unify(int a, int b) {
	int q = a;
	while (u[q] != q) q = u[q];
	int c1 = q;
	q = a;
	while (u[q] != q) { // path compression
		int qq = u[q];
		u[q] = c1;
		q = qq;
	}
	q = b;
	while (u[q] != q) q = u[q];
	int c2 = q;
	q = b;
	while (u[q] != q) { // path compression
		int qq = u[q];
		u[q] = c2;
		q = qq;
	}
	if (c1 == c2) return; // already connected
	if (w[c1] > w[c2]) { // union by rank
		u[c2] = c1;
	} else {
		u[c1] = c2;
		if (w[c1] == w[c2]) w[c2]++;
	}
	C -= 1;
}

int main(int argc, char *argv[]) {
	int N;
	scanf("%d", &N);
	for (int n = 1; n <= N; n++) {
		scanf("%d %d", &S, &P);
		for (int i = 0; i < P; i++) {
			scanf("%d %d", &x[i], &y[i]);
		}
		int E = 0;
		for (int i = 0; i < P; i++) {
			for (int j = i + 1; j < P; j++) {
				e[E].a = i;
				e[E].b = j;
				int dx = x[i] - x[j], dy = y[i] - y[j];
				e[E].d = dx * dx + dy * dy;
				E++;
			}
		}
		sort(e, e+E, compare_distance);
		for (int i = 0; i < P; i++) {
			u[i] = i;
			w[i] = 0;
		}
		D = 0;
		C = P;
		for (int i = 0; C > S; i++) {
			unify(e[i].a, e[i].b);
			D = e[i].d;
		}
		printf("%.2lf\n", sqrt((double) D));
	}
}

// vim:ts=4:sw=4
