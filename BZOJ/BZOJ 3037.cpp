#include <bits/stdc++.h>
#define PI pair<int, int>
#define fi first
#define se second
using namespace std;

const int N = 1000100;

int n, ans;

int h[N], e[N << 1], ne[N << 1], idx;
void add(int a, int b) {e[idx] = b, ne[idx] = h[a], h[a] = idx++;}

bool in_cir[N], dn[N];
vector<int> cir;
vector<PI> cir_ma;

int dfn[N], low[N], cnt;
stack<int> S;
void find_cir(int x, int l) {
    S.push(x);
    dfn[x] = low[x] = ++cnt;
    for(int i = h[x]; ~i; i = ne[i]) {
        int j = e[i];
        if((i ^ 1) == l) continue;
        if(!dfn[j]) {
            find_cir(j, i);
            low[x] = min(low[x], low[j]);
        } else low[x] = min(low[x], dfn[j]);
    }
    if(dfn[x] == low[x]) {
        if(S.top() != x) cir.push_back(x), in_cir[x] = 1;
        while(S.top() != x) {
            cir.push_back(S.top());
            in_cir[S.top()] = 1;
            S.pop();
        }
        S.pop();
    }
}

PI DP(int x, int l) {
    PI res = {-1e9, 0};
    vector<PI> tmp;
    for(int i = h[x]; ~i; i = ne[i]) {
        int j = e[i];
        if(in_cir[j] || j == l) continue;
        tmp.push_back(DP(j, x));
        if(tmp.back().se >= tmp.back().fi) dn[x] = 1;
        res.se += max(tmp.back().fi, tmp.back().se);
    }
    if(dn[x]) res.fi = res.se + 1;
    else for(PI i : tmp) res.fi = max(res.fi, res.se + min(0, i.se - i.fi) + 1);
    return res;
}

PI work(bool mode) {
    PI res;
    if(mode) res = {cir_ma[0].se + 1, -1e9};
    else res = {cir_ma[0].fi, cir_ma[0].se};
    for(int i = 1; i < cir.size(); i++) {
        PI tmp;
        tmp.fi = max(cir_ma[i].fi + max(res.fi, res.se), cir_ma[i].se + res.se + 1);
        tmp.se = cir_ma[i].se + max(res.fi, res.se);
        res = tmp;
    }
    return res;
}

int cir_DP() {
    int res;
    PI t1 = work(1), t0 = work(0);
    if(dn[cir[0]]) res = max(t1.fi, t1.se);
    else res = t1.se;
    res = max(res, max(t0.fi, t0.se));
    return res;
}

int main() {
    scanf("%d", &n);
    memset(h, -1, sizeof h);
    for(int i = 1; i <= n; i++) {
        int a; scanf("%d", &a);
        if(a == i) continue;
        add(a, i); add(i, a);
    }
    for(int i = 1; i <= n; i++) {
        if(dfn[i]) continue;
        cir.resize(0); cir_ma.resize(0);
        find_cir(i, -1);
        for(int j : cir) cir_ma.push_back(DP(j, 0));
        if(cir.size() == 0) ans += max(DP(i, -1).fi, DP(i, -1).se);
        else ans += cir_DP();
    }
    printf("%d", ans);
    return 0;
}