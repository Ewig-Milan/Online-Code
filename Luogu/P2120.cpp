//
// 一组 Hack：
/*
Input:
5
0 5 12
3 12 43
10 31 23
50 0 2
56 0 100

Correct Output: 78

Potential Wrong Answer: 178
*/ 
//
#include <bits/stdc++.h>
#define ll long long
#define PLL pair<ll, ll>
#define x first
#define y second
using namespace std;

const int N = 6000100;
const PLL O = {0, 0};

int n;
ll A[N], x[N], p[N], C[N], f[N];
unsigned ll ans = (unsigned ll)1 << 63;
vector<int> cvh; int l, r = -1;

ll X(int j) {return p[j];}
ll Y(int j) {return f[j] + x[j] * p[j] - A[j];}
ll F(int i, int j) {return Y(j) - x[i] * p[j] + C[i] + A[i];}

bool cmp_k(PLL a, PLL b, PLL c, PLL d) {
	return (__int128)(b.y - a.y) * (d.x - c.x)
	>= (__int128)(b.x - a.x) * (d.y - c.y);
}
PLL P(int id) {return {X(id), Y(id)};}
int get_ans(ll k) {
 	while(l < r && cmp_k(O, {1, k}, P(cvh[l]), P(cvh[l + 1]))) l++;
    return cvh[l];
}
void add_back(int x) {
	while(l < r && cmp_k(P(cvh[r - 1]), P(x), P(cvh[r]), P(x))) r--;
	cvh.resize(++r), cvh.push_back(x);
}
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		scanf("%lld%lld%lld", &x[i], &p[i], &C[i]);
		A[i] = A[i - 1] + p[i - 1] * (x[i] - x[i - 1]);
		p[i] += p[i - 1];
	}
	p[n + 1] = p[n];
	memset(f, 127, sizeof f);
	f[0] = 0, add_back(0);
	for(int i = 1; i <= n; i++) {
		f[i] = F(i, get_ans(x[i]));
		add_back(i);
	}
	for(int i = n; i && !(p[i + 1] - p[i]); i--) ans = min(ans, (unsigned ll)f[i]);
	printf("%llu", ans);
	return 0;
}