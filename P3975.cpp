#include <bits/stdc++.h>
using namespace std;

const int N = 500100;

char c[N];
int n, mode, K;

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

int get_far(int srt, int x) {
    for(int i = 20; i >= 0; i--)
        if(st_ht[srt][i] >= x) srt = srt + (1 << i) - 1;
    return srt;
}

int main() {
    scanf("%s", c + 1);
    scanf("%d%d", &mode, &K);
    n = strlen(c + 1);
    get_SA(c); get_ht(c);
    for(int i = 1; i <= n; i++) {
        for(int j = st_ht[i][0] + 1; j <= st_ht[i + 1][0]; j++) {
            int touch = get_far(i + 1, j);
            int del_k = mode ? touch - i + 1 : 1;
            if(K <= del_k) {
                for(int k = sa[i]; k <= sa[i] + j - 1; k++) printf("%c", c[k]);
                return 0;
            }
            K -= del_k;
        }
        int used = max(st_ht[i][0], st_ht[i + 1][0]);
        if(K <= n - sa[i] + 1 - used) {
            for(int j = sa[i]; j - sa[i] + 1 - used <= K; j++) printf("%c", c[j]);
            return 0;
        }
        K -= n - sa[i] + 1 - used;
    }
    printf("-1");
    return 0;
}