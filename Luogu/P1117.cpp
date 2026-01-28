#include <bits/stdc++.h>
using namespace std;

const int N = 30100;

int n;
char S[N];
int Log[N];

void pre() {for(int i = 2; i < N; i++) Log[i] = Log[i / 2] + 1;}

struct SA {
    int sa[N], se_st[N], rk[N << 1], rk_cpy[N << 1], ht[16][N << 1], T[N];
    void get_SA(char s[]) {
        memset(rk, 0, sizeof rk);
        memset(rk_cpy, 0, sizeof rk_cpy);
        int m = 128;
        for(int i = 0; i <= m; i++) T[i] = 0;
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
            swap(rk, rk_cpy), t = 0;
            for(int i = 1; i <= n; i++) {
                if(rk_cpy[sa[i]] != rk_cpy[sa[i - 1]] ||
                    rk_cpy[sa[i] + k] != rk_cpy[sa[i - 1] + k]) t++;
                rk[sa[i]] = t;
            }
            if(t == n) return;
        }
    }
    void get_ht(char s[]) {
        ht[0][1] = 0;
        for(int i = 1, k = 0; i <= n; i++) {
            if(rk[i] == 1) continue;
            if(k) k--;
            while(s[i + k] == s[sa[rk[i] - 1] + k] && 
                i + k <= n && sa[rk[i] - 1] + k <= n) k++;
            ht[0][rk[i]] = k;
        }
        for(int i = 1; i < 16; i++) for(int j = 1; j <= n; j++)
            ht[i][j] = min(ht[i - 1][j], j > (1 << (i - 1)) ? ht[i - 1][j - (1 << (i - 1))] : 0);
    }
    int query(int l, int r) {
        l = rk[l], r = rk[r];
        if(l > r) swap(l, r);
        int tmp = Log[r - l];
        return min(ht[tmp][r], ht[tmp][l + (1 << tmp)]);
    }
}A[2];

int L[N], R[N];
void work() {
    scanf("%s", S + 1);
    n = strlen(S + 1);
    A[0].get_SA(S), A[0].get_ht(S);
    reverse(S + 1, S + n + 1);
    A[1].get_SA(S), A[1].get_ht(S);
    for(int len = 1; len <= n / 2; len++) {
        for(int i = 1, j = 1 + len; j <= n; i += len, j += len) {
            int r = A[0].query(i, j), l = A[1].query(n - i + 1, n - j + 1);
            l = min(l, len), r = min(len, r);
            if(i - l + 1 <= i - len + r) R[i - l + 1]++, R[i - len + r + 1]--;
            if(j + len - l <= j + r - 1) L[j + len - l]++, L[j + r]--;
        }
    }
    for(int i = 2; i <= n; i++) L[i] += L[i - 1], R[i] += R[i - 1];
    long long ans = 0;
    for(int i = 1; i < n; i++) ans += (long long)L[i] * R[i + 1];
    printf("%lld\n", ans);
}

int main() {
    pre();
    int T; scanf("%d", &T);
    while(T--) {
        memset(L, 0, sizeof L);
        memset(R, 0, sizeof R);
        work();
    }
    return 0;
}