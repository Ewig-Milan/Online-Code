#include <bits/stdc++.h>
#define ll long long
#define f(x) (ll)(x) * (x + 1) / 2
using namespace std;

const int N = 100100;

int n;
ll ans;
char c[N];

int sa[N], rk[N << 1], rk_cpy[N << 1], se_st[N], T[N];
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
    for(int i = 1, k = 0; i <= n; i++) {
        if(rk[i] == 1) continue;
        if(k) k--;
        while(s[i + k] == s[sa[rk[i] - 1] + k] &&
            i + k <= n && sa[rk[i] - 1] + k <= n) k++;
        ans -= (ll)k;
    }
}

int main() {
    scanf("%d", &n);
    scanf("%s", c + 1);
    get_SA(c);
    get_ht(c);
    printf("%lld", ans + f(n));
    return 0;
}