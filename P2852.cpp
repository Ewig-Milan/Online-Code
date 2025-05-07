#include <bits/stdc++.h>
using namespace std;

const int N = 20100;

int n, d[N], ans, K;

int sa[N], rk[N << 1], rk_cpy[N << 1], T[N], se_st[N], ht[N];
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
		swap(rk_cpy, rk); t = 0;
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
        while(s[sa[rk[i] - 1] + k] == s[i + k] &&
            i + k <= n && sa[rk[i] - 1] + k <= n) k++;
        ht[rk[i]] = k;
    }
}

int main() {
	scanf("%d%d", &n, &K);

	vector<int> dc;
	for(int i = 1; i <= n; i++) scanf("%d", &d[i]), dc.push_back(d[i]);
	sort(dc.begin(), dc.end());
	dc.resize(unique(dc.begin(), dc.end()) - dc.begin());
	for(int i = 1; i <= n; i++)
		d[i] = lower_bound(dc.begin(), dc.end(), d[i]) - dc.begin() + 1;

	get_SA(d);
	get_ht(d);

	deque<int> q;
	for(int i = 1; i <= n; i++) {
		while(!q.empty() && ht[i] <= ht[q.back()]) q.pop_back();
		while(!q.empty() && q.front() + K - 1 <= i) q.pop_front();
		q.push_back(i);
		if(i >= K - 1) ans = max(ans, ht[q.front()]);
	}
	printf("%d", ans);
	return 0;
}