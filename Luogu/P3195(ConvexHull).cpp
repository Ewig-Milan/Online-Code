#include <bits/stdc++.h>
#define ll long long
#define PLL pair<ll, ll>
#define x first
#define y second
#define A(x) (C[x] + x - 1 - L)
#define B(x) (C[x] + x)
using namespace std;

const int N = 50100;
const PLL O = {0, 0};

int n;
ll C[N], f[N], L;
vector<int> cvh;
int l, r;

ll X(int id) {return B(id);}
ll Y(int id) {return f[id] + B(id) * B(id);}
ll F(int i, int j) {return f[j] + (A(i) - B(j)) * (A(i) - B(j));}

bool cmp_k(PLL a, PLL b, PLL c, PLL d) {
	return (__int128)(b.y - a.y) * (d.x - c.x)
	>= (__int128)(b.x - a.x) * (d.y - c.y);
}

PLL P(ll id) {return {X(id), Y(id)};}

int get_ans(ll k) {
 	while(l < r && cmp_k(O, {1, k}, P(cvh[l]), P(cvh[l + 1]))) l++;
    return cvh[l];
}
void add_back(int x) {
	while(r > l && cmp_k(P(cvh[r - 1]), P(x), P(cvh[r]), P(x))) r--;
	cvh.resize(++r), cvh.push_back(x);
}

int main() {
	scanf("%d%lld", &n, &L);
	for(int i = 1; i <= n; i++) {
		scanf("%lld", &C[i]);
		C[i] += C[i - 1]; 
	}
	memset(f, 127, sizeof f);
	f[0] = 0, add_back(0);
	for(int i = 1; i <= n; i++) {
		f[i] = F(i, get_ans(A(i) << 1));
		add_back(i); 
	}
	printf("%lld", f[n]);
	return 0;
}