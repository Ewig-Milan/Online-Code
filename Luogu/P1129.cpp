#include <bits/stdc++.h>
using namespace std;

const int N = 410, M = 80100, INF = 1e8;

int T, n;
int s, t;

int h[N], e[M], ne[M], ca[M], idx;

void add(int a, int b, int c) {
    e[idx] = b, ca[idx] = c, ne[idx] = h[a], h[a] = idx++;
    e[idx] = a, ca[idx] = 0, ne[idx] = h[b], h[b] = idx++;
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
    scanf("%d", &T);
    while(T--) {
        memset(h, -1, sizeof h), idx = 0;
        scanf("%d", &n);
        s = 0, t = n << 1 | 1;
        for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++) {
            int a; scanf("%d", &a);
            if(a) add(i, j + n, 1);
        }
        for(int i = 1; i <= n; i++) add(s, i, 1);
        for(int i = n + 1; i <= (n << 1); i++) add(i, t, 1);
        printf("%s\n", dinic() >= n ? "Yes" : "No");
    }
    return 0;
}