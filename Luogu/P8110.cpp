#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 100100, mod = 998244353;

int n, k;
int a[N], b[N];
int x, y, z;

int quick_p(int x, int a) {
    int res = 1;
    while(a) {
        if(a & 1) res *= x, res %= mod;
        x *= x, x %= mod;
        a >>= 1;
    }
    return res;
}

signed main() {
    scanf("%lld%lld", &n, &k);
    for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
    for(int i = 1; i <= n; i++) scanf("%lld", &b[i]);
    if(!k) {
        printf("%lld", n);
        return 0;
    }
    for(int i = 1; i <= n; i++) {
        x += a[i], y += b[i], z += a[i] * b[i] % mod;
        x = (x % mod + mod) % mod;
        y = (y % mod + mod) % mod;
        z = (z % mod + mod) % mod;
    }
    printf("%lld", x * y % mod * quick_p(z, k - 1) % mod);
    return 0;
}