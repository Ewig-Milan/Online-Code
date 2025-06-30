#include <bits/stdc++.h>
using namespace std;

const int N = 10100, M = 100100, INF = 1e9;

int n, F, D, S, T;

int h[N], ca[M], e[M], ne[M], idx;
void add(int a, int b) {
    e[idx] = b, ca[idx] = 1, ne[idx] = h[a], h[a] = idx++;
    e[idx] = a, ca[idx] = 0, ne[idx] = h[b], h[b] = idx++;
}

int dep[N], can[N];
bool bfs() {
    memset(dep, -1, sizeof dep);
    queue<int> q;
    q.push(S), dep[S] = 0;
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
    scanf("%d%d%d", &n, &F, &D);
    S = 0, T = n * 2 + F + D + 1;
    for(int i = 1; i <= F; i++) add(S, i);
    for(int i = 1; i <= D; i++) add(F + n * 2 + i, T);
    for(int i = 1; i <= n; i++) add(F + i, F + n + i);
    for(int i = 1; i <= n; i++) {
        int a, b; scanf("%d%d", &a, &b);
        while(a--) {
            int c; scanf("%d", &c);
            add(c, F + i);
        }
        while(b--) {
            int c; scanf("%d", &c);
            add(F + n + i, F + n * 2 + c);
        }
    }
    printf("%d", dinic());
    return 0;
}