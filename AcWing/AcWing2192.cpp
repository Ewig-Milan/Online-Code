#include <bits/stdc++.h>
using namespace std;

const int N = 200, M = 11100, INF = 1e9;

int n, m, S, T;
int cost;

int h[N], e[M], ca[M], v[M], ne[M], idx;
void add(int a, int b, int c, int d) {
    e[idx] = b, ca[idx] = c, v[idx] = d, ne[idx] = h[a], h[a] = idx++;
    e[idx] = a, ca[idx] = 0, v[idx] = -d, ne[idx] = h[b], h[b] = idx++;
}

int dis[N], can[N];
bool vis[N];
bool SPFA(bool mode) {
    for(int i = 0; i < N; i++) dis[i] = mode ? -INF : INF;
    memset(vis, 0, sizeof vis);
    queue<int> q;
    dis[S] = 0, q.push(S), vis[S] = 1;
    while(!q.empty()) {
        int x = q.front();
        q.pop(), vis[x] = 0;
        can[x] = h[x];
        for(int i = h[x]; ~i; i = ne[i]) {
            int j = e[i];
            if(ca[i] && (mode ? (dis[j] < dis[x] + v[i]) : (dis[j] > dis[x] + v[i]))) {
                dis[j] = dis[x] + v[i];
                if(!vis[j]) q.push(j), vis[j] = 1;
            }
        }
    }
    return mode ? (dis[T] > -INF) : (dis[T] < INF);
}

int dfs(int x, int lim) {
    if(x == T) return lim;
    vis[x] = 1;
    int flow = 0;
    for(int &i = can[x]; ~i && flow < lim; i = ne[i]) {
        int j = e[i];
        if(dis[j] == dis[x] + v[i] && ca[i] && !vis[j]) {
            int tmp = dfs(j, min(ca[i], lim - flow));
            if(!tmp) dis[j] = -1;
            else flow += tmp, ca[i] -= tmp, ca[i ^ 1] += tmp, cost += tmp * v[i];
        }
    }
    vis[x] = 0;
    return flow;
}

int dinic(bool mode) {
    cost = 0;
    for(int i = 0; i < idx; i += 2) ca[i] += ca[i ^ 1], ca[i ^ 1] = 0;
    while(SPFA(mode)) while(dfs(S, INF));
    return cost;
}

int main() {
    memset(h, -1, sizeof h);
    scanf("%d%d", &n, &m);
    S = 0, T = n + m + 1;
    for(int i = 1; i <= n; i++) {
        int a; scanf("%d", &a);
        add(S, i, a, 0);
    }
    for(int i = 1; i <= m; i++) {
        int a; scanf("%d", &a);
        add(i + n, T, a, 0);
    }
    for(int i = 1; i <= n; i++)
    for(int j = 1; j <= m; j++) {
        int a; scanf("%d", &a);
        add(i, j + n, INF, a);
    }
    printf("%d\n%d", dinic(0), dinic(1));
    return 0;
}