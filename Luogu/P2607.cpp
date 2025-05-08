//
// 美化
//
#include <bits/stdc++.h>
#define ll long long
#define PLL pair<ll, ll>
#define fi first
#define se second
using namespace std;

const int N = 1000100;

int n, w[N];
ll ans;

int h[N], e[N << 1], ne[N << 1], idx;
void add(int a, int b) {e[idx] = b, ne[idx] = h[a], h[a] = idx++;}

vector<int> cir;
vector<PLL> cir_ans;
bool in_cir[N];
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
        if(S.top() != x) cir.push_back(x), in_cir[x] = true;
        while(S.top() != x) {
            cir.push_back(S.top());
            in_cir[S.top()] = true;
            S.pop();
        }
        S.pop();
    }
}

PLL DP(int x, int l) {
    PLL res = {w[x], 0};
    for(int i = h[x]; ~i; i = ne[i]) {
        int j = e[i];
        if(in_cir[j] || j == l) continue;
        PLL tmp = DP(j, x);
        res.fi += tmp.se, res.se += max(tmp.fi, tmp.se);
    }
    return res;
}

PLL work(bool mode) {
    PLL res;
    if(mode) res = {-1e9, cir_ans[1].se + cir_ans[0].fi};
    else res = {cir_ans[0].se + cir_ans[1].fi, cir_ans[0].se + cir_ans[1].se};
    for(int i = 2; i < cir_ans.size(); i++) {
        PLL tmp = {cir_ans[i].fi + res.se, cir_ans[i].se + max(res.fi, res.se)};
        res = tmp;
    } 
    return res;
}

ll cir_DP() {return max(max(work(0).fi, work(0).se), work(1).se);}

int main() {
    memset(h, -1, sizeof h);
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        int a; scanf("%d%d", &w[i], &a);
        add(a, i); add(i, a);
    }
    for(int i = 1; i <= n; i++) {
        if(dfn[i]) continue;
        cir.resize(0); cir_ans.resize(0);
        find_cir(i, -1);
        for(int j : cir) cir_ans.push_back(DP(j, 0));
        ans += cir_DP();
    }
    printf("%lld", ans);
    return 0;
}