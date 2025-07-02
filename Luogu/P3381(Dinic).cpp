#include <bits/stdc++.h>
using namespace std;

const int N = 5100, M = 100100, INF = 1e9;

int n, m, S, T;
int cost;

int h[N], ca[M], v[M], ne[M], e[M], idx;
void add(int a, int b, int c, int d) {
    e[idx] = b, ca[idx] = c, v[idx] = d, ne[idx] = h[a], h[a] = idx++;
    e[idx] = a, ca[idx] = 0, v[idx] = -d, ne[idx] = h[b], h[b] = idx++;
}

int dis[N], can[N];
bool vis[N];
bool SPFA() {
    for(int i = 0; i < N; i++) dis[i] = INF;
    memset(vis, 0, sizeof vis);
    queue<int> q;
    dis[S] = 0, vis[S] = 1;
    q.push(S);
    while(!q.empty()) {
        int x = q.front();
        q.pop(), vis[x] = 0;
        can[x] = h[x];
        for(int i = h[x]; ~i; i = ne[i]) {
            int j = e[i];
            if(ca[i] && dis[j] > dis[x] + v[i]) {
                dis[j] = dis[x] + v[i];
                if(!vis[j]) q.push(j), vis[j] = 1;
            }
        }
    }
    return dis[T] < INF;
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
            else flow += tmp, ca[i] -= tmp, ca[i ^ 1] += tmp, cost += v[i] * tmp;
        }
    }
    vis[x] = 0;
    return flow;
}

int dinic() {
    int mf = 0, tmp;
    while(SPFA()) while(tmp = dfs(S, INF)) mf += tmp;
    return mf;
}

int main() {
    memset(h, -1, sizeof h);
    scanf("%d%d%d%d", &n, &m, &S, &T);
    for(int i = 1; i <= m; i++) {
        int a, b, c, d; scanf("%d%d%d%d", &a, &b, &c, &d);
        add(a, b, c, d);
    }
    int tmp = dinic();
    printf("%d %d", tmp, cost);
    return 0;
}