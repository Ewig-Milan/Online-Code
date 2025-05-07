#include <bits/stdc++.h>
using namespace std;

const int N = 1000100;

char c[N];
int n, ans;

int sa[N], rk[N << 1], rk_cpy[N << 1], se_st[N], T[N], st_ht[N][21];
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
    st_ht[1][0] = 0;
    for(int i = 1, k = 0; i <= n; i++) {
        if(rk[i] == 1) continue;
        if(k) k--;
        while(s[i + k] == s[sa[rk[i] - 1] + k] &&
            i + k <= n && sa[rk[i] - 1] + k <= n) k++;
        st_ht[rk[i]][0] = k;
    }
    for(int i = 1; i <= 20; i++) 
        for(int j = 1; j <= n; j++)
            st_ht[j][i] = min(st_ht[j][i - 1], st_ht[min(j + (1 << (i - 1)) + 1, n + 10)][i - 1]);
}

bool check(int x) {
    if(rk[1] < rk[1 + x]) return false;
    int k = max((int)log2(rk[1] - rk[1 + x] - 1), 0);
    return n - x == min(st_ht[rk[1]][k], st_ht[rk[1 + x] - (1 << k) + 2][k]);
}

int main() {
    while(~scanf("%s", c + 1) && c[1] != '.') {
        memset(T, 0, sizeof(T));
        memset(sa, 0, sizeof(sa));
        memset(rk, 0, sizeof(rk));
        memset(st_ht, 0, sizeof(st_ht));
        memset(rk_cpy, 0, sizeof(rk_cpy));
        memset(se_st, 0, sizeof(se_st));
        n = strlen(c + 1), ans = 0;
        get_SA(c);
        get_ht(c);
        for(int j = 1; j <= n >> 1; j++)
            if(n % j == 0 && check(j))  {
                ans = j;
                break;
            }
        if(!ans) ans = n;
        printf("%d\n", n / ans);
    }
    return 0;
}