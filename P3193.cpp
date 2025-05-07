#include <bits/stdc++.h>
#define ll long long
using namespace std;

int n, m, k, ne[30], ans;
char c[30];

struct Ma {
	int x, y, m[30][30];
}G, f;
Ma operator * (const Ma & a, const Ma & b) {
	Ma c;
	c.x = a.x, c.y = b.y;
	memset(c.m, 0, sizeof(c.m));
	for(int i = 0; i < a.x; i++)
		for(int j = 0; j < b.y; j++)
			for(int p = 0; p < a.y; p++)
				c.m[i][j] += (ll)(a.m[i][p] % k) * (b.m[p][j] % k) % k, c.m[i][p] %= k;
	return c;
}

Ma quick_p(Ma a, int x) {
	Ma res;
	memset(res.m, 0, sizeof(res.m));
	res.x = a.x, res.y = a.y;
	for(int i = 0; i < m; i++) res.m[i][i] = 1;
	while(x) {
		if(x & 1) res = res * a;
		a = a * a;
		x >>= 1;
	}
	return res;
}

int main() {
	scanf("%d%d%d", &n, &m, &k);
	scanf("%s", c + 1);
	for(int i = 2; i <= m; i++) {
		int j = ne[i - 1];
		while(j && c[j + 1] != c[i]) j = ne[j];
		if(c[j + 1] == c[i]) j++;
		ne[i] = j;
	}
	for(int i = 0; i < m; i++)
		for(char ch = '0'; ch <= '9'; ch++) {
			int j = i;
			while(j && c[j + 1] != ch) j = ne[j];
			if(c[j + 1] == ch) ++j;
			++G.m[i][j];
		}
	G.x = G.y = m;
	f.x = 1, f.y = m;
	f.m[0][0] = 1;
	f = f * quick_p(G, n);
	for(int i = 0; i < m; i++) ans += f.m[0][i], ans %= k;
	printf("%d", ans);
	return 0;
}