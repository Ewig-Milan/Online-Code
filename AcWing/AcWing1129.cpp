#include <bits/stdc++.h>
using namespace std;

const int N = 200100;

int n, m, s, en, cnt;
bool flag[N];
int dis[N];
struct Node {
	int x, v;
	friend bool operator < (const Node & a, const Node & b) {return a.v > b.v;}
};
priority_queue<Node> qu;
int e[N << 1], h[N], ne[N << 1], idx, v[N << 1];
void add(int a, int b, int c) {e[idx] = b, v[idx] = c, ne[idx] = h[a], h[a] = idx++;}

void dji(int st) {
	memset(dis, 127, sizeof(dis));
	dis[st] = 0;
	qu.push({st, 0});
	while(!qu.empty()) {
		while(!qu.empty() && flag[qu.top().x]) qu.pop();
		if(qu.empty()) break; 
		int x = qu.top().x;
		qu.pop();
		cnt++;
		flag[x] = true;
		if(cnt == n) break;
		for(int i = h[x]; ~i; i = ne[i]) {
			int j = e[i];
			if(flag[j]) continue; 
			if(dis[j] > dis[x] + v[i]) {
				dis[j] = dis[x] + v[i];
				qu.push({j, dis[j]});
			}
		}
	}
}

int main() {
	memset(h, -1, sizeof(h));
	scanf("%d%d%d%d", &n, &m, &s, &en);
	for(int i = 1; i <= m; i++) {
		int a, b, c; scanf("%d%d%d", &a, &b, &c);
		add(a, b, c);
		add(b, a, c);
	}
	dji(s);
	printf("%d", dis[en]);
	return 0;
}