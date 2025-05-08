#include <bits/stdc++.h>
#define Lb(x) x & -x
using namespace std;

const int N = 1000100;

int k, n;
int tr[N][26], ne[N], idx, en[N], pt[N];
int L[N], R[N], cnt = -1;
bool ex[N];

struct Bit_T {
	vector<int> sum;
	int tot;
	void cl(int n) {
		tot = n;
		sum.resize(0);
		sum.resize(n + 100);
	}
	void modify(int x, int delta) {
		while(x <= tot) {
			sum[x] += delta;
			x += Lb(x);
		}
	}
	int presum(int x) {
		int ans = 0;
		while(x) {
			ans += sum[x];
			x -= Lb(x);
		}
		return ans;
	}
	void debug() {
		for(int i = 1; i <= tot; i++) printf("%d ", presum(i));
		printf("\n");
	}
}b_t;

struct CFS {
	int h[N], e[N], ne[N], idx;
	void cl() {
		memset(h, -1, sizeof(h));
		idx = 0;
	}
	void add(int a, int b) {e[idx] = b, ne[idx] = h[a], h[a] = idx++;}
	void dfs(int x) {
		L[x] = ++cnt;
		for(int i = h[x]; ~i; i = ne[i]) dfs(e[i]);
		R[x] = cnt;
		if(en[x]) b_t.modify(L[x], en[x]), b_t.modify(R[x] + 1, -en[x]);
		//printf("%d %d %d  ", x, L[x], R[x]);
		//b_t.debug();
	}
	void debug(int x) {
		printf("fa:%d, son:", x);
		for(int i = h[x]; ~i; i = ne[i])
			printf("%d ", e[i]);
		printf("\n");
		for(int i = h[x]; ~i; i = ne[i]) debug(e[i]);
	}
}mp;

void insert(char s[], int x) {
	int s_n = strlen(s + 1), j = 0;
	for(int i = 1; i <= s_n; i++) {
		if(!tr[j][s[i] - 'a']) tr[j][s[i] - 'a'] = ++idx;
		j = tr[j][s[i] - 'a'];
	}
	en[j]++, pt[x] = j;
}

void build() {
	queue<int> q;
	for(int i = 0; i < 26; i++)
		if(tr[0][i]) q.push(tr[0][i]), mp.add(0, tr[0][i]);
	while(!q.empty()) {
		int j = q.front();
		q.pop();
		for(int i = 0; i < 26; i++) {
			int k = tr[j][i];
			if(k) q.push(k), ne[k] = tr[ne[j]][i], mp.add(ne[k], k);
			else tr[j][i] = tr[ne[j]][i];
		}
	} 
}

int work(char s[]) {
	int s_n = strlen(s + 1), ans = 0;
	for(int i = 1, j = 0; i <= s_n; i++) {
		j = tr[j][s[i] - 'a'];
		ans += b_t.presum(L[j]);
	}
	return ans;
}

int main() {
	mp.cl();
	scanf("%d%d", &k, &n);
	for(int i = 1; i <= n; i++) {
		char c[N]; scanf("%s", c + 1);
		insert(c, i); ex[i] = true;
	}
	build();
	b_t.cl(idx);
	mp.dfs(0);
	//mp.debug(0);
	while(k--) {
		char mode; scanf("\n%c", &mode);
		if(mode == '?') {
			char c[N]; scanf("%s", c + 1);
			printf("%d\n", work(c));
		} else {
			int a, x = mode == '+' ? 1 : -1; scanf("%d", &a);
			if(ex[a] == (mode == '+')) continue;
			b_t.modify(L[pt[a]], x), b_t.modify(R[pt[a]] + 1, -x);
			ex[a] = mode == '+';
		}
	}
	return 0;
}