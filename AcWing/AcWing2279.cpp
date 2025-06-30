#include <bits/stdc++.h>
#define db double
using namespace std;

const int N = 5100;
const db INF = 1e9;

int n, m, S, T;

int h[N], e[N], ne[N], w[N], idx;
db ca[N];
void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
    e[idx] = a, ne[idx] = h[b], h[b] = idx++;
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
            if(dep[j] == -1 && ca[i] > 1e-6) dep[j] = dep[x] + 1, q.push(j);
        }
    }
    return false;
}

db dfs(int x, db lim) {
    if(x == T) return lim;
    db flow = 0;
    for(int & i = can[x]; ~i && flow < lim; i = ne[i]) {
        int j = e[i];
        if(dep[j] == dep[x] + 1 && ca[i] > 1e-6) {
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
    db ans = 0;
    for(int i = 0; i < idx; i += 2) {
        if(w[i] - x <= 0) ans += (db)w[i] - x, ca[i] = 0, ca[i ^ 1] = 0;
        else ca[i] = ca[i ^ 1] = (db)w[i] - x;
    }
    ans += dinic();
    return ans <= 0;
}

int main() {
    memset(h, -1, sizeof h);
    scanf("%d%d%d%d", &n, &m, &S, &T);
    for(int i = 1; i <= m; i++) {
        int a, b, c; scanf("%d%d%d", &a, &b, &c);
        w[idx] = c, add(a, b);
    }
    db l = 0, r = 1e7;
    while(r - l > 1e-4) {
        db mid = (l + r) / 2;
        if(check(mid)) r = mid;
        else l = mid;
    }
    printf("%.2lf\n", l);
    return 0;
}