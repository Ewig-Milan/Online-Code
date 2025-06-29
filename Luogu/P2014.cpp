#include <bits/stdc++.h>
using namespace std;

const int N = 310;

int n, m;
int f[N][N];

int s[N];
int h[N], e[N << 1], ne[N << 1], idx;
void add(int a, int b) {e[idx] = b, ne[idx] = h[a], h[a] = idx++;}

void DP(int x) {
    for(int i = 1; i <= m; i++) f[x][i] = -1e9;
    if(x) f[x][1] = s[x];
    for(int i = h[x]; ~i; i = ne[i]) {
        int j = e[i];
        DP(j);
        for(int p = m; p >= 0; p--) // 父亲
        for(int k = 0; k + p <= m; k++) // 儿子
            if(p || !x) f[x][p + k] = max(f[x][p + k], f[x][p] + f[j][k]);
    }
}

int main() {
    memset(h, -1, sizeof h);
    
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++) {
        int a; scanf("%d%d", &a, &s[i]);
        if(a) add(a, i);
        else add(0, i);
    }
    DP(0);
    printf("%d", f[0][m]);
    return 0;
}