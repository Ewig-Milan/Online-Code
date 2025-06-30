#include <bits/stdc++.h>
using namespace std;

const int N = 110, M = 20100, INF = 1e9;



int n, m, s, t;

int h[N], e[M], ca[M], ne[M], idx;
void add(int a, int b, int c) {
    e[idx] = b, ca[idx] = c, ne[idx] = h[a], h[a] = idx++;
    e[idx] = a, ca[idx] = 0, ne[idx] = h[b], h[b] = idx++;
}

int dep[N], can[N];
bool bfs() {
    memset(dep, -1, sizeof dep);
    queue<int> q;
    dep[s] = 0, q.push(s);
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

int main() {
    memset(h, -1, sizeof h);
    scanf("%d%d", &m, &n);
    s = 0, t = n + 1;
    for(int i = 1; i <= m; i++) add(s, i, 1);
    for(int i = m + 1; i <= n; i++) add(i, t, 1);
    int a, b;
    while(~scanf("%d%d", &a, &b) && a != -1) add(a, b, 1);
    printf("%d\n", dinic());
    for(int i = 0; i <= idx; i += 2) if(e[i] > m && e[i] <= n && !ca[i])
        printf("%d %d\n", e[i ^ 1], e[i]);
    return 0;
}