//
// 小板子 也许是最终形态了 
//
#include <bits/stdc++.h>
#define ll long long
#define PLL pair<ll, ll>
#define x first
#define y second
using namespace std;

const int N = 300100;
const PLL O = {0, 0};

int n;
ll C[N], T[N], f[N], S;
vector<int> cvh; //convex hull
int l, r;


ll X(int id) {return C[id];}
ll Y(int id) {return f[id];}
ll F(int i, int j) {return f[j] - (S + T[i]) * C[j] + S * C[n] + T[i] * C[i];}
// 以上三个是随题变化的


// 若改成 <= 维护上凸壳
bool cmp_k(PLL a, PLL b, PLL c, PLL d) { // k(ab) >= k(cd)
	return (__int128)(b.y - a.y) * (d.x - c.x)
	>= (__int128)(b.x - a.x) * (d.y - c.y);
} // 带不带这个等号 关联的其实是一个常数问题 影响不大

// --------- 除法形式 容易爆精度 还容易爆除以0
// bool cmp_k(PLL a, PLL b, PLL c, PLL d) { // 同上
//     return (double)(b.y - a.y) / (b.x - a.x)
//     >= (double)(d.y - c.y) / (d.x - c.x);
// }


// 这三个完全不用变
PLL P(ll id) {return {X(id), Y(id)};}

// int get_ans(ll k) {
//  	while(l < r && cmp_k(O, {1, k}, P(cvh[l]), P(cvh[l + 1]))) l++;
//      return cvh[l];
// }
int get_ans(ll k) {
	l = 0, r = cvh.size() - 1;
	while(l < r) {
		int mid = l + r >> 1;
		if(cmp_k(P(cvh[mid]), P(cvh[mid + 1]), O, {1, k})) r = mid;
		else l = mid + 1;
	}
	int tmp = cvh[l];
	l = 0, r = cvh.size() - 1;
	return tmp;
}

void add_back(int x) {
	while(l < r && cmp_k(P(cvh[r - 1]), P(x), P(cvh[r]), P(x))) r--;
	cvh.resize(++r), cvh.push_back(x);
}

int main() {
	scanf("%d%lld", &n, &S);
	for(int i = 1; i <= n; i++) {
		scanf("%lld%lld", &T[i], &C[i]);
		T[i] += T[i - 1], C[i] += C[i - 1]; 
	}
	memset(f, 127, sizeof f);
	f[0] = 0, add_back(0);

	for(int i = 1; i <= n; i++) {
		f[i] = F(i, get_ans(S + T[i])/*回传下标*/);
		add_back(i); 
	}
	printf("%lld", f[n]);
	return 0;
}