#include <bits/stdc++.h>
using namespace std;

const int N = 80100, M = 320100;

int n, m, t, w[N], last, Nn;

int h[N], e[M], ne[M], idx;
void add(int a, int b) {e[idx] = b, ne[idx] = h[a], h[a] = idx++;}

int rt[N];

struct TR {
    struct Node {int l, r, sum;};
    vector<Node> t;
    int tot = 0;

    void cl() {
        t.resize(0); t.resize(80000 * 500);
        tot = 0;
    }
    int make(int rt) {
        t[++tot] = t[rt];
        return tot;
    }
    void push_up(int rt) {
        int &lc = t[rt].l, &rc = t[rt].r;
        t[rt].sum = t[lc].sum + t[rc].sum;
    }
    void build(int &rt, int l, int r) {
        rt = ++tot;
        int &lc = t[rt].l, &rc = t[rt].r;
        if(l == r) return;
        int mid = l + r >> 1;
        build(lc, l, mid);
        build(rc, mid + 1, r);
    }
    int modify(int rt, int l, int r, int n) {
        int &lc = t[rt].l, &rc = t[rt].r, tmp = make(rt);
        if(l == r) {
            t[tmp].sum++;
            return tmp;
        }
        int mid = l + r >> 1;
        if(n <= mid) t[tmp].l = modify(lc, l, mid, n);
        else t[tmp].r = modify(rc, mid + 1, r, n);
        push_up(tmp);
        return tmp;
    }
    int find(int v1, int v2, int v3, int v4, int l, int r, int k) {
        if(l == r) return l;
        int &lc1 = t[v1].l, &rc1 = t[v1].r;
        int &lc2 = t[v2].l, &rc2 = t[v2].r;
        int &lc3 = t[v3].l, &rc3 = t[v3].r;
        int &lc4 = t[v4].l, &rc4 = t[v4].r;
        int tmp = t[lc1].sum + t[lc2].sum - t[lc3].sum - t[lc4].sum;
        int mid = l + r >> 1;
        if(tmp >= k) return find(lc1, lc2, lc3, lc4, l, mid, k);
        else return find(rc1, rc2, rc3, rc4, mid + 1, r, k - tmp);
    }
}tr;

int fa[N][20], dep[N], siz[N];

void dfs(int x, int l) {
    rt[x] = tr.modify(rt[l], 1, Nn, w[x]);
    fa[x][0] = l, dep[x] = dep[l] + 1, siz[x] = 1;
    for(int i = 1; i <= 19; i++) fa[x][i] = fa[fa[x][i - 1]][i - 1];
    for(int i = h[x]; ~i; i = ne[i]) {
        int j = e[i];
        if(j == l) continue;
        dfs(j, x);
        siz[x] += siz[j];
    }
}

int LCA(int x, int y) {
    if(dep[x] < dep[y]) swap(x, y);
    for(int i = 19; i >= 0; i--)
        if(dep[fa[x][i]] >= dep[y])
            x = fa[x][i];
    if(x == y) return y;
    for(int i = 19; i >= 0; i--)
        if(fa[x][i] != fa[y][i])
            x = fa[x][i], y = fa[y][i];
    return fa[y][0];
}

int f[N];
int find(int x) {
    if(f[x] != x) f[x] = find(f[x]);
    return f[x];
}

int query(int a, int b, int k) {
    int lca = LCA(a, b);
    return tr.find(rt[a], rt[b], rt[lca], rt[fa[lca][0]], 1, Nn, k);
}

void link(int x, int y) {
    int fx = find(x), fy = find(y);
    if(fx == fy) return;
    if(siz[fx] < siz[fy]) swap(x, y), swap(fx, fy);
    siz[fx] += siz[fy];
    f[fy] = fx;
    dfs(y, x);
    add(x, y); add(y, x);
}

int main() {
    int nothing; scanf("%d", &nothing);
    memset(h, -1, sizeof(h));
    for(int i = 1; i < N; i++) f[i] = i;
    scanf("%d%d%d", &n, &m, &t);
    vector<int> dc;
    for(int i = 1; i <= n; i++) scanf("%d", &w[i]), dc.push_back(w[i]);
    sort(dc.begin(), dc.end());
    Nn = unique(dc.begin(), dc.end()) - dc.begin();
    dc.resize(Nn);
    for(int i = 1; i <= n; i++)
        w[i] = lower_bound(dc.begin(), dc.end(), w[i]) - dc.begin() + 1;
    tr.cl();
    tr.build(rt[0], 1, Nn);
    for(int i = 1; i <= m; i++) {
        int a, b; scanf("%d%d", &a, &b);
        add(a, b); add(b, a);
        f[find(a)] = find(b);
    }
    for(int i = 1; i <= n; i++)
        if(f[i] == i) dfs(i, 0);
    while(t--) {
        char mode[1]; scanf("%s", mode);
        if(mode[0] == 'Q') {
            int x, y, k; scanf("%d%d%d", &x, &y, &k);
            last = dc[query(x ^ last, y ^ last, k ^ last) - 1];
            printf("%d\n", last);
        } else {
            int x, y; scanf("%d%d", &x, &y);
            link(x ^ last, y ^ last);
        }
    }
    return 0;
}
