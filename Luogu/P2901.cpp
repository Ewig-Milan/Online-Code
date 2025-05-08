#include <bits/stdc++.h>
using namespace std;

const int N = 1100, M = 10100;

int n, m, k;
int g[N];
struct CFS {
	int h[N], e[M], ne[M], v[M], idx;
	void cl() {memset(h, -1, sizeof h); idx = 0;}
	void add(int a, int b, int c) {e[idx] = b, v[idx] = c, ne[idx] = h[a], h[a] = idx++;}
	
	int cnt;
	bool flag[N];
	struct dji_Node {
		int p, dis;
		friend bool operator < (const dji_Node & a, const dji_Node & b) {
			return a.dis > b.dis;
		}
	};
	void dji(int st) {
		memset(g, 127, sizeof g);
		priority_queue<dji_Node> q;
		q.push({st, 0});
		g[st] = 0;
		while(!q.empty()) {
			while(!q.empty() && flag[q.top().p]) q.pop();
			cnt++;
			if(cnt == n || q.empty()) break;
			int x = q.top().p;
			q.pop();
			flag[x] = true;
			for(int i = h[x]; ~i; i = ne[i]) {
				int j = e[i];
				if(flag[j]) continue;
				if(g[j] > g[x] + v[i]) {
					g[j] = g[x] + v[i];
					q.push({j, g[j]});
				}
			}
		}
	}
	struct AsNode {
		int p, f;
		friend bool operator < (const AsNode & a, const AsNode & b) {
			return a.f + g[a.p] > b.f + g[a.p];
		}
	};
	void A_star(int st, int k) {
		priority_queue<AsNode> q;
		q.push({st, 0});
		while(!q.empty()) {
			int x = q.top().p, f = q.top().f;
			q.pop();
			if(x == n) {
				printf("%d\n", f);
				if(!--k) break;
			}
			for(int i = h[x]; ~i; i = ne[i]) {
				int j = e[i];
				q.push({j, f + v[i]});
			}
		}
		while(k--) puts("-1");
	}
}mp, r_mp;
	
int main() {
	mp.cl(); r_mp.cl();
	scanf("%d%d%d", &n, &m, &k);
	for(int i = 1; i <= m; i++) {
		int a, b, c; scanf("%d%d%d", &a, &b, &c);
		mp.add(b, a, c), r_mp.add(a, b, c);
	}
	r_mp.dji(n);
	mp.A_star(1, k);
	return 0;
}