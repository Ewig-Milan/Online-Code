#include <bits/stdc++.h>
#define ll long long
#define PLL pair<ll, ll> //最大, 次大 
#define fi first
#define se second
#define SON int i = h[x]; ~i; i = ne[i]
using namespace std;

const int N = 1000100;

int n; ll ans, tmp;

int h[N], e[N << 1], ne[N << 1], v[N << 1], idx;
void add(int a, int b, int c) {
	e[idx] = b, v[idx] = c, ne[idx] = h[a], h[a] = idx++;
	e[idx] = a, v[idx] = c, ne[idx] = h[b], h[b] = idx++;
}

vector<int> cir;
vector<ll> cir_ans, cir_e/*在prepare中处理*/;
bool in_cir[N];
ll pm[N], pa[N], sm[N], sa[N];

int fa[N];
void find_cir(int x, int l) {
	for(SON) if((i ^ 1) != l) if(fa[e[i]] && cir.empty())
	for(int t = x; t != fa[e[i]]; t = fa[t]) cir.push_back(t), in_cir[t] = 1;
	else if(!fa[e[i]]) fa[e[i]] = x, find_cir(e[i], i);
}

PLL DP(int x, int l) {
	PLL res = {0, 0};
	for(int i = h[x]; ~i; i = ne[i]) {
		int j = e[i];
		if(j == l || in_cir[j]) continue;
		PLL tmp = DP(j, x);
		tmp.fi += v[i], tmp.se += v[i];
		if(tmp.fi > res.fi) res.se = res.fi, res.fi = tmp.fi;
		else res.se = max(res.se, tmp.fi);
	}
	tmp = max(tmp, res.fi + res.se);
	return res;
}

void prepare() {
	int siz = cir.size();
	for(int p = 0; p < siz; p++) {
		int real = cir[(p + siz - 1) % siz];
		for(int i = h[real]; ~i; i = ne[i]) if(e[i] == cir[p]) cir_e.push_back((ll)v[i]);
	}
	pm[0] = cir_e[0] + cir_ans[0], pa[0] = -1e9;
	sm[siz - 1] = cir_ans[siz - 1], sa[siz - 1] = -1e9;
	for(ll i = 1, sum = cir_e[0], mi = sum - cir_ans[0]; i < siz; i++) {
		sum += cir_e[i];
		pm[i] = max(pm[i - 1], sum + cir_ans[i]);
		pa[i] = max(pa[i - 1], sum + cir_ans[i] - mi);
		mi = min(mi, sum - cir_ans[i]);
	}
	for(ll i = siz - 2, sum = 0, mi = -cir_ans[siz - 1]; i >= 0; i--) {
		sum += cir_e[i + 1];
		sm[i] = max(sm[i + 1], sum + cir_ans[i]);
		sa[i] = max(sa[i + 1], sum + cir_ans[i] - mi);
		mi = min(mi, sum - cir_ans[i]);
	}
}

int main() {
	memset(h, -1, sizeof h);
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		int a, b; scanf("%d%d", &a, &b);
		add(a, i, b);
	}
    for(int i = 1; i <= n; i++) {
        if(fa[i]) continue;
        cir.resize(0); cir_ans.resize(0); cir_e.resize(0);
        fa[i] = -1, tmp = 0; find_cir(i, -1);
        for(int i : cir) cir_ans.push_back(DP(i, 0).fi);
        prepare();
        tmp = max(tmp, sa[0]);
        for(int i = 1; i < cir.size(); i++)
            tmp = max(tmp, max(max(pa[i - 1], sa[i]), pm[i - 1] + sm[i]));
        ans += tmp;    
    }
	printf("%lld", ans);
	return 0;
}