//致自己 后缀数组板子
//致自己 后缀数组板子
//致自己 后缀数组板子
//致自己 后缀数组板子
//致自己 后缀数组板子
//致自己 后缀数组板子
//致自己 后缀数组板子
//致自己 后缀数组板子
//致自己 后缀数组板子
//致自己 后缀数组板子
//致自己 后缀数组板子
//致自己 后缀数组板子
//致自己 后缀数组板子
//致自己 后缀数组板子
//致自己 后缀数组板子
//致自己 后缀数组板子
//致自己 后缀数组板子
//致自己 后缀数组板子
//致自己 后缀数组板子
//致自己 后缀数组板子

//最终版 (real? 
//
//请为自己负责：
//AC后请自测下面的 Hack数据 
//
// (Linux, 请勿用防爆的Windows)
// int main() {freopen("test.in", "w", stdout); for(int i = 1; i <= 1000000; i++) putchar('z'); putchar('\n'); return 0;}
// 
#include <bits/stdc++.h>
using namespace std;

const int N = 1000100;

char c[N];
int n;

int sa[N], ht[N], rk[N << 1], T[N], rk_cpy[N << 1], se_st[N];//4.3补丁 

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
		if(rk[i] == 1) continue;//4.3补丁 
		if(k) k--;
		while(s[i + k] == s[sa[rk[i] - 1] + k] &&
			i + k <= n && sa[rk[i] - 1] + k <= n) k++; //4.9补丁 
		ht[rk[i]] = k;
	}
}

int main() {
    scanf("%s", c + 1);
    n = strlen(c + 1);
    get_SA(c);
    get_ht(c);
    for(int i = 1; i <= n; i++) printf("%d ", sa[i]);
    printf("\n");
    for(int i = 1; i <= n; i++) printf("%d ", ht[i]);
    return 0;
}