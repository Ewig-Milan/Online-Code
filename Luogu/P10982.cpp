#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1100, mod = 1004535809ll;

int n, C[N][N], h[N];

int qp(int x, int a) {
    int res = 1;
    while(a) {
        if(a & 1) res *= x, res %= mod;
        a >>= 1;
        x *= x, x %= mod;
    }
    return res;
}

void get_C() {
    for(int i = 0; i < N; i++)
    for(int j = 0; j <= i; j++)
        if(!j || i == j) C[i][j] = 1;
        else C[i][j] = C[i - 1][j] + C[i - 1][j - 1], C[i][j] %= mod;
}

int H(int i) {
    if(i <= 1) return h[i] = 1;
    if(h[i]) return h[i];
    int res = qp(2, i * (i - 1) / 2);
    for(int k = 1; k <= i - 1; k++) {
        int tmp = H(k) * C[i - 1][k - 1] % mod;
        tmp *= qp(2, (i - k) * (i - k - 1) / 2), tmp %= mod;
        res -= tmp, res %= mod;
    }
    h[i] = (res + mod) % mod;
    return h[i];
}

signed main() {
    get_C();
	scanf("%lld", &n);
    printf("%lld", H(n));
    return 0;
}