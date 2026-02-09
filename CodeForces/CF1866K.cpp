#include <bits/stdc++.h>
#define ll long long
#define fi first
#define se second
using namespace std;

const int N = 100100;

int n, q;
ll D;

int h[N], e[N << 1], ne[N << 1], idx;
ll v[N << 1];
void add(int a, int b, ll c) {
    e[idx] = b, v[idx] = c, ne[idx] = h[a], h[a] = idx++;
    e[idx] = a, v[idx] = c, ne[idx] = h[b], h[b] = idx++;
}

struct Line {ll k, b; int id;};
vector<Line> V[N];
int cnt[N];
bool cmp(Line a, Line b, ll x) {return a.k * x + a.b > b.k * x + b.b;}

ll f[N][2]; // 0最大 1次大
void dfs1(int x, int l) {
    for(int i = h[x]; ~i; i = ne[i]) {
        if((i ^ 1) == l) continue;
        int j = e[i];
        dfs1(j, i);
        if(f[j][0] + v[i] >= f[x][0]) f[x][1] = f[x][0], f[x][0] = f[j][0] + v[i];
        else f[x][1] = max(f[x][1], f[j][0] + v[i]);
    }
    if(l != -1) V[e[l ^ 1]].push_back({v[l], f[x][0], ++cnt[e[l ^ 1]]});
    D = max(D, f[x][0] + f[x][1]);
}
void dfs2(int x, int l, ll ma) {
    for(int i = h[x]; ~i; i = ne[i]) {
        int j = e[i];
        if(j == l) continue;
        if(f[j][0] + v[i] == f[x][0]) {
            ll tmp = max(ma, f[x][1]);
            V[j].push_back({v[i], tmp, ++cnt[j]});
            dfs2(j, x, tmp + v[i]);
        } else {
            ll tmp = max(ma, f[x][0]);
            V[j].push_back({v[i], tmp, ++cnt[j]});
            dfs2(j, x, tmp + v[i]);
        }
    }
}

vector<int> pre[N], suf[N];

struct Node {
    Line L;
    int lc, rc;
}t[N * 150];
int tot;
int make(Line x) {
    t[++tot] = {x, 0, 0};
    return tot;
}
int clone(int rt) {
    t[++tot] = t[rt];
    return tot;
}
int Add(int rt, int l, int r, Line x) {
    if(!rt) return make(x);
    rt = clone(rt);
    int mid = l + r >> 1;
    if(cmp(x, t[rt].L, mid)) swap(x, t[rt].L);
    if(l == r) return rt;
    if(cmp(x, t[rt].L, l)) t[rt].lc = Add(t[rt].lc, l, mid, x);
    if(cmp(x, t[rt].L, r)) t[rt].rc = Add(t[rt].rc, mid + 1, r, x);
    return rt;
}
pair<ll, int> query(int rt, int l, int r, ll x) {
    if(!rt) return {0, 0};
    int mid = l + r >> 1;
    pair<ll, int> ans = {0, 0};
    if(x <= mid) ans = query(t[rt].lc, l, mid, x);
    else ans = query(t[rt].rc, mid + 1, r, x);
    if(t[rt].L.k * x + t[rt].L.b >= ans.fi) ans = {t[rt].L.k * x + t[rt].L.b, t[rt].L.id};
    return ans;
}

int main() {
    memset(h, -1, sizeof h);
    scanf("%d", &n);
    for(int i = 1; i < n; i++) {
        int a, b; ll c; scanf("%d%d%lld", &a, &b, &c);
        add(a, b, c);
    }
    dfs1(1, -1), dfs2(1, 0, 0);
    for(int i = 1; i <= n; i++) {
        pre[i].push_back(0), suf[i].push_back(0);
        for(Line &x : V[i]) pre[i].push_back(Add(pre[i].back(), 1, 1e9, x));
        reverse(V[i].begin(), V[i].end());
        for(Line &x : V[i]) suf[i].push_back(Add(suf[i].back(), 1, 1e9, x));
    }
    scanf("%d", &q);
    while(q--) {
        int a; ll b; scanf("%d%lld", &a, &b);
        auto ans = query(pre[a].back(), 1, 1e9, b);
        auto a1 = query(pre[a][ans.se - 1], 1, 1e9, b);
        auto a2 = query(suf[a][cnt[a] - ans.se], 1, 1e9, b);
        printf("%lld\n", max(ans.fi + max(a1.fi, a2.fi), D));
    }
    return 0;
}