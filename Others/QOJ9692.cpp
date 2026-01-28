#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 600, M = 6100, INF = 1e8;

int n, m, s = 0, t = N - 1;


int h[N], e[M], ca[M], ne[M], idx;
void add(int a, int b, int c) {
    e[idx] = b, ca[idx] = c, ne[idx] = h[a], h[a] = idx++;
    e[idx] = a, ca[idx] = 0, ne[idx] = h[b], h[b] = idx++;
}

int dep[N], can[N];
bool bfs() {
    queue<int> q;
    memset(dep, -1, sizeof dep);
    dep[s] = 0, q.push(s);
    while(!q.empty()) {
        int x = q.front();
        q.pop();
        can[x] = h[x];
        if(x == t) return 1;
        for(int i = h[x]; ~i; i = ne[i]) {
            int j = e[i];
            if(dep[j] == -1 && ca[i]) dep[j] = dep[x] + 1, q.push(j);
        }
    }
    return 0;
}

int dfs(int x, int lim) {
    if(x == t) return lim;
    int flow = 0;
    for(int &i = can[x]; ~i && flow < lim; i = ne[i]) {
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
    while(bfs()) while(tmp = dfs(s, INF)) mf += tmp;
    return mf;
}

signed main() {
    memset(h, -1, sizeof h);
    scanf("%lld%lld", &n, &m);
    for(int i = 1; i < n; i++) {
        int a; scanf("%lld", &a);
        add(s, i, a);
    }
    for(int i = 1; i <= n; i++) {
        int a; scanf("%lld", &a);
        if(i == 1) add(1, t, a);
        else if(i == n) add(s, n - 1, a);
        else add(i, i - 1, a), ca[idx - 1] = a;
    }
    for(int i = 1; i < n; i++) {
        int a; scanf("%lld", &a);
        add(i, t, a);
    }
    while(m--) {
        int a, b, c; scanf("%lld%lld%lld", &a, &b, &c);
        add(b, a, c);
    }
    printf("%lld", dinic());
    return 0;
}