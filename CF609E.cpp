#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 200100, M = 400100;

struct Edge {
	int a, b, w, id;
};
vector <Edge> edg;

int tot;

int h[N], e[M], ne[M], v[M], idx;
void add(int a, int b, int c) {
    e[idx] = b, v[idx] = c, ne[idx] = h[a], h[a] = idx++, tot++;
}

bool cmp(const Edge & a, const Edge & b) {return a.w < b.w;}

int n, m;
ll sum, ans[N];
int f[N];
int find(int x) {
	if(f[x] != x) f[x] = find(f[x]);
	return f[x];
}

int fa[N][26], ma[N][26], dep[N];
void dfs(int x, int l, int w) {
    fa[x][0] = l, ma[x][0] = w, dep[x] = dep[l] + 1;
    for(int i = 1; i <= 25; i++) {
        fa[x][i] = fa[fa[x][i - 1]][i - 1];
        ma[x][i] = max(ma[x][i - 1], ma[fa[x][i - 1]][i - 1]);
    }
    for(int i = h[x]; ~i; i = ne[i]) {
        int j = e[i];
        if(j == l) continue;
        dfs(j, x, v[i]);
    }
}

int get(int a, int b) {
    int mx = 0;
    if(dep[a] < dep[b]) swap(a, b);
    for(int i = 25; i >= 0; i--)
        if(dep[fa[a][i]] >= dep[b])
            mx = max(mx, ma[a][i]), a = fa[a][i];
    if(a == b) return mx;
    for(int i = 25; i >= 0; i--)
        if(fa[a][i] != fa[b][i]) {
            mx = max(mx, max(ma[a][i], ma[b][i]));
            a = fa[a][i], b = fa[b][i];
        }
    mx = max(mx, max(ma[a][0], ma[b][0]));
    return mx;
}

int main() {
	scanf("%d%d", &n, &m);
    memset(h, -1, sizeof(h));
	for(int i = 0; i < N; i++) f[i] = i;
	for(int i = 1; i <= m; i++) {
		int a, b, v; scanf("%d%d%d", &a, &b, &v);
		edg.push_back({a, b, v, i});
	}
	sort(edg.begin(), edg.end(), cmp);
	for(int i = 0; i < m; i++) {
        if(tot >> 1 == n - 1) break;
        int a = find(edg[i].a), b = find(edg[i].b);
        if(a == b) continue;
        add(edg[i].a, edg[i].b, edg[i].w);
        add(edg[i].b, edg[i].a, edg[i].w);
        f[a] = b, sum += (ll)edg[i].w;
    }
    dep[0] = -1;
    dfs(1, 0, 0);
    for(int i = 0; i < m; i++)
        ans[edg[i].id] = sum - get(edg[i].a, edg[i].b) + edg[i].w;
    for(int i = 1; i <= m; i++) printf("%lld\n", ans[i]);
    return 0;
}