#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 200100;

int T, n;
ll f[N], A[N];

int h[N], e[N << 1], v[N << 1], ne[N << 1], idx, d[N];
void add(int a, int b, int c) {
    e[idx] = b, v[idx] = c, ne[idx] = h[a], h[a] = idx++;
    e[idx] = a, v[idx] = c, ne[idx] = h[b], h[b] = idx++;
}

ll dfs(int x, int l) {
    if(d[x] == 1) return 1e13;
    for(int i = h[x]; ~i; i = ne[i]) {
        int j = e[i];
        if(j == l) continue;
        f[x] += min((ll)v[i], dfs(j, x));
    }
    return f[x];
}

void DP(int x, int l) {
    for(int i = h[x]; ~i; i = ne[i]) {
        int j = e[i];
        if(j == l) continue;
        A[j] = f[j] + min((ll)v[i], A[x] - min((ll)v[i], f[j]));
        DP(j, x);
    }
}

int main() {
    scanf("%d", &T);
    while(T--) {
        idx = 0;
        memset(A, 0, sizeof A);
        memset(f, 0, sizeof f);
        memset(h, -1, sizeof h);
        memset(d, 0, sizeof d);
        
        scanf("%d", &n);
        for(int i = 1; i < n; i++) {
            int a, b, c; scanf("%d%d%d", &a, &b, &c);
            add(a, b, c); d[a]++, d[b]++;
        }
        int rt;
        for(int i = 1; i <= n; i++) if(d[i] != 1) {rt = i; break;}
        dfs(rt, 0);
        A[rt] = f[rt];
        DP(rt, 0);
        ll ans = 0;
        for(int i = 1; i <= n; i++) ans = max(ans, A[i]);
        printf("%lld\n", ans);
    }
    return 0;
}