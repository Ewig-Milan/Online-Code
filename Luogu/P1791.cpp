#include <bits/stdc++.h>
#define ll long long
using namespace std;

const ll INF = 1e18;
const int N = 1100, M = 1100000;

int n, S = 0, T = N - 1;
ll E[N][N], A[N], sum;

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
    dep[S] = 0, q.push(S);
    while(!q.empty()) {
        int x = q.front();
        q.pop();
        can[x] = h[x];
        if(x == T) return 1;
        for(int i = h[x]; ~i; i = ne[i]) {
            int j = e[i];
            if(dep[j] == -1 && ca[i]) dep[j] = dep[x] + 1, q.push(j);
        }
    }
    return 0;
}
ll dfs(int x, ll lim) {
    if(x == T) return lim;
    ll flow = 0;
    for(int i = can[x]; ~i && flow < lim; i = ne[i]) {
        can[x] = i;
        int j = e[i];
        if(dep[j] == dep[x] + 1 && ca[i]) {
            ll tmp = dfs(j, min(lim - flow, ca[i]));
            if(!tmp) dep[j] = -1;
            else flow += tmp, ca[i] -= tmp, ca[i ^ 1] += tmp;
        }
    }
    return flow;
}
ll dinic() {
    ll mf = 0, tmp;
    while(bfs()) while(tmp = dfs(S, INF)) mf += tmp;
    return mf;
}

int main() {
    memset(h, -1, sizeof h);
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%lld", &A[i]), add(S, i, A[i]);
    for(int i = 1; i <= n; i++) {
        ll tmp = 0;
        for(int j = 1; j <= n; j++) scanf("%lld", &E[i][j]), tmp += E[i][j], sum += E[i][j];
        add(i, T, tmp);
    }
    for(int i = 1; i < n; i++) for(int j = i + 1; j <= n; j++) add(i, j, 2ll * E[i][j]), ca[idx - 1] = 2ll * E[i][j];
    printf("%lld", sum - dinic());
    return 0;
}