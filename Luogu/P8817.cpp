#include <bits/stdc++.h>
#define int long long
#define PII pair<int, int>
#define fi first
#define se second
using namespace std;

const int N = 2600, M = 20100;

int n, m, k;

int h[N], e[M], ne[M], idx;
void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
    e[idx] = a, ne[idx] = h[b], h[b] = idx++;
}

int w[N];
bool G[N][N];

bool vis1[N];
void bfs1(int x, int l, int dep) {
    queue<array<int, 3> > q;
    q.push({x, l, dep});
    while(!q.empty()) {
        auto X = q.front();
        q.pop();
        if(X[2] > k) continue;
        if(vis1[X[0]]) continue;
        vis1[X[0]] = 1;
        for(int i = h[X[0]]; ~i; i = ne[i]) {
            int j = e[i];
            if(j == X[1]) continue;
            q.push({j, X[0], X[2] + 1});
        }
    }
}

PII f[N], g[N], p[N]; // 先存值 后存下标

bool vis2[N];
void bfs2(int rt, int x, int l, int dep) {
    queue<array<int, 3> > q;
    q.push({x, l, dep});
    while(!q.empty()) {
        auto X = q.front();
        q.pop();
        if(X[2] > k) continue;
        if(vis2[X[0]]) continue;
        vis2[X[0]] = G[rt][X[0]] = 1;
        if(vis1[X[0]] && X[0] != rt && X[0] != 1) {
            if(w[X[0]] >= f[rt].fi) p[rt] = g[rt], g[rt] = f[rt], f[rt] = {w[X[0]], X[0]};
            else if(w[X[0]] >= g[rt].fi) p[rt] = g[rt], g[rt] = {w[X[0]], X[0]};
            else if(w[X[0]] >= p[rt].fi) p[rt] = {w[X[0]], X[0]};
        }
        for(int i = h[X[0]]; ~i; i = ne[i]) {
            int j = e[i];
            if(j == X[1]) continue;
            q.push({j, X[0], X[2] + 1});
        }
    }
}

signed main() {
    memset(h, -1, sizeof h);
    scanf("%lld%lld%lld", &n, &m, &k);
    for(int i = 2; i <= n; i++) scanf("%lld", &w[i]);
    for(int i = 1; i <= m; i++) {
        int a, b; scanf("%lld%lld", &a, &b);
        add(a, b);
    }
    bfs1(1, 0, -1);
    for(int i = 2; i <= n; i++) {
        memset(vis2, 0, sizeof vis2);
        bfs2(i, i, 0, -1);
    }
    int ans = 0;
    for(int i = 2; i <= n; i++)
    for(int j = i + 1; j <= n; j++) {
        if(!G[i][j]) continue;
        if(f[i].se && f[j].se && f[i].se != f[j].se && f[i].se != j && f[j].se != i) ans = max(ans, w[i] + w[j] + f[i].fi + f[j].fi);
        else {
            if(f[i].se && g[j].se && f[i].se != g[j].se && f[i].se != j && g[j].se != i) ans = max(ans, w[i] + w[j] + f[i].fi + g[j].fi);
            if(g[i].se && f[j].se && g[i].se != f[j].se && g[i].se != j && f[j].se != i) ans = max(ans, w[i] + w[j] + g[i].fi + f[j].fi);
            if(g[i].se && g[j].se && g[i].se != g[j].se && g[i].se != j && g[j].se != i) ans = max(ans, w[i] + w[j] + g[i].fi + g[j].fi);
            if(f[i].se && p[j].se && f[i].se != p[j].se && f[i].se != j && p[j].se != i) ans = max(ans, w[i] + w[j] + f[i].fi + p[j].fi);
            if(p[i].se && f[j].se && p[i].se != f[j].se && p[i].se != j && f[j].se != i) ans = max(ans, w[i] + w[j] + p[i].fi + f[j].fi);
            if(g[i].se && p[j].se && g[i].se != p[j].se && g[i].se != j && p[j].se != i) ans = max(ans, w[i] + w[j] + g[i].fi + p[j].fi);
            if(p[i].se && g[j].se && p[i].se != g[j].se && p[i].se != j && g[j].se != i) ans = max(ans, w[i] + w[j] + p[i].fi + g[j].fi);
            if(p[i].se && p[j].se && p[i].se != p[j].se && p[i].se != j && p[j].se != i) ans = max(ans, w[i] + w[j] + p[i].fi + p[j].fi);
        }
    }
    printf("%lld", ans);
    return 0;
}