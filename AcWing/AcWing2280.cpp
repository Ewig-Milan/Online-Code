#include <bits/stdc++.h>
#define ll long long
#define fi first
#define se second
using namespace std;

const int N = 100100, INF = 1e9;

int n, m, k, S, T;
ll ans;
vector<pair<int, int> > p;

int h[N], ca[N], e[N], ne[N], idx, la_idx, org_idx;
void add(int a, int b, int c) {
    e[idx] = b, ca[idx] = c, ne[idx] = h[a], h[a] = idx++;
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
            if(dep[j] == -1 && ca[i]) dep[j] = dep[x] + 1, q.push(j);
        }
    }
    return false;
}

int dfs(int x, int lim) {
    if(x == T) return lim;
    int flow = 0;
    for(int & i = can[x]; ~i && flow < lim; i = ne[i]) {
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
    scanf("%d%d", &n, &m);
    S = 0, T = n + 1;
    for(int i = 1; i <= m; i++) {
        int a, b; scanf("%d%d", &a, &b);
        add(a, b, 1), ca[idx - 1] = 1;
    }
    la_idx = org_idx = idx;

    scanf("%d", &k);
    while(k--) {
        int a, b; scanf("%d%d", &a, &b);
        p.push_back({a, b});
    }

    for(int i = 0; i < 31; i++, la_idx = idx) {
        for(auto x : p) {
            if((x.se >> i) & 1) add(S, x.fi, INF);
            else add(x.fi, T, INF);
        }
        ans += (1ll << i) * dinic();

        for(int j = 0; j < org_idx; j += 2) ca[j] = 1, ca[j ^ 1] = 1;
        for(int j = la_idx; j < idx; j++) ca[j] = 0;
    }
    printf("%lld", ans);
    return 0;
}