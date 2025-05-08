#include <bits/stdc++.h>
using namespace std;

const int N = 100100, M = 200100;

int n, c[N], ans[N];

int h[N], e[M], ne[M], idx;
void add(int a, int b) {
	e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

int siz[N], ma_s[N], cnt_ma/*time*/; 
int L[N], R[N], id[N], cnt[N]/*下标为颜色*/, num[N]/*下标为time*/, cnt_dfn;//cnt存个数 num存同i次的和 
void dfs_pre(int x, int l) {
	L[x] = ++cnt_dfn, id[cnt_dfn] = x, siz[x] = 1;
	for(int i = h[x]; ~i; i = ne[i]) {
		int j = e[i];
		if(j == l) continue;
		dfs_pre(j, x);
		siz[x] += siz[j];
		if(siz[j] > siz[ma_s[x]]) ma_s[x] = j;
	}
	R[x] = cnt_dfn;
}

void add_col(int col) {
	if(cnt[col] == cnt_ma) cnt_ma++;
	num[cnt[col]] -= col;
    cnt[col]++;
	num[cnt[col]] += col;
}

void del_col(int col) {
    if(cnt[col] == cnt_ma && num[cnt_ma] == col) cnt_ma--;
    num[cnt[col]] -= col;
    cnt[col]--;
    num[cnt[col]] += col;
}

void dfs(int x, int l, bool keep) {
	for(int i = h[x]; ~i; i = ne[i]) {
		int j = e[i];
		if(j == l || j == ma_s[x]) continue;
		dfs(j, x, 0);
	}
	if(ma_s[x]) dfs(ma_s[x], x, 1);
	for(int i = h[x]; ~i; i = ne[i]) {
		int j = e[i];
		if(j == l || j == ma_s[x]) continue;
		for(int k = L[j]; k <= R[j]; k++) add_col(c[id[k]]);
	}
	add_col(c[x]);
	ans[x] = num[cnt_ma];
	if(!keep) for(int i = L[x]; i <= R[x]; i++) del_col(c[id[i]]);
}

int main() {
	memset(h, -1, sizeof(h));
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &c[i]);
	for(int i = 1; i < n; i++) {
		int a, b; scanf("%d%d", &a, &b);
		add(a, b); add(b, a);
	}
	dfs_pre(1, 0);
	dfs(1, 0, 1);
	for(int i = 1; i <= n; i++) printf("%d ", ans[i]);
	return 0;
}