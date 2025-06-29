#include <bits/stdc++.h>
using namespace std;

const int N = 13;

int n, m, ans = 1e7;
int g[N][N], cost[1 << 12][1 << 12];
int f[N][1 << N];

void pre() {
    for(int i = 0; i < (1 << 12); i++) 
    for(int j = 0; j < (1 << 12); j++) cost[i][j] = 1e7;
    for(int t = 1; t < (1 << n); t++) {
        cost[t][t] = 0;
        for(int s = (t - 1) & t; s; s = (s - 1) & t) {
            int c_t = (t ^ s) & -(t ^ s), id_ct = 0, mi = 1e7;
            while(c_t) c_t >>= 1, id_ct++;
            for(int i = 1; i <= n; i++) if(s >> (i - 1) & 1) mi = min(mi, g[i][id_ct]);
            cost[s][t] = cost[s][((t ^ s) - ((t ^ s) & -(t ^ s))) | s] + mi;
        }
    }
}

int main() {
    for(int i = 0; i < N; i++) 
    for(int j = 0; j < N; j++) g[i][j] = 1e7;
    for(int i = 0; i < N; i++)
    for(int j = 0; j < (1 << N); j++) f[i][j] = 1e7;
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; i++) {
        int a, b, c; scanf("%d%d%d", &a, &b, &c);
        g[a][b] = g[b][a] = min(g[a][b], c);
    }
    pre();
    for(int i = 0; i < n; i++) f[0][1 << i] = 0;
    ans = min(ans, f[0][(1 << n) - 1]);
    for(int i = 1; i < n; i++) {
        for(int t = 1; t < (1 << n); t++)
        for(int s = (t - 1) & t; s; s = (s - 1) & t)
            f[i][t] = min(f[i][t], f[i - 1][s] + cost[s][t] * i);
        ans = min(ans, f[i][(1 << n) - 1]);
    }
    printf("%d", ans);
    return 0;
}