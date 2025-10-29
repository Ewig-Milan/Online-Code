//
// DP 题的一个重要做题方法就是 “ 在容易 DP 的问题上 DP ”，正如本题：在分割线上 DP
// 看上去是废话，但其实就是告诉我们：
// 要仔细寻找题目的特点（性质），并转换成一些好做的东西
//
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 2100, mod = 1e9 + 7;

int n;
int p_v[N][N], p_h[N][N];
int f[2][N][N];
char mp[N][N];

int P[N];
void prepare() {P[0] = 1; for(int i = 1; i < N; i++) P[i] = 2ll * P[i - 1] % mod;}

int main() {
    prepare();

    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%s", mp[i] + 1);
    for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++)
        p_h[i][j] = p_h[i][j - 1] + (mp[i][j] == '.');
    for(int j = 1; j <= n; j++) for(int i = 1; i <= n; i++)
        p_v[j][i] = p_v[j][i - 1] + (mp[i][j] == '.');
    
    f[0][0][0] = f[1][0][0] = 1;
    for(int i = 0; i <= n; i++) for(int j = 0; j <= n; j++) {
        if(!i && !j) continue;
        if(i) {
            f[0][i][j] = (ll)f[0][i - 1][j] * P[p_h[i][j]] % mod;
            if(mp[i][j] == '.') f[0][i][j] += (ll)f[1][i - 1][j] * P[p_h[i][j - 1]] % mod;
            f[0][i][j] %= mod;
        }
        if(j) {
            f[1][i][j] = (ll)f[1][i][j - 1] * P[p_v[j][i]] % mod;
            if(mp[i][j] == '.') f[1][i][j] += (ll)f[0][i][j - 1] * P[p_v[j][i - 1]] % mod;
            f[1][i][j] %= mod;
        }
    }
    printf("%d", (f[0][n][n] + f[1][n][n]) % mod);
    return 0;
}