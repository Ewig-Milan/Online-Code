#include <bits/stdc++.h>
using namespace std;

const int N = 600, M = 10100, INF = 1e9;

int n, m, S, T, ans;
bool rch[N][2];

int h[N], e[M], ne[M], ca[M], idx;
void add(int a, int b, int c) {
    e[idx] = b, ca[idx] = c, ne[idx] = h[a], h[a] = idx++;
    e[idx] = a, ca[idx] = 0, ne[idx] = h[b], h[b] = idx++;
}

int dep[N], can[N];
bool bfs() {
    memset(dep, -1, sizeof dep);
    queue<int> q;
    dep[S] = 0, q.push(S);
    while(!q.empty()) {
        int x = q.front();
        q.pop();
        can[x] = h[x];
        if(x == T) return true;
        for(int i = h[x]; ~i; i = ne[i]) {
            int j = e[i];
            if(dep[j] == -1 && ca[i]) dep[j] = dep[x] + 1, q.push(j);
        }
    }
    return false;
}

int dfs(int x, int lim) {
    if(x == T) return lim;
    int flow = 0;
    for(int i = can[x]; ~i && flow < lim; i = ne[i]) {
        can[x] = i;
        int j = e[i];
        if(ca[i] && dep[j] == dep[x] + 1) {
            int tmp = dfs(j, min(ca[i], lim - flow));
            if(!tmp) dep[j] = -1;
            else flow += tmp, ca[i] -= tmp, ca[i ^ 1] += tmp;
        }
    }
    return flow;
}

int dinic() {
    int mf = 0, tmp;
    while(bfs()) while(tmp = dfs(S, INF)) mf += tmp;
    return mf;
}

void reach(int x, bool dir) {
    rch[x][dir] = true;
    for(int i = h[x]; ~i; i = ne[i]) {
        int j = e[i];
        if(!rch[j][dir] && ca[i ^ dir]) reach(j, dir);
    }
}

int main() {
    memset(h, -1, sizeof h);
    scanf("%d%d", &n, &m);
    S = 0, T = n - 1;
    for(int i = 1; i <= m; i++) {
        int a, b, c; scanf("%d%d%d", &a, &b, &c);
        add(a, b, c);
    }
    dinic();
    reach(S, 0), reach(T, 1);
    for(int i = 0; i < m * 2; i += 2)
        if(!ca[i] && rch[e[i]][1] && rch[e[i ^ 1]][0]) ans++;

    printf("%d", ans);
    return 0;
}