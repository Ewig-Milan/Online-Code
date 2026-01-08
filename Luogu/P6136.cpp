#include <bits/stdc++.h>
using namespace std;

const int N = 100100;

int seed = 0xABC3DD;
int rnd() {return seed = seed * 3 % 11762797;}

int n, m;
int A[N];

int root;
struct Node {int l, r, x, key, siz;} t[N * 11];
int tot;
int make(int x) {
    t[++tot] = {0, 0, x, rnd(), 1};
    return tot;
}
void push_up(int rt) {
    int &lc = t[rt].l, &rc = t[rt].r;
    t[rt].siz = t[lc].siz + t[rc].siz + 1;
}
int build() {
    deque<int> q;
    sort(A + 1, A + n + 1);
    for(int i = 1; i <= n; i++) {
        int tmp = make(A[i]), last = 0;
        while(!q.empty() && t[q.back()].key > t[tmp].key) push_up(last = q.back()), q.pop_back();
        if(!q.empty()) t[q.back()].r = tmp;
        t[tmp].l = last, q.push_back(tmp);
    }
    int rt = q.front();
    while(!q.empty()) push_up(q.back()), q.pop_back();
    return rt;
}
void split(int rt, int k, int &x, int &y) {
    int &lc = t[rt].l, &rc = t[rt].r;
    if(!rt) {x = y = 0; return;}
    // push_down(rt);
    if(t[rt].x <= k) x = rt, split(rc, k, rc, y);
    else y = rt, split(lc, k, x, lc);
    push_up(rt);
}
int merge(int x, int y) {
    if(!x || !y) return max(x, y);
    if(t[x].key <= t[y].key) {
        // push_down(x);
        t[x].r = merge(t[x].r, y);
        push_up(x);
        return x;
    } else {
        // push_down(y);
        t[y].l = merge(x, t[y].l);
        push_up(y);
        return y;
    }
}
int find(int rt, int k) {
    int &lc = t[rt].l, &rc = t[rt].r;
    if(t[lc].siz + 1 == k) return rt;
    // push_down(rt);
    if(t[lc].siz + 1 > k) return find(lc, k);
    return find(rc, k - t[lc].siz - 1);
}

void ins(int x) {
    int t1, t2;
    split(root, x, t1, t2);
    root = merge(merge(t1, make(x)), t2);
}
void del(int x) {
    int t1, t2, t3;
    split(root, x - 1, t1, t3);
    split(t3, x, t2, t3);
    t2 = merge(t[t2].l, t[t2].r);
    root = merge(merge(t1, t2), t3);
}
int get_rk(int x) {
    int t1, t2;
    split(root, x - 1, t1, t2);
    int tmp = t[t1].siz + 1;
    root = merge(t1, t2);
    return tmp;
}
int get_kth(int k) {return t[find(root, k)].x;}
int pre(int x) {
    int t1, t2;
    split(root, x - 1, t1, t2);
    int tmp = t[find(t1, t[t1].siz)].x;
    root = merge(t1, t2);
    return tmp;
}
int nxt(int x) {
    int t1, t2;
    split(root, x, t1, t2);
    int tmp = t[find(t2, 1)].x;
    root = merge(t1, t2);
    return tmp;
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++) scanf("%d", &A[i]);
    root = build();
    int Lans = 0, ans = 0;
    while(m--) {
        int mode, a; scanf("%d%d", &mode, &a);
        a ^= Lans;
        if(mode == 1) ins(a);
        if(mode == 2) del(a);
        if(mode == 3) Lans = get_rk(a);
        if(mode == 4) Lans = get_kth(a);
        if(mode == 5) Lans = pre(a);
        if(mode == 6) Lans = nxt(a);
        if(mode > 2) ans ^= Lans; // printf("%d\n", Lans);
    }
    printf("%d", ans);
    return 0;
}