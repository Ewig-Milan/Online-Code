#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 50100, M = 100100, mod = 201314;

int n, m, ans[N];
struct Ques {int qid, k, x;};
vector<Ques> Q[N];

int h[N], e[M], ne[M], idx;
void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
    e[idx] = a, ne[idx] = h[b], h[b] = idx++;
}

int dep[N], siz[N], ma_s[N], tp[N], fa[N];
int L[N], dfn[N], cnt;

void dfs_pre(int x, int l) {
    fa[x] = l, dep[x] = dep[l] + 1, siz[x] = 1;
    for(int i = h[x]; ~i; i = ne[i]) {
        int j = e[i];
        if(j == l) continue;
        dfs_pre(j, x);
        siz[x] += siz[j];
        if(siz[ma_s[x]] < siz[j]) ma_s[x] = j;
    }
}

void dfs_top(int x, int l, int top) {
    L[x] = ++cnt, dfn[cnt] = x, tp[x] = top;
    if(ma_s[x]) dfs_top(ma_s[x], x, top);
    for(int i = h[x]; ~i; i = ne[i]) {
        int j = e[i];
        if(j == l || j == ma_s[x]) continue;
        dfs_top(j, x, j);
    }
}

struct TR {
    vector<int> sum, ly;
    void cl(int n) {
        sum.resize(0), sum.resize(n << 2);
        ly.resize(0), ly.resize(n << 2);
    }
    void push_up(int rt) {sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];}
    void push_down(int rt, int l, int r) {
        if(!ly[rt]) return;
        int mid = l + r >> 1;
        ly[rt << 1] += ly[rt];
        ly[rt << 1 | 1] += ly[rt];
        sum[rt << 1] += (mid - l + 1) * ly[rt];
        sum[rt << 1 | 1] += (r - mid) * ly[rt];
        ly[rt] = 0;
    }
    void modify(int rt, int l, int r, int ql, int qr, int x) {
        if(ql <= l && qr >= r) {
            sum[rt] += x * (r - l + 1), ly[rt] += x;
            return;
        }
        push_down(rt, l, r);
        int mid = l + r >> 1;
        if(ql <= mid) modify(rt << 1, l, mid, ql, qr, x);
        if(qr > mid) modify(rt << 1 | 1, mid + 1, r, ql, qr, x);
        push_up(rt);
    }
    int query(int rt, int l, int r, int ql, int qr, int x) {
        if(ql <= l && qr >= r) return sum[rt];
        push_down(rt, l, r);
        int mid = l + r >> 1;
        int res = 0;
        if(ql <= mid) res += query(rt << 1, l, mid, ql, qr, x);
        if(qr > mid) res += query(rt << 1 | 1, mid + 1, r, ql, qr, x);
        return res;
    }
}t;

void modify(int x, int y) {
    while(tp[x] != tp[y]) {
        if(dep[tp[x]] < dep[tp[y]]) swap(x, y);
        t.modify(1, 1, n, L[tp[x]], L[x], 1);
        x = fa[tp[x]];
    }
    if(dep[x] < dep[y]) swap(x, y);
    t.modify(1, 1, n, L[y], L[x], 1);
}

int query(int x, int y) {
    int res = 0;
    while(tp[x] != tp[y]) {
        if(dep[tp[x]] < dep[tp[y]]) swap(x, y);
        res += t.query(1, 1, n, L[tp[x]], L[x], 1);
        x = fa[tp[x]];
    }
    if(dep[x] < dep[y]) swap(x, y);
    res += t.query(1, 1, n, L[y], L[x], 1);
    return res;
}

signed main() {
    memset(h, -1, sizeof h);
    scanf("%lld%lld", &n, &m);
    t.cl(n);
    for(int i = 2; i <= n; i++) {
        int a; scanf("%lld", &a);
        add(a + 1, i);
    }
    dep[0] = -1;
    dfs_pre(1, 0);
    dfs_top(1, 0, 1);
    for(int i = 1; i <= m; i++) {
        int a, b, c; scanf("%lld%lld%lld", &a, &b, &c);
        Q[a].push_back({i, -1, c + 1}), Q[b + 1].push_back({i, 1, c + 1});
    }
    for(int i = 1; i <= n; i++) {
        modify(1, i);
        for(auto q : Q[i]) ans[q.qid] += q.k * query(1, q.x), ans[q.qid] %= mod;
    }
    for(int i = 1; i <= m; i++) printf("%lld\n", (ans[i] + mod) % mod);
    return 0;
}