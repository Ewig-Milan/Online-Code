#include <bits/stdc++.h>
#define db double
using namespace std;

const int N = 200, M = 2100, INF = 1e9;
const db eps = 1e-9;

int n, m, p, S, T, max_flow;

int h[N], e[M], ne[M], idx, w[M];
db ca[M];
void add(int a, int b, int c) {
    e[idx] = b, ca[idx] = w[idx] = c, ne[idx] = h[a], h[a] = idx++;
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
            if(dep[j] == -1 && ca[i] > eps) dep[j] = dep[x] + 1, q.push(j);
        }
    }
    return false;
}

db dfs(int x, db lim) {
    if(x == T) return lim;
    db flow = 0;
    for(int &i = can[x]; ~i && flow < lim; i = ne[i]) {
        int j = e[i];
        if(dep[j] == dep[x] + 1 && ca[i] > eps) {
            db tmp = dfs(j, min(ca[i], lim - flow));
            if(!tmp) dep[j] = -1;
            else flow += tmp, ca[i] -= tmp, ca[i ^ 1] += tmp;
        }
    }
    return flow;
}

db dinic() {
    db mf = 0, tmp;
    while(bfs()) while(tmp = dfs(S, INF)) mf += tmp;
    return mf;
}

bool check(db x) {
    for(int i = 0; i < idx; i += 2) ca[i] = min(x, (db)w[i]), ca[i ^ 1] = 0;
    return max_flow - dinic() < eps;
}

int main() {
    memset(h, -1, sizeof h);
    scanf("%d%d%d", &n, &m, &p);
    S = 1, T = n;
    for(int i = 1; i <= m; i++) {
        int a, b, c; scanf("%d%d%d", &a, &b, &c);
        add(a, b, c);
    }
    max_flow = dinic();
    db l = 0, r = 10000;
    while(r - l > eps) {
        db mid = (l + r) / 2;
        if(check(mid)) r = mid;
        else l = mid;
    }
    printf("%d\n%.4lf", max_flow, l * p);
    return 0;
}