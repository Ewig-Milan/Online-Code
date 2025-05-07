#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 200100;

char c1[N], c2[N], c3[N << 1];
int n;
ll ans;

int sa[N << 1], ht[N << 1], rk[N << 2], rk_cpy[N << 2], se_st[N << 1], T[N << 1];
void get_SA(char s[]) {
    n = strlen(s + 1);
    int m = 128;
    memset(T, 0, sizeof(T));
    memset(sa, 0, sizeof(sa));
    for(int i = 1; i <= n; i++) T[rk[i] = s[i]]++;
    for(int i = 2; i <= m; i++) T[i] += T[i - 1];
    for(int i = n; i; i--) sa[T[rk[i]]--] = i;
    for(int t, k = 1; k < n; k <<= 1, m = t) {
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
void get_ht(char s[]) {
    memset(ht, 0, sizeof(ht));
    for(int i = 1, k = 0; i <= n; i++) {
        if(rk[i] == 1) continue;
        if(k) k--;
        while(s[i + k] == s[sa[rk[i] - 1] + k] &&
            i + k <= n && sa[rk[i] - 1] + k <= n) k++;
        ht[rk[i]] = k;
    }
}

struct Edge {int a, b, w;};
vector<Edge> edg;
bool cmp(const Edge & a, const Edge & b) {return a.w > b.w;}
int fa[N << 1], siz[N << 1];
int find(int x) {
    if(x != fa[x]) fa[x] = find(fa[x]);
    return fa[x];
}
void merge(Edge x, ll & res) {
    int a = x.a, b = x.b;
    int f_a = find(a), f_b = find(b);
    if(f_a == f_b) return;
    res += (ll)siz[f_a] * siz[f_b] * x.w;
    fa[f_a] = f_b, siz[f_b] += siz[f_a];
}
ll work() {
    ll res = 0;
    edg.resize(0);
    for(int i = 1; i <= n; i++) fa[i] = i, siz[i] = 1;
    for(int i = 2; i <= n; i++) edg.push_back({sa[i - 1], sa[i], ht[i]});
    sort(edg.begin(), edg.end(), cmp);
    for(auto i : edg) merge(i, res);
    return res;
}

int main() {
    scanf("%s\n%s", c1 + 1, c2 + 1);
    n = strlen(c1 + 1);
    int tmp = n;
    for(int i = 1; i <= n; i++) c3[i] = c1[i];
    n = strlen(c2 + 1), c3[++tmp] = '#';
    for(int i = 1; i <= n; i++) c3[tmp + i] = c2[i];
    get_SA(c1); get_ht(c1); ans -= work();
    get_SA(c2); get_ht(c2); ans -= work();
    get_SA(c3); get_ht(c3); ans += work();
    printf("%lld", ans);
    return 0;
}