//
// Tarjan 缩点 + DAGdp写法 
//
#include <bits/stdc++.h>
using namespace std;

const int N = 100100, M = 500100;

int n, m;
int w[N];

int bl_id[N], bl_cnt;
vector<int> bl[N];
int rd[N];

struct CFS {
	int h[N], e[M << 1], ne[M << 1], idx;
	int ma[N], mi[N], ans[N];
	void cl() {
		memset(h, -1, sizeof(h));
		memset(ma, 128, sizeof(ma));
		memset(mi, 127, sizeof(mi));
		idx = 0;
	}
	void add(int a, int b) {e[idx] = b, ne[idx] = h[a], h[a] = idx++;}
	
	int dfn[N], low[N], cnt = 0;
	bool flag[N];
	stack<int> S;
	void tarjan(int x) {
		dfn[x] = low[x] = ++cnt;
		S.push(x);
		flag[x] = true;
		for(int i = h[x]; ~i; i = ne[i]) {
			int j = e[i];
			if(!dfn[j]) {
				tarjan(j);
				low[x] = min(low[x], low[j]);
			} else if(flag[j]) low[x] = min(low[x], low[j]);
		}
		if(dfn[x] == low[x]) {
			bl_id[x] = ++bl_cnt;
			bl[bl_cnt].push_back(x);
			while(S.top() != x) {
				int j = S.top();
				S.pop();
				flag[j] = false;
				bl[bl_cnt].push_back(j);
				bl_id[j] = bl_cnt;
			}
			S.pop();
			flag[x] = false;
		}
	}
	int dp(int id) {
		queue<int> q;
		q.push(id);
		while(!q.empty()) {
			int x = q.front();
			ans[x] = max(ans[x], ma[x] - mi[x]);
			q.pop();
			for(int i = h[x]; ~i; i = ne[i]) {
				int j = e[i];
				rd[j]--, mi[j] = min(mi[x], mi[j]);
				ans[j] = max(ans[x], ans[j]);
				if(!rd[j]) q.push(j);
			}
		}
		return ans[bl_id[n]];
	}
}mp, bl_mp;

struct Edge {int a, b;};
vector<Edge> edg;

int main() {
	mp.cl(); bl_mp.cl();
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%d", &w[i]);
	
	for(int i = 1; i <= m; i++) {
		int a, b, c; scanf("%d%d%d", &a, &b, &c);
		mp.add(a, b); edg.push_back({a, b});
		if(c == 2) {mp.add(b, a); edg.push_back({b, a});}
	}
	mp.tarjan(1);
	for(int i = 1; i <= bl_cnt; i++) {
		for(auto j : bl[i]) {
			bl_mp.ma[i] = max(bl_mp.ma[i], w[j]);
			bl_mp.mi[i] = min(bl_mp.mi[i], w[j]);
		}
	}
	for(auto i : edg) if(bl_id[i.a] != bl_id[i.b]) {
		bl_mp.add(bl_id[i.a], bl_id[i.b]);
		rd[bl_id[i.b]]++;
	}
	printf("%d", bl_mp.dp(bl_id[1]));
	return 0;
}