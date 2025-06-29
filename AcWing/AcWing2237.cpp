#include <bits/stdc++.h>
using namespace std;

const int N = 1000100, M = 3000100, INF = 1e9;

int m, n, S, T;
int pig[N], left_by[N];

int h[N], e[M], ca[M], ne[M], idx;
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
        if(dep[j] == dep[x] + 1 && ca[i]) {
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

int main() {
    memset(h, -1, sizeof h);
    scanf("%d%d", &m, &n);
    S = 0, T = n + 1;
    for(int i = 1; i <= m; i++) scanf("%d", &pig[i]);
    for(int i = 1; i <= n; i++) {
        int a; scanf("%d", &a);
        int fih = 0;
        while(a--) {
            int c; scanf("%d", &c);
            if(!left_by[c]) fih += pig[c];
            else add(left_by[c], i, INF);
            left_by[c] = i;
        }
        add(S, i, fih);
        int b; scanf("%d", &b);
        add(i, T, b);
    }
    printf("%d", dinic());
    return 0;
}