#include <bits/stdc++.h>
using namespace std;

const int N = 610;

int n, m;

struct Edge {int next, to;} e[N];

int rt, h[N], idx, v[N], f[N][N];
void add(int x, int y) {
    e[++idx].next = h[x];
    h[x] = idx;
    e[idx].to = y;
}

void DP(int u, int t) {
    if(t <= 0) return;
    for(int i = h[u]; i; i = e[i].next) {
        int j = e[i].to;
        for(int k = 0; k < t; ++k) f[j][k] = f[u][k] + v[j];
        DP(j, t - 1);
        for(int k = 1; k <= t; ++k) f[u][k] = max(f[u][k], f[j][k - 1]);
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++) {
        int a; scanf("%d%d", &a, &v[i]);
        if(a) add(a, i);
        else add(0, i);
    }
    DP(0, m);
    printf("%d", f[0][m]);
    return 0;
}