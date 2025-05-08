#include <bits/stdc++.h>
using namespace std;

const int N = 500100, M = 1000100;

int n;

int h[N], e[M], v[M], ne[M], idx;
void add(int a, int b, int c) {
	e[idx] = b, v[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

int dep[N], d[N], ma_s[N], siz[N];
int L[N], R[N], ans[N], cnt, id[N];
int mp[(1 << 22) + 100];//存深度 

void dfs_pre(int x, int l, int p) {
	d[x] = p, dep[x] = dep[l] + 1, siz[x] = 1, L[x] = ++cnt, id[cnt] = x;
	for(int i = h[x]; ~i; i = ne[i]) {
		int j = e[i];
		if(j == l) continue;
		dfs_pre(j, x, p ^ (1 << v[i]));
		siz[x] += siz[j];
		if(siz[ma_s[x]] < siz[j]) ma_s[x] = j;
	}
	R[x] = cnt;
}

void dfs(int x, int l, bool keep) {
	for(int i = h[x]; ~i; i = ne[i]) {
		int j = e[i];
		if(j == l || j == ma_s[x]) continue;
		dfs(j, x, 0);
	}
	if(ma_s[x]) dfs(ma_s[x], x, 1);
	for(int k = 0, i = 0; i <= 22; k = 1 << i, i++)//i跑到22,k跑到1<<21时停 我在这地方调了一个小时(错误在i < 22没带等号)!!!
		if(mp[d[x] ^ k]) ans[x] = max(ans[x], mp[d[x] ^ k] - dep[x]);
	mp[d[x]] = max(mp[d[x]], dep[x]);
	for(int i = h[x]; ~i; i = ne[i]) if(e[i] != l && ans[e[i]] > ans[x]) ans[x] = ans[e[i]];//一定要带上 因为DSU on T只会统计子树间串联的情况 与点分治相似
	for(int i = h[x]; ~i; i = ne[i]) {
		int j = e[i];
		if(j == l || j == ma_s[x]) continue;
		for(int k = L[j]; k <= R[j]; k++) {
			int t = id[k];
			for(int K = 0, I = 0; I <= 22; K = 1 << I, I++)
				if(mp[d[t] ^ K]) ans[x] = max(ans[x], mp[d[t] ^ K] + dep[t] - 2 * dep[x]);
		}
		for(int k = L[j]; k <= R[j]; k++)
			mp[d[id[k]]] = max(mp[d[id[k]]], dep[id[k]]);
	}
	if(!keep) for(int i = L[x]; i <= R[x]; i++) mp[d[id[i]]] = 0;
}

int main() {
	scanf("%d", &n);
	memset(h, -1, sizeof(h));
	for(int i = 2; i <= n; i++) {
		int a; char b; scanf("%d %c", &a, &b);
		add(i, a, b - 'a'); add(a, i, b - 'a');
	}
	dfs_pre(1, 0, 0);
	dfs(1, 0, 1);
	for(int i = 1; i <= n; i++) printf("%d ", ans[i]);
	return 0;
}