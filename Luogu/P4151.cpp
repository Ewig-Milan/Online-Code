#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int N = 50100, M = N << 2;

int n, m;
ll ans, xr[N], d[65];
bool vis[N];

int h[N], e[M], ne[M], idx;
ll v[M];
void add(int a, int b, ll c) {
    e[idx] = b, v[idx] = c, ne[idx] = h[a], h[a] = idx++;
    e[idx] = a, v[idx] = c, ne[idx] = h[b], h[b] = idx++;
}

void ins(ll x) {
    for(int i = 62; i >= 0; i--) if((x >> i) & 1)
        if(d[i]) x ^= d[i];
        else {
            d[i] = x;
            return;
        }
}

void dfs(int x, int l, ll res) {
    vis[x] = true, xr[x] = res;
    for(int i = h[x]; ~i; i = ne[i]) {
        int j = e[i];
        if(j == l) continue;
        if(!vis[j]) dfs(j, x, res ^ v[i]);
        else ins(res ^ v[i] ^ xr[j]);
    }
}

int main() {
    memset(h, -1, sizeof h);
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; i++) {
        int a, b; ll c; scanf("%d%d%lld", &a, &b, &c);
        add(a, b, c);
    }
    dfs(1, 0, 0ll), ans = xr[n];
    for(int i = 62; i >= 0; i--) ans ^=(ans ^ d[i]) > ans ? d[i] : 0;
    printf("%lld\n", ans);
    return 0;
}