#include <bits/stdc++.h>
using namespace std;

const int N = 1100, M = 102100, INF = 1e8;

int n1, n2, m, s, t;

int h[N], e[M], ne[M], ca[M], idx;
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

int main() {
    memset(h, -1, sizeof h);
    scanf("%d%d%d", &n1, &n2, &m);
    s = 0, t = n1 + n2 + 1;
    for(int i = 1; i <= n1; i++) add(s, i, 1);
    for(int i = 1; i <= n2; i++) add(i + n1, t, 1);
    for(int i = 1; i <= m; i++) {
        int a, b; scanf("%d%d", &a, &b);
        add(a, b + n1, 1);
    }
    printf("%d\n", dinic());
    for(int x = 1; x <= n1; x++) {
        int tmp = 0;
        for(int i = h[x]; ~i; i = ne[i]) {
            int j = e[i];
            if(j == s) continue;
            // if(!ca[i]) printf("%d %d\n", x, j - n1);
        }
    }
    return 0;
}