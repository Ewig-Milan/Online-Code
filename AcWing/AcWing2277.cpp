#include <bits/stdc++.h>
using namespace std;

const int N = 300, M = 80100, INF = 1e9;

int n, m, T;
int s, t;
int L[M >> 1];

int h[N], e[M], ca[M], ne[M], idx;
void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
    e[idx] = a, ne[idx] = h[b], h[b] = idx++;
}

int dep[N], can[N];
bool bfs() {
    memset(dep, -1, sizeof dep);
    queue<int> q;
    q.push(s), dep[s] = 0;
    while(!q.empty()) {
        int x = q.front();
        q.pop();
        can[x] = h[x];
        if(x == t) return true;
        for(int i = h[x]; ~i; i = ne[i]) {
            int j = e[i];
            if(dep[j] == -1 && ca[i]) dep[j] = dep[x] + 1, q.push(j);
        }
    }
    return false;
}

int dfs(int x, int lim) {
    if(x == t) return lim;
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
    while(bfs()) while(tmp = dfs(s, INF)) mf += tmp;
    return mf;
}

bool check(int x) {
    memset(ca, 0, sizeof ca);
    for(int i = 1; i <= m; i++) if(L[i] <= x)
        ca[(i << 1) - 1] = ca[(i << 1) - 2] = 1;
    return dinic() >= T;
}

int main() {
    memset(h, -1, sizeof h);
    scanf("%d%d%d", &n, &m, &T);
    s = 1, t = n;
    for(int i = 1; i <= m; i++) {
        int a, b; scanf("%d%d%d", &a, &b, &L[i]);
        add(a, b);
    }
    int l = 1, r = 1e6;
    while(l < r) {
        int mid = l + r >> 1;
        if(check(mid)) r = mid;
        else l = mid + 1;
    }
    printf("%d", l);
    return 0;
}