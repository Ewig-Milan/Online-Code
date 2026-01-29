#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

const int N = 100100;

int n, m;
vector<pair<int, int>> Q[N];
int ans[N];

int h[N], ne[N << 1], e[N << 1], idx;
void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
    e[idx] = a, ne[idx] = h[b], h[b] = idx++;
}

int dep[N], fa[18][N];
void pre(int x, int l) {
    fa[0][x] = l, dep[x] = dep[l] + 1;
    for(int i = 1; i < 18; i++) fa[i][x] = fa[i - 1][fa[i - 1][x]];
    for(int i = h[x]; ~i; i = ne[i]) {
        int j = e[i];
        if(j == l) continue;
        pre(j, x);
    }
}
int LCA(int x, int y) {
    if(dep[x] < dep[y]) swap(x, y);
    for(int i = 17; i >= 0; i--) 
        if(dep[fa[i][x]] >= dep[y]) x = fa[i][x];
    if(x == y) return y;
    for(int i = 17; i >= 0; i--) if(fa[i][x] != fa[i][y])
        x = fa[i][x], y = fa[i][y];
    return fa[0][y];
}

int root[N];
struct Seg_T {
    struct Node {
        int lc, rc, ma, ma_id;
    }t[N * 100];
    int tot;
    int make() {
        t[++tot] = {0, 0, 0, 0};
        return tot;
    }
    void push_up(int rt) {
        int &lc = t[rt].lc, &rc = t[rt].rc;
        if(t[lc].ma >= t[rc].ma) t[rt].ma = t[lc].ma, t[rt].ma_id = t[lc].ma_id;
        else t[rt].ma = t[rc].ma, t[rt].ma_id = t[rc].ma_id;
    }
    void modify(int rt, int l, int r, int a, int x) {
        if(l == r) {
            t[rt].ma += x, t[rt].ma_id = a;
            return;
        }
        int &lc = t[rt].lc, &rc = t[rt].rc;
        if(!lc) lc = make();
        if(!rc) rc = make();
        int mid = l + r >> 1;
        if(a <= mid) modify(lc, l, mid, a, x);
        else modify(rc, mid + 1, r, a, x);
        push_up(rt);
    }
    int merge(int t1, int t2, int l, int r) {
        if(!t1 || !t2) return max(t1, t2);
        if(l == r) {t[t1].ma += t[t2].ma, t[t1].ma_id = l; return t1;}
        int mid = l + r >> 1;
        t[t1].lc = merge(t[t1].lc, t[t2].lc, l, mid);
        t[t1].rc = merge(t[t1].rc, t[t2].rc, mid + 1, r);
        push_up(t1);
        return t1;
    }
}t;

void dfs(int x, int l) {
    root[x] = t.make();
    for(int i = h[x]; ~i; i = ne[i]) {
        int j = e[i];
        if(j == l) continue;
        dfs(j, x);
        root[x] = t.merge(root[x], root[j], 1, 1e5);
    }
    for(auto i : Q[x]) t.modify(root[x], 1, 1e5, i.fi, i.se);
    ans[x] = t.t[root[x]].ma ? t.t[root[x]].ma_id : 0;
}

int main() {
    memset(h, -1, sizeof h);
    scanf("%d%d", &n, &m);
    for(int i = 1; i < n; i++) {
        int a, b; scanf("%d%d", &a, &b);
        add(a, b);
    }
    pre(1, 0);
    while(m--) {
        int a, b, c; scanf("%d%d%d", &a, &b, &c);
        int lca = LCA(a, b);
        Q[a].push_back({c, 1}), Q[b].push_back({c, 1});
        Q[lca].push_back({c, -1}), Q[fa[0][lca]].push_back({c, -1});
    }
    dfs(1, 0);
    for(int i = 1; i <= n; i++) printf("%d\n", ans[i]);
    return 0;
}