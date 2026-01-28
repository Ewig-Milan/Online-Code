#include <bits/stdc++.h>
#define ll long long
using namespace std;

int seed = 0xABCDE;
int rnd() {return seed = seed * 97 % 11762797;}

const int N = 200100;

int n, m;

struct Node {
    int l, r, fa, siz, key;
    ll x, sum;
};
vector<Node> t;
int tot;
void cl(int a) {t.resize(a + 100), tot = 0;}
void make(int x) {t[++tot] = {0, 0, 0, 1, rnd(), x, x};}
void push_up(int rt) {
    int &lc = t[rt].l, &rc = t[rt].r;
    t[rt].sum = t[rt].x + t[lc].sum + t[rc].sum;
    t[rt].siz = t[lc].siz + t[rc].siz + 1;
    t[lc].fa = t[rc].fa = rt;
}
void split(int rt, int k, int &x, int &y) {
    int &lc = t[rt].l, &rc = t[rt].r;
    if(!rt) {x = y = 0; return;}
    if(t[lc].siz + 1 <= k) x = rt, split(rc, k - t[lc].siz - 1, rc, y);
    else y = rt, split(lc, k, x, lc);
    push_up(rt);
}
int merge(int x, int y) {
    if(!x || !y) return max(x, y);
    if(t[x].key <= t[y].key) {
        t[x].r = merge(t[x].r, y);
        push_up(x);
        return x;
    } else {
        t[y].l = merge(x, t[y].l);
        push_up(y);
        return y;
    }
}
pair<int, int> get_rtrk(int a) {
    int rk = t[t[a].l].siz + 1;
    while(t[a].fa) {
        int fa = t[a].fa;
        if(t[fa].r == a) rk += t[t[fa].l].siz + 1;
        a = fa;
    }
    return {a, rk};
}
ll query(int a, int b) {
    pair<int, int> tmp1 = get_rtrk(a), tmp2 = get_rtrk(b);
    if(tmp1.first != tmp2.first) return -1;
    int rt = tmp1.first; a = tmp1.second, b = tmp2.second;
    if(a > b) swap(a, b);
    int t1, t2, t3;
    split(rt, a - 1, t1, t2), t[t1].fa = t[t2].fa = 0;
    split(t2, b - a + 1, t2, t3), t[t2].fa = t[t3].fa = 0;
    ll res = t[t2].sum;
    t[t2 = merge(t2, t3)].fa = 0;
    t[merge(t1, t2)].fa = 0;
    return res;
}

int main() {
    scanf("%d%d", &n, &m);
    cl(n);
    for(int i = 1; i <= n; i++) {
        int a; scanf("%d", &a);
        make(a);
    }
    while(m--) {
        char mode[5]; scanf("%s", mode);
        if(mode[0] == 'M') {
            int a, b; scanf("%d%d", &a, &b);
            int t1 = get_rtrk(a).first, t2 = get_rtrk(b).first;
            if(t1 != t2) t[merge(t2, t1)].fa = 0;
        } else if(mode[0] == 'D') {
            int a, x, y; scanf("%d", &a);
            pair<int, int> tmp = get_rtrk(a);
            split(tmp.first, tmp.second - 1, x, y);
            t[x].fa = t[y].fa = 0;
        } else {
            int a, b; scanf("%d%d", &a, &b);
            printf("%lld\n", query(a, b));
        }
    }
    return 0;
}