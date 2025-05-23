#include <bits/stdc++.h>
#define ll long long
#define PLL pair<ll, ll>
#define x first
#define y second
using namespace std;

const int N = 3100;
const PLL O = {0, 0};

int n, m;
ll D[N], f[2][N];
vector<int> cvh; int l, r = -1;

ll X(int id) {return D[id];}
ll Y(bool t, int id) {return f[t][id] + D[id] * D[id] * (m + 1);}
ll F(bool t, int i, int k) {return Y(t, k) - D[i] * D[k] * m * 2 + D[i] * D[i] * (m - 1);}

bool cmp_k(PLL a, PLL b, PLL c, PLL d) {
	return (__int128)(b.y - a.y) * (d.x - c.x)
	>= (__int128)(b.x - a.x) * (d.y - c.y);
}
PLL P(bool t, ll id) {return {X(id), Y(t, id)};}
int get_ans(bool t, ll k) {
 	while(l < r && cmp_k(O, {1, k}, P(t, cvh[l]), P(t, cvh[l + 1]))) l++;
    return cvh[l];
}
void add_back(bool t, int x) {
	while(l < r && cmp_k(P(t, cvh[r - 1]), P(t, x), P(t, cvh[r]), P(t, x))) r--;
	cvh.resize(++r), cvh.push_back(x);
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%lld", &D[i]), D[i] += D[i - 1];
	memset(f, 127, sizeof f);
	f[0][0] = 0;
	for(int day = 1, j = 1; day <= m; j = (++day) & 1) {
		for(int i = 0; i <= n; i++) f[j][i] = 1e18;
		f[j][0] = 0, l = 0, r = -1;
		cvh.resize(0), add_back(j, 0);
		for(int i = 1; i <= n; i++) {
			f[j][i] = F(j ^ 1, i, get_ans(j ^ 1, (D[i] * m) << 1));
			add_back(j ^ 1, i);
		}
	}
	printf("%lld", f[m & 1][n]);
	return 0;
}