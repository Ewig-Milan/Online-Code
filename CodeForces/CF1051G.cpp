#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 400100;

int n;
ll ANS;
bool flag[N];
int fa[N], R[N];
int find(int x) {return x == fa[x] ? x : (x = find(fa[x]));}

int root[N];
struct Seg_T {
    struct Node {
        int l, r, siz;
        ll sum, ans;
    }t[25 * N];
    int tot = 0;
    int make() {
        t[++tot] = {0, 0, 0, 0, 0};
        return tot;
    }
    void push_up(int rt) {
        int &lc = t[rt].l, &rc = t[rt].r;
        t[rt].sum = t[lc].sum + t[rc].sum;
        t[rt].siz = t[lc].siz + t[rc].siz;
        t[rt].ans = t[rc].ans + t[lc].ans + t[lc].sum * t[rc].siz;
    }
    void build(int &rt, int l, int r, int x) {
        if(!rt) rt = make();
        int &lc = t[rt].l, &rc = t[rt].r;
        if(l == r) {
            t[rt].siz = 1, t[rt].sum = x;
            return;
        }
        int mid = l + r >> 1;
        if(x <= mid) build(lc, l, mid, x);
        else build(rc, mid + 1, r, x);
        push_up(rt);
    }
    void merge(int &x, int &y) {
        if(!x || !y) {x = max(x, y); return;}
        merge(t[x].l, t[y].l);
        merge(t[x].r, t[y].r);
        push_up(x);
    }
}t;

void mix(int x, int y) {
    ANS -= t.t[root[x]].ans + t.t[root[y]].ans;
    ANS -= t.t[root[y]].sum * (y - x);
    t.merge(root[x], root[y]);
    ANS += t.t[root[x]].ans;
    fa[y] = x, R[x] = R[y];
}

int main() {
    scanf("%d", &n);
    for(int i = 0; i < N; i++) fa[i] = i;
    for(int i = 1; i <= n; i++) {
        int a, b; scanf("%d%d", &a, &b);
        if(flag[a]) {
            int tmp = find(a);
            ANS += (R[tmp] + 1ll - a) * b;
            a = R[tmp] + 1;
        }
        flag[a] = 1, R[a] = a, t.build(root[a], 1, n, b);
        if(flag[a - 1]) mix(find(a - 1), a);
        if(flag[a + 1]) mix(find(a), a + 1);
        printf("%lld\n", ANS);
    }
    return 0;
}