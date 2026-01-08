#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 300100, mod = 1e9 + 7;

int anywhere_with_xh = 24/7*265;
int rnd() {return anywhere_with_xh = anywhere_with_xh * 97 % 11762797;}
int Rand(int x) {return rnd() % x + 1;}

int n, q;
int A[N];

int root;
struct Node {
    int l, r, x, siz;
    ll sum;
    int add, all;
    bool rev;
}t[N * 10];
int tot;
int make(int x) {
    t[++tot] = {0, 0, x, 1, x, 0, -1, 0};
    return tot;
}
int clone(int rt) {
    t[++tot] = t[rt];
    return tot;
}
void push_up(int rt) {
    int &lc = t[rt].l, &rc = t[rt].r;
    t[rt].siz = t[lc].siz + t[rc].siz + 1;
    t[rt].sum = (t[lc].sum + t[rc].sum + t[rt].x) % mod;
}
void D_add(int rt, ll a) {
    if(!rt) return;
    t[rt].x += a, t[rt].x %= mod;
    t[rt].sum += a * t[rt].siz % mod, t[rt].sum %= mod;
    if(t[rt].all != -1) t[rt].all += a, t[rt].all %= mod;
    else t[rt].add += a, t[rt].add %= mod;
}
void D_all(int rt, ll a) {
    if(!rt) return;
    t[rt].x = a;
    t[rt].sum = a * t[rt].siz % mod;
    t[rt].add = 0, t[rt].all = a;
}
void D_rev(int rt) {
    if(!rt) return;
    swap(t[rt].l, t[rt].r), t[rt].rev ^= 1;
}
void push_down(int rt) {
    if(!t[rt].add && t[rt].all == -1 && !t[rt].rev) return;
    int &lc = t[rt].l, &rc = t[rt].r;
    if(lc) lc = clone(lc);
    if(rc) rc = clone(rc);
    if(t[rt].add) D_add(lc, t[rt].add), D_add(rc, t[rt].add), t[rt].add = 0;
    if(t[rt].all != -1) D_all(lc, t[rt].all), D_all(rc, t[rt].all), t[rt].all = -1;
    if(t[rt].rev) D_rev(lc), D_rev(rc), t[rt].rev = 0;
}
int build(int l, int r) {
    if(l > r) return 0;
    int mid = l + r >> 1;
    int tmp = make(A[mid]);
    t[tmp].l = build(l, mid - 1), t[tmp].r = build(mid + 1, r);
    push_up(tmp);
    return tmp;
}
int idx;
void dfs(int rt) {
    if(!rt) return;
    push_down(rt);
    dfs(t[rt].l);
    A[++idx] = t[rt].x;
    dfs(t[rt].r);
}
void rebuild() {
    idx = 0, dfs(root);
    tot = 0, root = build(1, n);
}
void split(int rt, int k, int &x, int &y) {
    if(!rt) {x = y = 0; return;}
    rt = clone(rt), push_down(rt);
    int &lc = t[rt].l, &rc = t[rt].r;
    if(t[lc].siz + 1 <= k) x = rt, split(rc, k - t[lc].siz - 1, rc, y);
    else y = rt, split(lc, k, x, lc);
    push_up(rt);
}
int merge(int x, int y) {
    if(!x || !y) return max(x, y);
    if(Rand(t[x].siz + t[y].siz) <= t[x].siz) {
        x = clone(x), push_down(x);
        t[x].r = merge(t[x].r, y);
        push_up(x);
        return x;
    } else {
        y = clone(y), push_down(y);
        t[y].l = merge(x, t[y].l);
        push_up(y);
        return y;
    }
}

ll op1(int l, int r) {
    int t1, t2, t3;
    split(root, l - 1, t1, t2), split(t2, r - l + 1, t2, t3);
    ll res = t[t2].sum;
    root = merge(merge(t1, t2), t3);
    return res;
}
void op2(int l, int r, int a) {
    int t1, t2, t3;
    split(root, l - 1, t1, t2), split(t2, r - l + 1, t2, t3);
    D_all(t2, a);
    root = merge(merge(t1, t2), t3);
}
void op3(int l, int r, int a) {
    int t1, t2, t3;
    split(root, l - 1, t1, t2), split(t2, r - l + 1, t2, t3);
    D_add(t2, a);
    root = merge(merge(t1, t2), t3);
}
void op4(int l1, int r1, int l2, int r2) {
    int t1, t2, t3, t4, t5;
    if(l1 < l2) {
        split(root, l1 - 1, t1, t2), split(t2, r1 - l1 + 1, t2, t3);
        split(t3, l2 - r1 - 1, t3, t4), split(t4, r2 - l2 + 1, t4, t5);
        root = merge(merge(merge(merge(t1, t2), t3), t2), t5);
    } else {
        split(root, l2 - 1, t1, t2), split(t2, r2 - l2 + 1, t2, t3);
        split(t3, l1 - r2 - 1, t3, t4), split(t4, r1 - l1 + 1, t4, t5);
        root = merge(merge(merge(merge(t1, t4), t3), t4), t5);
    }
}
void op5(int l1, int r1, int l2, int r2) {
    int t1, t2, t3, t4, t5;
    if(l1 > l2) swap(l1, l2), swap(r1, r2);
    split(root, l1 - 1, t1, t2), split(t2, r1 - l1 + 1, t2, t3);
    split(t3, l2 - r1 - 1, t3, t4), split(t4, r2 - l2 + 1, t4, t5);
    root = merge(merge(merge(merge(t1, t4), t3), t2), t5);
}
void op6(int l, int r) {
    int t1, t2, t3;
    split(root, l - 1, t1, t2), split(t2, r - l + 1, t2, t3);
    D_rev(t2);
    root = merge(merge(t1, t2), t3);
}
void debug(int rt) {
    if(!rt) return;
    rt = clone(rt), push_down(rt);
    debug(t[rt].l);
    printf("%d ", t[rt].x);
    debug(t[rt].r);
}

int main() {
    scanf("%d%d", &n, &q);
    for(int i = 1; i <= n; i++) scanf("%d", &A[i]);
    root = build(1, n);
    ll Lans = 0;
    while(q--) {
        int mode; ll a, b; scanf("%d%lld%lld", &mode, &a, &b), a ^= Lans, b ^= Lans;
        if(mode == 4 || mode == 5) {
            ll c, d; scanf("%lld%lld", &c, &d), c ^= Lans, d ^= Lans;
            if(mode == 4) op4(a, b, c, d);
            else op5(a, b, c, d);
        } else if(mode == 2 || mode == 3) {
            ll c; scanf("%lld", &c), c ^= Lans;
            if(mode == 2) op2(a, b, c);
            else op3(a, b, c);
        } else if(mode == 6) op6(a, b);
        else printf("%lld\n", Lans = op1(a, b));
        if(tot > N * 8) rebuild();
    }
    debug(root), puts("");
    return 0;
}
/*
10 10
7 1 3 2 2 4 0 1 2 2 
4 10 10 3 3
3 4 10 5
6 6 7
6 9 10
1 10 10
5 9 10 6 7
2 8 10 0
5 4 4 5 5
5 2 4 8 10
3 3 9 0

1 求和
2 赋值
3 加
4 复制
5 交换
6 rev
*/