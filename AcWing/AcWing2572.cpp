#include <bits/stdc++.h>
#define ll long long
#define f(x) (ll)(x) * (x + 1) / 2
using namespace std;

const int N = 100100;

int n;
int d[N], ne_f[N], ne_b[N], d_tmp[N];
ll ans[N], del_tmp;

int ht[N], rk[N << 1], rk_cpy[N << 1], se_st[N], sa[N], T[N]; 
void get_SA(int s[]) {
    int m = n;
    for(int i = 1; i <= n; i++) T[rk[i] = s[i]]++;
    for(int i = 2; i <= m; i++) T[i] += T[i - 1];
    for(int i = n; i; i--) sa[T[rk[i]]--] = i;
    for(int k = 1, t; k < n; k <<= 1, m = t) {
        t = 0;
        for(int i = n - k + 1; i <= n; i++) se_st[++t] = i;
        for(int i = 1; i <= n; i++)
            if(sa[i] > k) se_st[++t] = sa[i] - k;
        for(int i = 0; i <= m; i++) T[i] = 0;
        for(int i = 1; i <= n; i++) T[rk[i]]++;
        for(int i = 2; i <= m; i++) T[i] += T[i - 1];
        for(int i = n; i; i--) sa[T[rk[se_st[i]]]--] = se_st[i];
        swap(rk, rk_cpy); t = 0;
        for(int i = 1; i <= n; i++) {
            if(rk_cpy[sa[i]] != rk_cpy[sa[i - 1]] ||
				rk_cpy[sa[i] + k] != rk_cpy[sa[i - 1] + k]) t++;
            rk[sa[i]] = t;
        }
        if(t == n) return;
    }
}
void get_ht(int s[]) {
    ht[1] = 0;
	for(int i = 1, k = 0; i <= n; i++) {
		if(rk[i] == 1) continue;
		if(k) k--;
		while(s[i + k] == s[sa[rk[i] - 1] + k] &&
			i + k <= n && sa[rk[i] - 1] + k <= n) k++;
		ht[rk[i]] = k;
	}
}

int main() {
	scanf("%d", &n);
	
	vector<int> dc;
	for(int i = 1; i <= n; i++) scanf("%d", &d[i]), dc.push_back(d[i]);
	sort(dc.begin(), dc.end()); dc.resize(unique(dc.begin(), dc.end()) - dc.begin());
	for(int i = 1; i <= n; i++)	d_tmp[i] = lower_bound(dc.begin(), dc.end(), d[n - i + 1]) - dc.begin() + 1;
	
	get_SA(d_tmp);
	get_ht(d_tmp);
	
	for(int i = 1; i <= n; i++) {
		del_tmp += ht[i];
		ne_f[i] = i + 1, ne_b[i] = i - 1;
	}
	for(int i = 1; i <= n; i++) {
		ans[i] = -del_tmp + f(n - i + 1);
		int r = rk[i], F = ne_f[r];
		int new_ht = min(ht[r], ht[F]);
		del_tmp -= ht[r] + ht[F] - new_ht, ht[F] = new_ht;
		ne_f[ne_b[r]] = ne_f[r], ne_b[ne_f[r]] = ne_b[r];
	}
	for(int i = n; i; i--) printf("%lld\n", ans[i]);
	return 0;
}