#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 300, M = 10100;
const ll INF = 1e12;

int n, m, s, t;

int h[N], e[M], ne[M], idx;
ll ca[M];
void add(int a, int b, ll c) {
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

ll dfs(int x, ll lim) {
    if(x == t) return lim;
    ll flow = 0;
    for(int i = can[x]; ~i && flow < lim; i = ne[i]) {
        can[x] = i;
        int j = e[i];
        if(dep[j] == dep[x] + 1 && ca[i]) {
            ll tmp = dfs(j, min(ca[i], lim - flow));
            if(!tmp) dep[j] = -1;
            else flow += tmp, ca[i] -= tmp, ca[i ^ 1] += tmp;
        }
    }
    return flow;
}

ll dinic() {
    ll mf = 0, tmp;
    while(bfs()) while(tmp = dfs(s, INF)) mf += tmp;
    return mf;
}

int main() {
    memset(h, -1, sizeof h);
    scanf("%d%d%d%d", &n, &m, &s, &t);
    for(int i = 1; i <= m; i++) {
        int a, b; ll c; scanf("%d%d%lld", &a, &b, &c);
        add(a, b, c);
    }
    printf("%lld", dinic());
    return 0;
}