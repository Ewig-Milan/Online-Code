#include <bits/stdc++.h>
using namespace std;

const int N = 10100, M = 60500, INF = 1e8;

int n, m, s = 0, t = N - 1;
int A[N], B[N], mi[N];
vector<pair<int, int>> E;

int pidx;
int id[110][110];

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
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%d%d", &A[i], &B[i]), mi[i] = A[i];
    scanf("%d", &m);
    for(int i = 1; i <= m; i++) {
        int a, b; scanf("%d%d", &a, &b);
        E.push_back({a, b});
        mi[a] = max(mi[a], min(B[a], B[b]));
        mi[b] = max(mi[b], min(B[a], B[b]));
    }
    for(int i = 1; i <= n; i++) for(int j = mi[i]; j <= 100; j++)
        id[i][j] = ++pidx;

    for(int i = 1; i <= n; i++) {
        int nw = id[i][mi[i]];
        add(s, nw, max(0, B[i] - mi[i]));
        add(nw, t, 0);
        while(++nw <= id[i][100]) add(nw, nw - 1, INF), add(nw, t, 1);
    }
    for(pair<int, int> x : E) {
        int a = x.first, b = x.second;
        if(B[a] <= B[b]) swap(a, b);
        add(id[a][mi[a]], id[b][B[a]], INF);
    }
    int res = 0;
    for(int i = 1; i <= n; i++) res += mi[i] - A[i];
    printf("%d", res + dinic());
    return 0;
}