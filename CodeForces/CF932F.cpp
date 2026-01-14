#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 200100, M = 1000100/*值域*/, O = 1e5 + 10;


int n;
int A[N], B[N];
ll f[N];

int h[N], e[N << 1], ne[N << 1], idx, d[N];
void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++, d[a]++;
    e[idx] = a, ne[idx] = h[b], h[b] = idx++, d[b]++;
}

int root[N];
struct Line {ll k, b;};
bool cmp(const Line &a, const Line &b, ll x) { // a 优先级更高
    x -= O;
    return a.k * x + a.b < b.k * x + b.b;
}

struct Node {
    Line L;
    int lc, rc;
}t[M << 2];
int tot;
int make(Line x) {
    t[++tot] = {x, 0, 0};
    return tot;
}
void Add(int &rt, int l, int r, Line x) {
    if(!rt) {rt = make(x); return;}
    int mid = l + r >> 1;
    if(cmp(x, t[rt].L, mid)) swap(t[rt].L, x);
    if(l == r) return;
    if(cmp(x, t[rt].L, l)) Add(t[rt].lc, l, mid, x);
    if(cmp(x, t[rt].L, r)) Add(t[rt].rc, mid + 1, r, x);  
}
int merge(int x, int y, int l, int r) {
    if(!x || !y) return max(x, y);
    Add(x, l, r, t[y].L);
    int mid = l + r >> 1;
    t[x].lc = merge(t[x].lc, t[y].lc, l, mid);
    t[x].rc = merge(t[x].rc, t[y].rc, mid + 1, r);
    return x;
}
ll query(int rt, int l, int r, ll x) {
    if(!rt) return 1e15;
    int mid = l + r >> 1;
    ll ans;
    if(x <= mid) ans = query(t[rt].lc, l, mid, x);
    else ans = query(t[rt].rc, mid + 1, r, x);
    return min(ans, t[rt].L.k * (x - O) + t[rt].L.b);
}

void dfs(int x, int l) {
    if(x != 1 && d[x] == 1) {
        f[x] = 0, root[x] = make({B[x], f[x]});
        return;
    }
    for(int i = h[x]; ~i; i = ne[i]) {
        int j = e[i];
        if(j == l) continue;
        dfs(j, x);
        root[x] = merge(root[x], root[j], 1, N - 1);
    }
    f[x] = query(root[x], 1, N - 1, A[x] + O);
    Add(root[x], 1, N - 1, {B[x], f[x]});
}

int main() {
    memset(h, -1, sizeof h);
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%d", &A[i]);
    for(int i = 1; i <= n; i++) scanf("%d", &B[i]);
    for(int i = 1; i < n; i++) {
        int a, b; scanf("%d%d", &a, &b);
        add(a, b);
    }
    dfs(1, 0);
    for(int i = 1; i <= n; i++) printf("%lld ", f[i]);
    return 0;
}