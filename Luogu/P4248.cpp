#include <bits/stdc++.h>
#define ll long long
#define f(x) (ll)x * (x - 1) * (x + 1) / 2
using namespace std;

const int N = 5000100;

char c[N];
int n;
ll ans;
struct Edge {int a, b, w;};
vector<Edge> edg;

int fa[N], siz[N];
int find(int x) {
    if(fa[x] != x) x = find(fa[x]);
    return fa[x];
}
int sa[N], ht[N], rk[N << 1], T[N], rk_cpy[N << 1], se_st[N];
void get_SA(char s[]) {
    int m = 128;
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
void get_ht(char s[]) {
    ht[1] = 0;
	for(int i = 1, k = 0; i <= n; i++) {
		if(rk[i] == 1) continue;
		if(k) k--;
		while(s[i + k] == s[sa[rk[i] - 1] + k] &&
			i + k <= n && sa[rk[i] - 1] + k <= n) k++;
		ht[rk[i]] = k;
	}
    for(int i = 2; i <= n; i++) edg.push_back({sa[i], sa[i - 1], ht[i]});
}
bool cmp(const Edge & a, const Edge & b) {return a.w > b.w;}

void merge(Edge p) {
    int f_a = find(p.a), f_b = find(p.b);
    ans += 2 * (ll)p.w * siz[f_a] * siz[f_b];
    fa[f_a] = f_b; siz[f_b] += siz[f_a];
}
int main() {
    scanf("%s", c + 1);
    n = strlen(c + 1);
    get_SA(c); get_ht(c);
    for(int i = 1; i <= n; i++) fa[i] = i, siz[i] = 1;
    sort(edg.begin(), edg.end(), cmp);
    for(auto p : edg) merge(p);
    printf("%lld", f(n) - ans);
    return 0;
}