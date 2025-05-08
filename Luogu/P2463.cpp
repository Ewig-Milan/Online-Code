#include <bits/stdc++.h>
using namespace std;

const int N = 200100;

int n, Nn, lim;
int d[N];

int sa[N], ht[N], blg[N], rk[N << 1], rk_cpy[N << 1], T[N],  se_st[N];
void get_SA(int s[]) {
    int m = 20000;
    for(int i = 1; i <= Nn; i++) T[rk[i] = s[i]]++;
    for(int i = 2; i <= m; i++) T[i] += T[i - 1];
    for(int i = Nn; i; i--) sa[T[rk[i]]--] = i;
    for(int k = 1, t; k < Nn; k <<= 1, m = t) {
        t = 0;
        for(int i = Nn - k + 1; i <= Nn; i++) se_st[++t] = i;
        for(int i = 1; i <= Nn; i++)
            if(sa[i]  > k) se_st[++t] = sa[i] - k;
        for(int i = 0; i <= m; i++) T[i] = 0;
        for(int i = 1; i <= Nn; i++) T[rk[i]]++;
        for(int i = 2; i <= m; i++) T[i] += T[i - 1];
        for(int i = Nn; i; i--) sa[T[rk[se_st[i]]]--] = se_st[i];
        swap(rk_cpy, rk); t = 0;
        for(int i = 1; i <= Nn; i++) {
            if(rk_cpy[sa[i]] != rk_cpy[sa[i - 1]] || 
                rk_cpy[sa[i] + k] != rk_cpy[sa[i - 1] + k]) t++;
            rk[sa[i]] = t;
        }
        if(t == Nn) return;
    }
}
void get_ht(int s[]) {
    ht[1] = 0;
    for(int i = 1, k = 0; i <= Nn; i++) {
        if(rk[i] == 1) continue;
        if(k) k--;
        while(s[i + k] == s[sa[rk[i] - 1] + k] && 
            i + k <= Nn && sa[rk[i] - 1] + k <= Nn) k++;
        ht[rk[i]] = k;
    }
}

bool check(int x) {
    int C[1100];
    memset(C, 0, sizeof(C));
    for(int i = 1, cnt = 0; i <= Nn; i++) {
        if(ht[i] < x) memset(C, 0, sizeof(C)), cnt = 0;
        if(!C[blg[sa[i]]] && blg[sa[i]]) cnt++;
        C[blg[sa[i]]]++;
        if(cnt == n) return true;
    }
    return false;
}

int main() {
    scanf("%d", &n);
    int tmp = 0;
    for(int i = 1, len; i <= n; i++) {
        scanf("%d", &len);
        for(int j = 1; j <= len; j++) scanf("%d", &d[tmp + j]), blg[tmp + j] = i;
        blg[tmp + len] = 0;
        tmp += len;
        d[++tmp] = -1;
    }
    if(n == 1) {
        printf("%d", tmp - 1);
        return 0;
    }
    Nn = tmp - 1;
    for(int i = 1; i <= Nn; i++) 
        if(d[i] != -1 && d[i + 1] != -1) d[i] = d[i + 1] - d[i];
        else d[i] = -9999 + lim++;
    for(int i = 1; i <= Nn; i++) d[i] += 10000;
    get_SA(d); get_ht(d);
    int l = 0, r = 110;
    while(l < r) {
        int mid = l + r + 1 >> 1;
        if(check(mid)) l = mid;
        else r = mid - 1;
    }
    printf("%d", l + 1);
    return 0;
}