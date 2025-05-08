#include <bits/stdc++.h>
using namespace std;

const int N= 100100, M = 200100;

int n, m, w[N], ans[N], ans_temp;

int siz[N], ma_s[N], cnt[N], L[N], R[N], id[N], cc;

int h[N], e[M], ne[M], idx;
void add(int a, int b) {
    e[idx] = b, ne[idx] =  h[a], h[a] = idx++;
}

void dfs_pre(int x, int l) {
    siz[x] = 1, L[x] = ++cc, id[cc] = x;
    for(int i = h[x]; ~i; i = ne[i]) {
        int j = e[i];
        if(j == l) continue;
        dfs_pre(j, x);
        siz[x] += siz[j];
        if(siz[j] > siz[ma_s[x]]) ma_s[x] = j;
    }
    R[x] = cc;
}

void dfs(int x, int l, bool keep) {
    for(int i = h[x]; ~i; i = ne[i]) {
        int j = e[i];
        if(j == l || j == ma_s[x]) continue;
        dfs(j, x, 0);
    }
    if(ma_s[x]) dfs(ma_s[x], x, 1);
    if(!cnt[w[x]]) ans_temp++, cnt[w[x]]++;
    for(int i = h[x]; ~i; i = ne[i]) {
        int j = e[i];
        if(j == l || j == ma_s[x]) continue;
        for(int k = L[j]; k <= R[j]; k++) if(!cnt[w[id[k]]]) ans_temp++, cnt[w[id[k]]]++;
    }
    ans[x] = ans_temp;
    if(!keep) for(int i = L[x]; i <= R[x]; i++) if(cnt[w[id[i]]] - 1 == 0) ans_temp--, cnt[w[id[i]]]--;
}

int main() {
    scanf("%d", &n);
    memset(h, -1,  sizeof(h));
    for(int i = 1; i < n; i++) {
        int a, b; scanf("%d%d", &a, &b);
        add(a, b); add(b, a);
    }
    for(int i = 1; i <= n; i++) scanf("%d", &w[i]);
    scanf("%d", &m);
    dfs_pre(1, 0);
    dfs(1, 0, 1);
    while(m--) {
        int a; scanf("%d", &a);
        printf("%d\n", ans[a]);
    }
    return 0;
}