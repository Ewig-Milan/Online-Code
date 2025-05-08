#include <bits/stdc++.h>
#define int long long
#define PLL pair<int, int>
#define sub(x1, x2, x3, x4) (x1 == x2) ? max(x3, x4) : ((x1 > x2) ? max(x2, x3) : max(x1, x4))//已知：x1 > x3, x2 > x4 
using namespace std;

const int N = 100100, M = 300100;

int n, m, rt, ans, mi_delta = 1e18;

int h[N], e[N << 1], ne[N << 1], v[N << 1], idx;
void add(int a, int b, int c) {
	e[idx] = b, v[idx] = c, ne[idx] = h[a], h[a] = idx++;
	e[idx] = a, v[idx] = c, ne[idx] = h[b], h[b] = idx++;
}

struct Edge{int a, b, c;};
vector<Edge> edg, E;
bool cmp(const Edge & a, const Edge & b) {return a.c < b.c;}
bool used[M];

int f[N];
int find(int x) {
	if(f[x] != x) f[x] = find(f[x]);
	return f[x];
}
void krus() {
	for(int i = 0; i < N; i++) f[i] = i;
	sort(edg.begin(), edg.end(), cmp);
	for(int i = 0, cnt = 0; i < m; i++) {
		int f_a = find(edg[i].a), f_b = find(edg[i].b);
		if(f_a == f_b) continue;
		add(edg[i].a, edg[i].b, edg[i].c);
		used[i] = true, f[f_b] = f_a, ans += edg[i].c;
		if(++cnt == n - 1) {rt = f_a; break;}
	}
}

int fa[N][18], dep[N], Ma[N][18], Sub[N][18];
void dfs_pre(int x, int l, int w) {
	dep[x] = dep[l] + 1, fa[x][0] = l;
	Ma[x][0] = w, Sub[x][0] = -1;
	for(int i = 1; i <= 17; i++) {
		fa[x][i] = fa[fa[x][i - 1]][i - 1];
		Ma[x][i] = max(Ma[x][i - 1], Ma[fa[x][i - 1]][i - 1]);
		Sub[x][i] = sub(Ma[x][i - 1], Ma[fa[x][i - 1]][i - 1], Sub[x][i - 1], Sub[fa[x][i - 1]][i - 1]);
	}
	for(int i = h[x]; ~i; i = ne[i]) if(e[i] != l) dfs_pre(e[i], x, v[i]);
}

PLL LCA(int x, int y) {
	int ma = 0, sub_ma = -1;
	if(dep[x] < dep[y]) swap(x, y);
	for(int i = 17; i >= 0; i--) if(dep[fa[x][i]] >= dep[y]) {
		ma = max(ma, Ma[x][i]);
		sub_ma = sub(ma, Ma[x][i], sub_ma, Sub[x][i]);
		x = fa[x][i];
	}
	if(x == y) return {ma, sub_ma};
	int ma1 = 0, sub_ma1 = -1;
	for(int i = 17; i >= 0; i--) if(fa[x][i] != fa[y][i]) {
		ma = max(ma, Ma[x][i]);
		sub_ma = sub(ma, Ma[x][i], sub_ma1, Sub[x][i]);
		ma1 = max(ma1, Ma[y][i]);
		sub_ma1 = sub(ma1, Ma[y][i], sub_ma1, Sub[y][i]);
		x = fa[x][i], y = fa[y][i];
	}
	ma = max(ma, Ma[x][0]);
	sub_ma = sub(ma, Ma[x][0], sub_ma1, Sub[x][0]);
	ma1 = max(ma1, Ma[y][0]);
	sub_ma1 = sub(ma1, Ma[y][0], sub_ma1, Sub[y][0]);
	return {max(ma, ma1), sub(ma, ma1, sub_ma, sub_ma1)};
}

signed main() {
	memset(h, -1, sizeof h);
	scanf("%lld%lld", &n, &m);
	edg.resize(m);
	for(auto & i : edg) scanf("%d%d%d", &i.a, &i.b, &i.c);
	krus();
	for(int i = 0; i < m; i++) if(!used[i]) E.push_back(edg[i]);
	dfs_pre(rt, 0, 0);
	for(auto i : E) {
		int a = i.a, b = i.b, c = i.c;
		if(!c || a == b) continue;
		int ma, sub_ma; PLL lca = LCA(a, b);
		ma = lca.first, sub_ma = lca.second;
		if(ma != c) mi_delta = min(mi_delta, c - ma);
		else mi_delta = min(mi_delta, c - sub_ma);
	}
	printf("%lld", ans + mi_delta);
	return 0;
}