#include <bits/stdc++.h>
using namespace std;

const int N = 5100;

int d[N], n;

int ht[N], rk[N << 1], rk_cpy[N << 1], se_st[N], sa[N], T[N]; 
void get_SA(int s[]) {
    int m = 270;
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
        for(int i = n; i; i--)
        sa[T[rk[se_st[i]]]--] = se_st[i];
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

bool check(int x) {
	int ma, mi;
	for(int i = 1; i <= n; i++) {
		if(ht[i] < x) ma = sa[i], mi = sa[i];
		ma = max(ma, sa[i]), mi = min(mi, sa[i]);
		if(ma - mi > x) return true;
	}
	return false; 
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &d[i]);
	n--;
	for(int i = 1; i <= n; i++) d[i] = d[i + 1] - d[i];
	for(int i = 1; i <= n; i++) d[i] += 90;
	
	get_SA(d);
	get_ht(d);
	
	int l = 3, r = n;
	while(l < r) {
		int mid = l + r + 1 >> 1;
		if(check(mid)) l = mid;
		else r = mid - 1;
	}
	printf("%d", l < 4 ? 0 : l + 1);
	return 0;
}
